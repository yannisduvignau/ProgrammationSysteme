/*
 * Nom du fichier : TP6_2.1.c
 * Auteur         : Yannis DUVIGNAU
 * Description    : Implémentation du TP6 - Le problème du Rendez-vous
 * Date           : 03/12/2023
*/


//--------------------------------//
//   Question 1 - "Rendez-vous"   //
//--------------------------------//

// Avec des threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PERSONS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int personsArrived = 0;
int personsLeft = 0;

typedef struct {
    int id;
    int left;
    int duration;
} Person;

void *attendMeeting(void *arg) {
    Person *person = (Person *)arg;

    // Simuler le temps d'arrivée de la personne
    sleep(4);  // Augmenté le temps entre les arrivées pour mieux observer le départ et le retour

    pthread_mutex_lock(&mutex); // Verrouiller la section critique

    printf("Personne %d est arrivee.\n", person->id);
    personsArrived++;

    pthread_mutex_unlock(&mutex); // Déverrouiller la section critique

    // Simuler l'attente de l'arrivée de tous les membres
    sleep(5); // Peut être ajusté selon vos besoins

    pthread_mutex_lock(&mutex); // Verrouiller la section critique

    // Une personne a 50% de chance de partir pour revenir plus tard
    if (rand() % 2 == 0) {
        person->left = 1;
        printf("Personne %d est partie.\n", person->id);
        personsLeft++;
        pthread_mutex_unlock(&mutex); // Déverrouiller la section critique
        // Simuler la durée pendant laquelle la personne est partie
        sleep(5);
        person->duration += 5;
        pthread_mutex_lock(&mutex); // Verrouiller la section critique
        printf("Personne %d est revenue apres avoir quitte pendant %d secondes.\n", person->id, person->duration);
    }

    pthread_mutex_unlock(&mutex); // Déverrouiller la section critique

    pthread_exit(NULL);
}

int main() {
    int i;
    Person persons[MAX_PERSONS];
    pthread_t threads[MAX_PERSONS];

    for (i = 0; i < MAX_PERSONS; i++) {
        persons[i].id = i + 1;
        persons[i].left = 0;
        persons[i].duration = 0;
        pthread_create(&threads[i], NULL, attendMeeting, &persons[i]);
        // Ajout d'un délai entre les créations de threads pour mieux observer le départ et le retour
        sleep(2);
    }

    // Attendre que tous les threads se terminent
    for (i = 0; i < MAX_PERSONS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Détruire le mutex

    return 0;
}

