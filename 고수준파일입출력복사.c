#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    FILE* fp1;
    FILE* fp2;
    // 2개의 file 포인터 생성
    char buf[BUFSIZ];
    int n;

    if((fp1 = fopen(argv[1], "r")) == NULL)
    {
        perror("fail open !!! \n");
        exit(0);
    }

    if((fp2 = fopen(argv[2], "w")) == NULL)
    {
        perror("fail open !!! \n");
        exit(0);
    }

    while((n=fread(buf, sizeof(char), 1, fp1))>0)
    {
        buf[6] = '\0';
        fwrite(buf, sizeof(char), 1, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;

}
