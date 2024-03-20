#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    int tube[2];// tube avec 2 descripteur
    char caractere;
    int pipe(int tube[2]);
    if(pipe(tube) == -1){
        printf("Création du tube impossible\n");
        exit(EXIT_FAILURE);
    }
    
    pid_t id;
    id = fork();

    switch (id)
    {
    case -1:
        printf("fork error\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        //Ce que fait seulement le prossessus fils
        close(tube[1]);

        read(tube[0], &caractere, sizeof(char));
        if (caractere == '$')
        {
            printf("Fin programme\n");
            exit(EXIT_SUCCESS);
        }
        close(tube[0]);   
        break;
    
    default:
        //Ce que fait seulement le prossessus père
        close(tube[0]);

        while (caractere!='$')
        {
            printf("Saisie un caractere : ");
            caractere = getchar();
            write(tube[1], &caractere, sizeof(char));
            break;
        }
        close(tube[1]);      
    }



    return 0;
}
