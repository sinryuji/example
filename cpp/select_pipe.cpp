#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <string>
#include <vector>

using namespace std;

int readSize(const std::string &s) {
  for (int i = 0; i < s.size(); ++i) {
    if (!isdigit(s[i])) {
      return std::atoi(s.substr(0, i).c_str());
    }
  }
  return 0;
}

int main() {
  std::vector<std::string> bufs(10000);
  const int NUM_CHILDREN = 5;
  int pipes[NUM_CHILDREN][2]; // 파이프 배열 선언

  // 파이프 생성 및 오류 처리
  for(int i=0; i<NUM_CHILDREN; i++) {
    if(pipe(pipes[i]) == -1) {
      perror("pipe");
      exit(1);
    }
  }

  // 자식 프로세스 생성
  pid_t pid;
  for(int i=0; i<NUM_CHILDREN; i++) {
    pid = fork();
    if(pid == -1) {
      perror("fork");
      exit(1);
    } else if(pid == 0) { // 자식 프로세스
      close(pipes[i][0]); // 자식 프로세스는 읽기 파이프를 사용하지 않음
//      char msg[] = "Hello from child process!";
//      write(pipes[i][1], msg, sizeof(msg)); // 자식 프로세스가 부모 프로세스에게 데이터 전송
      srand(i * 12312893);
      while(1) {
        std::string aa = "GET /hello.htm HTTP/1.1\
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\
Host: www.tutorialspoint.com\
Accept-Language: en-us\
Accept-Encoding: gzip, deflate\
Connection: Keep-Alive";
        aa = to_string(aa.length()) + aa;
        write(pipes[i][1], aa.c_str(), aa.length());
        sleep(rand() % 20);
      }
      close(pipes[i][1]);
      exit(1);
    }
  }

  // 부모 프로세스
  fd_set readfds;
  int maxfd = -1;

  for(int i=0; i<NUM_CHILDREN; i++) {
    close(pipes[i][1]); // 부모 프로세스는 쓰기 파이프를 사용하지 않음
    fcntl(pipes[i][0], F_SETFL, O_NONBLOCK);
    if(pipes[i][0] > maxfd) {
      maxfd = pipes[i][0];
    }
  } 

  

  while(1) {
    FD_ZERO(&readfds);
    for(int i=0; i<NUM_CHILDREN; i++) {
      FD_SET(pipes[i][0], &readfds);
    }

    struct timeval asd;
    asd.tv_sec = 1;
    asd.tv_usec = 1;
    if(select(maxfd+1, &readfds, NULL, NULL, &asd) == -1) {
      perror("select");
      exit(1);
    }

    for(int i=0; i<NUM_CHILDREN; i++) {
      if(FD_ISSET(pipes[i][0], &readfds)) {
        char buf[1024];
        size_t num_read = read(pipes[i][0], buf, sizeof(buf));
        buf[num_read] = 0;
        if(num_read == -1) {
          perror("read");
          exit(1);
        } else {
          bufs[i] += buf;
          int size = readSize(bufs[i]);
          if (bufs[i].length() >= size) {
            std::cout << bufs[i].substr(3, size) << std::endl;
            bufs[i].erase(0, size + 3);
          }
        }
      }
    }

    // 모든 자식 프로세스가 종료되면 종료
    int status;
    pid_t result;
      result = waitpid(-1, &status, WNOHANG);
      if(result > 0) {
        cout << "Child process " << result << " exited with status " << status << endl;
      }
  }
}
