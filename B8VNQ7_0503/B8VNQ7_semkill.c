#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L

	int semid,nsems,rtn;
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
        perror("Semget hiba!\n"); 
        exit(0);
    }
	else
    {
        printf("semid: %d\n",semid);
    }

	cmd = IPC_RMID;
	rtn = semctl(semid, 0, cmd, arg);

	printf("kill rtn: %d\n",rtn);
}