#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} rcvbuf, *msgp;

struct msqid_ds ds, *buf;

main()
{
	int msgid;
	key_t key;
	int mtype, msgflg;
	int rtn, msgsz;
	
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);    
 	if (msgid == -1) 
        {
            perror("Az msgget rendszerhivas nem sikerult!\n");
            exit(-1);
        }

	printf("Az msgid: %d\n", msgid);

	msgp = &rcvbuf;
	buf = &ds;
	msgsz = 20;
	mtype = 0;
	rtn = msgctl(msgid, IPC_STAT, buf);

	printf("Az uzenetek szama: %d\n", buf->msg_qnum);
	
	while (buf->msg_qnum) 
        {
            rtn = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
            printf("Az rtn: %d, a vett uzenet: %s\n", rtn, msgp->mtext);
            rtn = msgctl(msgid,IPC_STAT,buf);
        }
	exit (0);
}