//shmid로 shared memory 사용

#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int shmid;
    int pid;

    int* cal_num;
    void* shared_memory = (void*)0;
    // 공유메모리 공간을 만든다.
    shmid = shmget((key_t)1234, sizeof(int), 0666 | IPC_CREAT);
    // shared memory 가져오기 (key, szie, flag)
    if(shmid == -1)
    {
        perror("shmget failed : ");
        exit(1);
    }

    shared_memory = shmat(shmid, (void*)0, 0);
    if(shared_memory == (void*)-1)
    {
        perror("shmat failed : ");
        exit(0);
    }

    cal_num = (int*)shared_memory;
    pid=fork();

    if(pid==0)
    {
        shmid = shmget((key_t)1234, sizeof(int), 0);
        if(shmid == -1)
        {
            perror("shmget failed : ");
            exit(1);
        }
        
        shared_memory = shmat(shmid, (void*)0, 0666 | IPC_CREAT);
        if(shared_memory == (void*)-1)
        {
            perror("shmat failed : ");
            exit(1);
        }
        cal_num = (int*)shared_memory;
        *cal_num = 1;

        while(1)
        {
            *cal_num = *cal_num + 1;
            printf("child %d\n", *cal_num);
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        while(1)
        {
            sleep(1);
            printf("%d\n", *cal_num);
        }
    }
}
