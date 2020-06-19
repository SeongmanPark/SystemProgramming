// message queue send

#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    // 메세지 타입 (양수여야 함)
    char mtext[80];
    // 메세지 자료 자체를 담음.
};
// 메세지를 위해 구조체를 만듬 (구조체로 메시지 전송)

int main()
{
    key_t key;
    // 메세지의 생성자와 주인의 정보를 담는 키 변수
    int msgid;

    struct mymsgbuf mesg;
    // 메세지 정보를 담을 구조체 생성
    key = ftok("keyfile", 1);
    // ftok의 첫 번째 인자에 해당하는 파일이 있어야 key가 만들어진다.
    // 없을시 -1이 리턴되는데 이걸 아이디로 받아들여 아이디가 0xffffffff가 된다.
    // 예외처리 해 줘야함.
    msgid = msgget(key, IPC_CREAT | 0644);
    // Message Queue를 생성 !!!!!!! return 은 msgid
    // flag가 IPC_EXCL 일때 key를 가진 메세지 큐가 이미 존재하면 에러를 리턴
    if(msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    mesg.mtype = 1;
    // 메세지 구조체에 메세지 타입을 1이라고 설정
    strcpy(mesg.mtext, "Message Q Test\n");
    // 메세지 구조체에 보낼 메세지 입력

    if(msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) < 0) // 메세지 전송, 
    // IPC_NOWAIT -> 메세지 큐가 가득 찼으면, 메세지는 큐에 씌여질 수 없고, 통제권(control)은 호출한 프로세스에게 돌아간다
    {
        perror("msgsnd");
        exit(1);
    }

    printf("Send Message Queue : %s", mesg.mtext);
    return 0;
}
