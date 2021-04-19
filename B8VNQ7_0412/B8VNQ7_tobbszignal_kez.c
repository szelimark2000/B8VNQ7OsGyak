#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int sig);

unsigned int interrupts = 0;

int main(void){

   if(signal(SIGINT, handleSignals) == SIG_ERR)
   {
           printf("A HandleSignal-t nem sikerult atallitani a SIGINT jelre!\n");
           return 0;
   }

   if(signal(SIGQUIT, handleSignals) == SIG_ERR)
   {
           printf("A HandleSignal-t nem sikerult SIGQUIT jelre atallitani!\n");
           return 0;
   }

   while (!interrupts)
   {
        printf("Varakozas a signal-ra...\n");
        sleep(5);
   }

   printf("Terminalodas...\n");

   return 0;
}

void handleSignals(int sig){

        switch(sig)
        {
                case SIGINT: 
                {
                        printf("\nSIGINT signal: %d\n", sig);
                        printf("A kovetkezo SIGINT-re (CTRL+C) leall!\n");
                        signal(SIGINT, SIG_DFL);
                        break;
                }

                case SIGQUIT: 
                {
                        printf("SIGQUIT signal: %d\n", sig);
                        interrupts = 1;
                        break;
                }
        }
}