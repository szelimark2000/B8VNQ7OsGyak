#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> // Szükséges, hiányos header állomány deklarálása.

/*
Feladat leírása:
--------------------------------------------------------------------------------------
    3. Írjon C nyelvű programot, ami:
        - létrehoz két gyermekprocesszt,
        - ezek a gyermekprocesszek létrehoznak 3-3 további gyermeket,
        - ezek az unokák várakoznak néhány másodpercet és szűnjenek meg,
        - a szülők várják meg a gyermekek befejeződését és csak utána szűnjenek meg.
*/

int main()
{   
    int gyermek_pid[2]; // Gyermekprocesszek PID értékeineknek tárolására szolgáló tömb.
    int unoka_pid[6]; // Unokaprocesszek PID értékeineknek tárolására szolgáló tömb.
    pid_t pid; // pid_t adattípus a proceszek azonosítását jelenti.
    int alvas = 10; // A várakozásra szolgáló változó, melynek értéke 10.

    printf("Szülőprocessz vagyok!\n"); // Szülőprocessz kiíratása.

        for(int i = 0; i < 2; i++) // 2 gyermekprocessz létrehozását szolgáló számláló (for) ciklus.
    {
        if((pid = fork()) < 0) // Hibaellenőrzés.
        {
            perror("Fork ERROR!\n"); // Fork error kiíratása.
        }

        else if(pid == 0) // A gyermekprocessz létrehozása. Ha a fork() rendszerhívás visszatérési értéke 0, akkor lefut az elágazás.
        {
            gyermek_pid[i] = getpid(); // A tömb i-edik elemének beállítása.

            printf("Gyermekprocessz vagyok! PID értékem: %d, Szülőm PID értéke: %d\n", getpid(), getppid()); // A gyermekprocessz, annak PID-je, valamint a szülőjének PID-jének kiíratása.

            for(int i = 0; i < 3; i++) // 3-3 unokaprocesszek létrehozására szolgáló számláló (for) ciklus.
            {
                if((pid = fork()) < 0) // Hibaellenőrzés.
                {
                    perror("Fork ERROR!\n"); // Fork error kiíratása.
                }
                
                else if(pid == 0) // Az unokaprocesszek létrehozása. Ha a fork() rendszerhívás visszatérési értéke 0, akkor lefut az elágazás.
                {
                    unoka_pid[i] = getpid(); // A tömb i-edik elemének beállítása.
                    printf("Unokaprocessz vagyok! Unokaprocessz PID értékem: %d, Szülőm PID értéke: %d\n", getpid(), getppid()); // Az uokaprocessz, annak PID-je, valamint a szülőjének PID-jének kiíratása.
                    sleep(alvas); // Az unokaprocesszek 10 másodperc után megszűnnek.
                    printf("Megszűnt unokaprocessz! A megszűnt unokaprocessz PID értéke: %d\n", getpid()); // Az unokaprocessz megszűnésének kiíratása, valamint annak PID-je.
                    exit (0);
                }
            }

            wait(NULL); // Unokaprocesszekre való várakozás.
            printf("Megszűnt gyermekprocessz! A megszűnt gyermekprocessz PID értéke: %d\n", getpid()); // A gyermkeporcessz megszűnésének kiíratása, valamint annak PID-je.
            exit (0);            
        }      
    }

    wait(NULL); // Gyermekprocesszekre való várakozás.
    printf("Megszűnt szülőprocessz!\n"); // Szülőprocessz megszűnésének kiíratása.
    return 0;
}