#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {		
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

main()
{
	int msgid;
	key_t key;
	int msgflg;
	int rtn, msgsz;
	
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget(key, msgflg);

 	if (msgid == -1) 
        {
            perror("Az msgget rendszerhivas nem sikerult!\n");
            exit(-1);
        }

	printf("Az msgid %d, %x : \n ", msgid, msgid);

	msgp = &sndbuf;
	msgp->mtype = 1;
 	strcpy(msgp->mtext, "Nev: Szeli Mark\n");
	msgsz = strlen(msgp->mtext) + 1;

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("Az 1. msgsnd visszaadott %d-t\n", rtn);
	printf("A kikuldott uzenet: %s\n ", msgp->mtext);

	strcpy(msgp->mtext, "NEPTUN kod: B8VNQ7\n ");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("A 2.  msgsnd visszaadott %d-t\n ", rtn);
	printf("A kikuldott uzenet: %s\n ", msgp->mtext);
	exit (0);
}