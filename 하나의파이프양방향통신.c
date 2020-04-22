#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
 pid_t pid;
 int status, fds[2];
 char buffer[BUFSIZ];
 if(pipe(fds) == -1 )
     perror("pipe() error\n");

 if((pid=fork())>0)
 {
  read(fds[0], buffer, BUFSIZ);
  printf("[parent] %s\n", buffer);
  strcpy(buffer, "Parent 안녕하세요.");
  write(fds[1], buffer, BUFSIZ);
  //sleep(3);
  waitpid(pid, &status, 0);
 }
 else if(pid == 0)
 {
  strcpy(buffer, "child 안녕하세요.");
  write(fds[1], buffer, BUFSIZ);
  sleep(2);
  read(fds[0], buffer, BUFSIZ);
  printf("[child] %s\n", buffer);
 }

 return 0;
}
