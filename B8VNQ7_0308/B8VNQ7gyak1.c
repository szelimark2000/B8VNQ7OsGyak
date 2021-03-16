#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    system("date"); //sikeres, lefutó parancs
    system("hello"); //hibás, nem létező parancs

    return 0;
}
