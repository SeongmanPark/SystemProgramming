// shared memory mapping

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
 int fd;
 caddr_t  addr;
 struct stat statbuf;
 
 if(argc != 2)
 {
  fprintf(stderr, "Usage : %s file name\n", argv[0]);
  exit(1);
 }

 if(stat(argv[1], &statbuf) == -1)
 {
  perror("stat");
  exit(1);
 }

 if((fd=open(argv[1], O_RDWR)) == -1)
 {
  perror("open");
  exit(1);
 }

 addr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
 
 if(addr == MAP_FAILED)
 {
  perror("mmap");
  exit(1);
 }

 close(fd);

 printf("%s", addr);
 
 if(munmap(addr, statbuf.st_size) == -1)
 {
  perror("munmap !!");
  exit(1);
 }
 // 매핑한 메모리 해제 부분 !!!!!

 printf("%s", addr);
 return 0;
}
