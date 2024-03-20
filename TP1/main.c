#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    //  Exercice 1
    pid_t numProcs = getpid();
    pid_t numProcsPere = getppid();

    printf("Je suis le processus numéro %d\n", numProcs);

    int var = fork();

    numProcs = getpid();
    numProcsPere = getppid();

    printf("Fork m'a renvoyé la valeur : %d\n", var);

    printf("Je suis le processus numéro %d et mon père est le processus numéro %d\n", numProcs, numProcsPere);
    /*
    Question :
    5 affichages
    Le père et le fils
    */

    /*  Exercice 2 */
    /*pid_t numProcPere = getpid();
    pid_t numProcFils = getppid();

    pid_t id = fork();
    switch(id) {
    case -1 :
            printf("Impossible de créer un processus fils\n");
            exit(EXIT_FAILURE);
            break;
    case 0 :
            for(int i = 0; i < 10; i++)
            {
                printf("Processus fils n°%d -> Valeur n°%d : %d\n", getpid(), i+1, 2*i);
            }
        break;
    default :
            for(int i = 1; i <= 10; i++)
            {
                printf("Processus père n°%d -> Valeur n°%d : %d\n", getpid(), i, 2*i + 1);
            }
        break;
    }*/
    return 0;
}
