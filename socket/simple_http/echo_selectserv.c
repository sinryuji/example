#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	struct timeval timeout;
	fd_set reads, cpy_reads;
	socklen_t adr_sz;	
	int fd_max, str_len, fd_num, i;
	char buf[BUF_SIZE];

	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);									   	// socket 함수 호출을 통해 소켓을 생성하고 있다.
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)           // bind 함수 호출을 통해서 IP 주소와 port 번호를 할당하고 있다.
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)                                                      // listen 함수를 호출하고 있다. 이로써 소켓은 연결 요청을 받아들일 수 있는 상태가 된다.
		error_handling("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);
	fd_max = serv_sock;
	printf("serv_sock : %d\n", serv_sock);

	while(1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
			break;
		if (fd_num == 0)
			continue;

		for (i = 0; i < fd_max + 1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))
			{
				if (i == serv_sock)
				{
					adr_sz = sizeof(clnt_addr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &adr_sz);
					FD_SET(clnt_sock, &reads);
					if (fd_max < clnt_sock)
						fd_max = clnt_sock;
					const char * ddd = "\
HTTP/1.1 200 OK\r\n\
Server: Hyeongki&Kanghyki server\r\n\
Content-Length: 63\r\n\
Content-Type: text/html\r\n\
\r\n\
<!doctype html>\
<html>\
<body>\
<h1>Hello, World!</h1>\
</body>\
</html>";
					write(clnt_sock, ddd, strlen(ddd));
					close(clnt_sock);
					FD_CLR(clnt_sock, &reads);
					printf("connected client: %d \n", clnt_sock);
				}
				else
				{
					str_len = read(i, buf, BUF_SIZE);
					if (str_len == 0)
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n", i);
					}
					else
					{
						printf("buf: %s", buf);
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
