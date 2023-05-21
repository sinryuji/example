#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("./test/test.txt", O_WRONLY | O_CREAT, 0644);
  std::cout << "fd : " << fd << std::endl;
  close(fd);
  write(fd, "asdf", 4);
}
