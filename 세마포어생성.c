// create semphore

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int semid;

    semid = semget((key_t)12345, 1, 0666 | IPC_CREAT);
    // (key, 세마포어의 크기, flag)
    if(semid == -1)
    {
        perror("semaphores failed : ");
        exit(1);
    }
    return 0;
}
