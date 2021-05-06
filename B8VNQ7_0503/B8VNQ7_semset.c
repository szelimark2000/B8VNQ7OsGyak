#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456

	int semid;
	int nsems;
	int semnum;
    int rtn;
	int semflg;
	struct sembuf sembuf, *sop; 
	union semun arg;
	int cmd;
main()
{
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) 
    {
        perror("semget hiba!\n"); 
        exit(0);
    }
	else 
    {
        printf("emid: %d\n",semid);
    }
    printf ("Kerem a semval erteket!\n");
	semnum = 0;
	cmd = SETVAL;
	scanf("%d",&arg.val);
	rtn = semctl(semid, semnum, cmd, arg);
	printf("set rtn: %d, semval: %d\n",rtn, arg.val);
}