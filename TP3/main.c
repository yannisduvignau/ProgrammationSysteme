#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//Déclaration et initialisation du mutex
unsigned long cpt = 0;

void compteur(){
    pthread_mutex_lock(&mutex);//entre en section critique (blocage)

    //TRAITEMENT ALGORITHME
    unsigned long tmp = 0;
    for (long i = 0; i < 100000000; i++)
    {
        tmp = cpt;
        tmp ++;
        cpt = tmp;
    }
    printf("Valeur finale du compteur = %lu\n",cpt);

    pthread_mutex_unlock(&mutex);//sorti de section critique (déblocage)
}

int main()
{
    //Stocker le temps d'éxecution du code
    double time_spent = 0.0;

    clock_t begin = clock();//Démarrer le temps

    //DEFINITION VARIABLE
    pthread_attr_t attr;
    pthread_t thread_id1,thread_id2;

    pthread_attr_init(&attr);
    pthread_create(&thread_id1,&attr,(void *)compteur,NULL);
    pthread_create(&thread_id2,&attr,(void *)compteur,NULL);

    pthread_join(thread_id1,NULL);
    pthread_join(thread_id2,NULL);
    
    pthread_mutex_destroy(&mutex);
    
    clock_t end = clock();//arreter le temps
    //Calcul du temps (end-begin)
    time_spent += (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Le temps d'execution du programme est de : %f seconde",time_spent);

    return 0;
}
