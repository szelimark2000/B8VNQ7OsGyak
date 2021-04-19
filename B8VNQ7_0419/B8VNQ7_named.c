#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    pid_t cpid;
    int visszater;
    int fd;
    char buffer[64];
    char B8VNQ7[] = "B8VNQ7";

    visszater = mkfifo(B8VNQ7, 0666);
    cpid = fork();

    if(visszater == -1)
    {
        perror("mkfifo()");
        exit(-1);
    }

    if(cpid == 0)
    {
        printf("Gyermekprocessz PID erteke: %d\n", getpid());
        fd = open(B8VNQ7, O_WRONLY);

        if(fd == -1)
        {
            perror("open()");
            exit(-1);
        }

        strcpy(buffer, "Szeli Mark, B8VNQ7\n");
        write(fd, buffer, strlen(buffer));
        printf("Gyermek PID erteke iras utan: %d\n", getpid());
        close(fd);
    }

    else
    {
        printf("Szuloprocessz PID erteke: %d\n", getpid());
        fd = open(B8VNQ7, O_RDONLY);
        if(fd == -1)
        {
            perror("open()");
            exit(-1);
        }

        printf("Szuloprocessz PID erteke olvasas elott: %d\n", getpid());
        visszater = read(fd, &buffer, sizeof(buffer));
        printf("read() %d byte-ot olvasott be, string: %s\n", visszater, buffer);
        close(fd);
        unlink(B8VNQ7);
    }

    return 0;
}