//msg recevied

#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

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
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1);
    // ftok의 첫 번째 인자에 해당하는 파일이 있어야 key가 만들어진다.
    // 없을시 -1이 리턴되는데 이걸 아이디로 받아들여 아이디가 0xffffffff가 된다.
    // 예외처리 해 줘야함.
    if((msgid = msgget(key, 0))< 0)
    {
        perror("msgget");
        exit(1);
    }

    len = msgrcv(msgid, &inmsg, 80, 0, IPC_NOWAIT);
    // msgid 번호의 메세지 큐에서 메세지를 받고 inmsg구조체에 저장.
    // flag IPC_NOWAIT 메세지 받을때까지 블록되는것을 방지하기 위해 메세지가 없으면 -1리턴
    // (메세지 식별자, 메세지 정보를 담을 구조체, 메세지 버퍼 크기, 읽어올 메세지 유형, flag)
    printf("Received Msg = %s\nLen=%d\n", inmsg.mtext, len);
    return 0;
}
