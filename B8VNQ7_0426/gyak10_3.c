#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main() {
    int child = 0;

    if ((child = fork()) == 0) {
        int shmid;
        key_t key;
        int size=512;
        int shmflg;

        key = SHMKEY;
        shmflg = 0;
        if ((shmid=shmget( key, size, shmflg)) < 0) 
        {
            printf("Nincs meg szegmens! El kell kesziteni!\n");
            shmflg = 00666 | IPC_CREAT;
            if ((shmid=shmget( key, size, shmflg)) < 0) 
            {
                perror("Az shmget rendszerhivas sikertelen!\n");
                exit(-1);
            }
        } 
        else 
        {
            printf("Letezik mar szegmens!\n");
        }

        printf("Az shmid azonositoja %d:\n", shmid);

        exit (0);
    }

    else
    {
        if (child = fork() == 0) {
            int shmid;
            key_t key;
            int size=512;
            int shmflg;
            struct vmi {
                int  hossz;
                char szoveg[512-sizeof(int)];
            } *segm;
            
            key = SHMKEY;
            shmflg = 0;
            if ((shmid=shmget( key, size, shmflg)) < 0) 
            {
                perror("Az shmget rendszerhivas sikertelen!\n");
                exit(-1);
            }

            shmflg = 00666 | SHM_RND;
            segm = (struct vmi *)shmat(shmid, NULL, shmflg);
            if (segm == (void *)-1) {
                perror("Sikertelen attach!\n");
                exit (-1);
            }

            if (strlen(segm->szoveg) > 0)
            {
                printf("Regi szoveg: %s (%d hosszon)\n",segm->szoveg,segm->hossz);
            } 
        
            printf("Kerem, adjon meg uj szoveget!\n");
            gets(segm->szoveg);
            printf("Az uj szoveg: %s\n",segm->szoveg);
            segm->hossz=strlen(segm->szoveg);
                
            shmdt(segm);

            exit(0);
        }

        else 
        {
            int shmid;
            key_t key;
            int size=512;
            int shmflg;
            int rtn;
            int cmd;
            struct shmid_ds shmid_ds, *buf;
            buf = &shmid_ds;

            key = SHMKEY;
            shmflg = 0;
            if ((shmid=shmget( key, size, shmflg)) < 0) 
            {
                perror("Az shmget rendszerhivas sikertelen!\n");
                exit(-1);
            }

        do {
            printf("Kerem, adja meg a parancs szamat!\n");
            printf("0 IPC_STAT (status)\n");
            printf("1 IPC_RMID (torles)   >  ");
            scanf("%d",&cmd);
            } while (cmd < 0 && cmd > 1);

            switch (cmd)
            {
            case 0: rtn = shmctl(shmid, IPC_STAT, buf);
                printf("Segm. meret: %ld\n",buf->shm_segsz);
                printf("Utolso shmop-os processz PID: %d\n ",buf->shm_lpid);
                break;
            case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
                printf("Szegmens sikeresen torolve!\n");
            }
            
            exit(0);
        }
    }
}