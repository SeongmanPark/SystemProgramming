// message queue remove

#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main()
{
    key_t key;
    int msgid;

    key = ftok("keyfile", 1);
    // ftok의 첫 번째 인자에 해당하는 파일이 있어야 key가 만들어진다.
    // 없을시 -1이 리턴되는데 이걸 아이디로 받아들여 아이디가 0xffffffff가 된다.
    // 예외처리 해 줘야함.
    msgid = msgget(key, IPC_CREAT | 0644);
    // key로 msgid 얻고, 동시에 메세지 큐 생성 !!! 권한 0644 
    if(msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    printf("Before IPC_RMID\n");
    system("ipcs -q");
    // 메세지 큐 삭제하기 전에 ipcs -q 명령어 실행
    msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
    // (메세지 큐 식별자, 수행할 제어 기능, 제어 기능에 사용되는 메세지 큐 구조체 주소)
    printf("After IPC_RMID\n");
    system("ipcs -q");
    // 메세지 큐 삭제한 후 ipcs -q 명령어로 확인

    return 0;
}
