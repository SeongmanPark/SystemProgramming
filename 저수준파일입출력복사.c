#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    int fd1, fd2;
    // file descriptor 정의
    int n;
    char buf[BUFSIZ];
    // 몇글자씩 읽었는지 알려주는 n, 읽은 글자를 저장할 buf

    if((fd1 = open(argv[1], O_RDONLY)) == -1)
    {
        perror("open fail !!! \n");
        exit(1);
    }

    if((fd2 = open(argv[2], O_CREAT | O_WRONLY)) == -1)
    {
        perror("open fail !!! \n");
        exit(1);
    }

    while((n = read(fd1, buf, sizeof(buf))) > 0)
    {
        buf[n] = '\0';
        // 읽은 문자의 마지막을 NULL로 하기.
        write(fd2, buf, n);
        //write할 파일에다가 쓰기
    }

    close(fd1);
    close(fd2);

    return 0;
}
