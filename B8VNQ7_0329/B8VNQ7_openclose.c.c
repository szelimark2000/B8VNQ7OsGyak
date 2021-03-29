#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd, ret;
    char buf[38];

    buf[0] = 0;

    fd = open("B8VNQ7.txt", O_RDWR);

    printf("Hibakereses:\n");

    if (fd != -1){
        printf("Sikeres beolvasas!\n");
    }
    else {
        printf("Sikertelen megnyitas!\n");
        exit(-1);
    }

    ret = read(fd, buf, 38);
    printf("\nA read() rendszerhivas beolvasott %d byte-ot. Az alabbiak szerepeltek a dokumentumban: %s\n", ret, buf);

    ret = lseek(fd, 0, SEEK_SET);
    printf("\nA lseek() rendszerhivas: %d\n", ret);

    ret = write(fd, buf, 6);
    printf("\nA write() rendszerhivas: %d\n", ret);

    close(fd);

    return 0;
}
