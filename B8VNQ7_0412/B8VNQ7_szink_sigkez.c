#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void alarmkap()
{
    printf("SIGUSR1 kuldes a gyermekprocessznek...\n");
}

void signalusr()
{
    printf("SIGUSR1 kapott a gyermekprocessz!\n");
}

int main(void)
{
    pid_t pid;
    int stop = 5;
    int time = 10;

    if((pid = fork()) < 0)
    {
        perror("Fork error!\n");
    }

    else if(pid == 0)
    {
        printf("A gyermekprocessz kimenete.\n");
        signal(SIGUSR1, signalusr);

        for(int i = 0; i < stop; i++)
        {
            pause();
            printf("A gyermekprocessz allpota megvaltozott!\n");
        }

        printf("A gyermekprocessz leallt!\n");
    }

    else
    {
        printf("A szuloprocessz kimenetele.\n");
        signal(SIGALRM, alarmkap);

        for(int i = 0; i < stop; i++)
        {
            alarm(time);
            pause();
            printf("PID erteke: %d\n", pid);
            kill(pid, SIGUSR1);
        }

        printf("A szuloprocessz leallt!\n");
    }

    exit(0);
}