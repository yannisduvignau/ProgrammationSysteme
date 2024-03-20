/*
 * Nom du fichier : TP6_1.1.c
 * Auteur         : Yannis DUVIGNAU
 * Description    : Implémentation du TP6 - Le problème du coiffeur endormi
 * Date           : 01/12/2023
*/

//Avec des threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Définition du nombre initial de chaises dans le salon
int N_CHAISES = 3;

// Déclaration d'un mutex pour protéger l'accès aux ressources partagées
pthread_mutex_t mutex_chaises = PTHREAD_MUTEX_INITIALIZER;

// Variables partagées entre les threads
int chaises_disponibles = 3;

// Fonction représentant la coiffure du client
void coiffer_client() {
    // Libération de la chaise après la coiffure
    chaises_disponibles++;
    printf(">   Le client s'installe sur le fauteuil.\n");
    printf(">   Le coiffeur commence a coiffer un client.\n");
    sleep(5);
    printf("<   Le coiffeur termine de coiffer le client.\n");
}

// Fonction représentant l'accueil et l'arrivée d'un client
void accueillir_client() {
    // Vérification de la disponibilité des chaises
    if (chaises_disponibles != 0) {
        printf("\nUn client s'installe sur une chaise.\n\n");
        chaises_disponibles--;
        
        // Utilisation du mutex pour protéger l'accès à la ressource partagée
        pthread_mutex_lock(&mutex_chaises);
        
        // Appel à la fonction de coiffure
        coiffer_client();
        
        // Libération du mutex
        pthread_mutex_unlock(&mutex_chaises);
    } else {
        printf("Le client s'en va.\n");
    }
}


int main() {
    // Message indiquant que le coiffeur dort initialement
    printf("Le coiffeur dort.\n");
    
    // Génération d'un nombre aléatoire de clients
    int nb_client = rand() % 5 + 1;
    
    // Message indiquant combien de client vont arriver pour la vérification
    printf("Nombre de clients qui vont arriver : %d\n", nb_client);

    // Tableau de threads représentant les clients
    pthread_t clients_threads[nb_client];

    // Boucle pour la création des threads clients
    for (int i = 0; i < nb_client; ++i) {
        pthread_create(&clients_threads[i], NULL, (void *)accueillir_client, NULL);
        int temps_attente = rand() % 5 + 1;
        sleep(temps_attente);
    }

    // Boucle pour attendre la fin de tous les threads clients
    for (int i = 0; i < nb_client; ++i) {
        pthread_join(clients_threads[i], NULL);
    }

    // Message indiquant que le coiffeur se rendort
    printf("Le coiffeur se rendort.\n");
    
    // Attente pour permettre aux threads de terminer
    sleep(7);

    return 0;
}