#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void thread1(){
    setbuf(stdout,NULL);
    while(1)
    {
        printf(".\n");
        sleep(1);
    }
}

void thread2(){
    printf("Tapez un caractère\n");
    getchar();
    printf("Fin du thread 2\n");
}

int main()
{
    pthread_attr_t attr;
    pthread_t id1, id2;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&id1, &attr, (void *)thread1, NULL);
    pthread_create(&id2, &attr, (void *)thread2, NULL);

    printf("Les 2 threads sont lances.\n");

    pthread_join(id2, NULL);

    printf("On va s'arreter la\n");

    return 0;
}

/*
    1. Ne marche pas

    2. Fonctionne comme attendu car join suspend l'exécution du thread jusqu'à exécution

    3. Affiche tout mais ne fonctionne pas pour l'arret

    4. Join ne marche plus
*/
