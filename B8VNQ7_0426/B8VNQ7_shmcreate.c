#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

main()
{
	int shmid;
	key_t key;
	int size=512;
	int shmflg;

	key = SHMKEY;
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) 
    {
        printf("Nincs meg szegmens! El kell kesziteni!\n");
        shmflg = 00666 | IPC_CREAT;
        
        if ((shmid=shmget(key, size, shmflg)) < 0) 
            {
                perror("Az shmget system-call sikertelen!\n ");
                exit(-1);
            }
	} 
    else 
    {
        printf("Letezik mar szegmens!\n ");
    }

	printf("Az shmid azonositoja: %d\n", shmid);
	exit (0);
}