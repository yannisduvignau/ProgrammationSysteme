/*
 * Nom du fichier : TP6_1.2.c
 * Auteur         : Yannis DUVIGNAU
 * Description    : Implémentation du TP6 - Le problème du coiffeur endormi
 * Date           : 01/12/2023
*/

//Avec des processus
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Définition du nombre initial de chaises dans le salon
int N_CHAISES = 3;

// Variables partagées entre les processus
int chaises_disponibles = 3;

// Variable pour indiquer si le coiffeur est occupé
int coiffeur_occupe = 0;

// Fonction représentant la coiffure du client
void coiffer_client() {
    printf(">   Le client s'installe sur le fauteuil.\n");
    printf(">   Le coiffeur commence à coiffer un client.\n");
    sleep(5);
    printf("<   Le coiffeur termine de coiffer le client.\n");
}

// Fonction représentant l'accueil et l'arrivée d'un client
void accueillir_client(int signum) {
    if (chaises_disponibles != 0 && !coiffeur_occupe) {
        printf("\nUn client s'installe sur une chaise.\n\n");
        chaises_disponibles--;

        // Notifier le coiffeur qu'un client est prêt
        kill(getppid(), SIGUSR1);

        // Attendre que le coiffeur confirme la disponibilité
        while (coiffeur_occupe) {
            sleep(1);
        }

        // Appel à la fonction de coiffure
        coiffer_client();

        // Libération du coiffeur en signalant que la coiffure est terminée
        kill(getppid(), SIGUSR2);

    } else {
        printf("Le client s'en va.\n");
    }
}

// Gestionnaire de signal pour le coiffeur
void handler_coiffeur(int signum) {
    if (signum == SIGUSR1) {
        // Le coiffeur est notifié qu'un client est prêt
        coiffeur_occupe = 1;
    } else if (signum == SIGUSR2) {
        // Le coiffeur est notifié que la coiffure est terminée
        coiffeur_occupe = 0;
    }
}

int main() {
    // Installation des gestionnaires de signal pour le coiffeur
    signal(SIGUSR1, handler_coiffeur);
    signal(SIGUSR2, handler_coiffeur);

    // Message indiquant que le coiffeur dort initialement
    printf("Le coiffeur dort.\n");

    // Génération d'un nombre aléatoire de clients
    int nb_clients = rand() % 5 + 1;

    // Message indiquant combien de clients vont arriver pour la vérification
    printf("Nombre de clients qui vont arriver : %d\n", nb_clients);

    // Boucle pour la création des processus clients
    for (int i = 0; i < nb_clients; ++i) {
        pid_t pid_client = fork();

        if (pid_client == 0) {
            // Processus enfant (client)
            // Attente aléatoire avant d'arriver
            int temps_attente = rand() % 5 + 1;
            sleep(temps_attente);

            // Accueil du client
            accueillir_client(0);

            exit(0);
        } else if (pid_client < 0) {
            perror("Erreur lors de la création d'un processus client");
            exit(EXIT_FAILURE);
        }
    }

    // Attendre la fin de tous les processus clients
    for (int i = 0; i < nb_clients; ++i) {
        wait(NULL);
    }

    // Message indiquant que le coiffeur se rendort
    printf("Le coiffeur se rendort.\n");

    return 0;
}


