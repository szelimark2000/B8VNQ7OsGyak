#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    if(argc != 2)
    {
        fprintf(stderr, "Használata: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(pipe(pipefd) == -1)
    {
        perror("PIPE");
        exit(EXIT_FAILURE);
    }

    printf("PID erteke: %d, fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]);

    cpid = fork();

    if(cpid == -1)
    {
        perror("FORK");
        exit(EXIT_FAILURE);
    }

    if(cpid == 0)
    {
        close(pipefd[1]);
        while (read(pipefd[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }

    else
    {
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}