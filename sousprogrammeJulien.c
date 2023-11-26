#include "header.h"

// Fonction pour lire le temps de cycle
float lireTempsDeCycle() {
    char* nomFichier = "temps_cycle.txt";
    FILE* fichier = ouvrirFichier(nomFichier);

    float tempsCycle;
    fscanf(fichier, "%f", &tempsCycle);

    fclose(fichier);
    return tempsCycle;
}

// Fonction pour lire les opérations depuis le fichier
Operation* lireOperations(int *nombreOperations) {
    char* nomFichier = "operations.txt";
    FILE* fichier = ouvrirFichier(nomFichier);

    int numOperation;
    float executionTime;
    Operation* operations = NULL;

    // Compter le nombre d'opérations dans le fichier
    while (fscanf(fichier, "%d %f", &numOperation, &executionTime) == 2) {
        (*nombreOperations)++;
    }

    // Allouer de la mémoire pour le tableau d'opérations
    operations = (Operation*)malloc(*nombreOperations * sizeof(Operation));

    // Revenir au début du fichier
    fseek(fichier, 0, SEEK_SET);

    // Lire les opérations et les enregistrer dans le tableau
    for (int i = 0; i < *nombreOperations; ++i) {
        fscanf(fichier, "%d %f", &((operations)[i].numOperation), &((operations)[i].executionTime));
    }

    fclose(fichier);

    return operations;
}


// Fonction pour trier les opérations par ordre croissant en fonction de leur temps d'exécution
void trierOperations(Operation* operations, int nombreOperations) {
    for (int i = 1; i < nombreOperations; ++i) {
        Operation cle = operations[i];
        int j = i - 1;

        // Déplacer les éléments de la partie triée du tableau qui sont plus grands que la clé
        while (j >= 0 && operations[j].executionTime > cle.executionTime) {
            operations[j + 1] = operations[j];
            j = j - 1;
        }
        operations[j + 1] = cle;
    }
}

// Fonction pour afficher les opérations triées
void afficherOperations(Operation* operations, int nombreOperations) {
    printf("Opérations triées par ordre croissant d'exécution :\n");
    for (int i = 0; i < nombreOperations; ++i) {
        printf("Numéro d'opération : %d, Temps d'exécution : %.2f\n", operations[i].numOperation, operations[i].executionTime);
    }
}



// Fonction pour créer des tâches à partir des opérations
Tache* creerTaches(Operation* operations, int nombreOperations, int* nombreTaches) {
    float tempsCycle = lireTempsDeCycle();  // Temps maximum pour une tâche (en secondes)
    float tempsTotal = 0.0;  // Temps total actuel de la tâche
    int numeroTache = 0;  // Numéro de la tâche en cours
    int indexOperation = 0;  // Index de l'opération en cours

    Tache* taches = NULL;

    while (indexOperation < nombreOperations) {
        // Créer une nouvelle tâche
        taches = (Tache*)realloc(taches, (*nombreTaches + 1) * sizeof(Tache));
        taches[*nombreTaches].numeroTache = numeroTache;
        taches[*nombreTaches].nombreOperations = 0;
        taches[*nombreTaches].operations = NULL;

        // Ajouter des opérations à la tâche jusqu'à atteindre 10 secondes
        while (indexOperation < nombreOperations && tempsTotal + operations[indexOperation].executionTime <= tempsCycle) {
            // Ajouter l'opération à la tâche
            taches[*nombreTaches].operations = (Operation*)realloc(taches[*nombreTaches].operations, (taches[*nombreTaches].nombreOperations + 1) * sizeof(Operation));
            taches[*nombreTaches].operations[taches[*nombreTaches].nombreOperations] = operations[indexOperation];
            taches[*nombreTaches].nombreOperations++;

            // Mettre à jour le temps total de la tâche
            tempsTotal += operations[indexOperation].executionTime;

            // Passer à l'opération suivante
            indexOperation++;
        }

        // Réinitialiser le temps total pour la prochaine tâche
        tempsTotal = 0.0;
        // Passer à la prochaine tâche
        (*nombreTaches)++;
        numeroTache++;
    }

    return taches;
}

// Fonction pour afficher les tâches
void afficherTaches(Tache* taches, int nombreTaches) {
    printf("Tâches créées :\n");
    for (int i = 0; i < nombreTaches; ++i) {
        printf("Tâche %d :\n", taches[i].numeroTache);
        for (int j = 0; j < taches[i].nombreOperations; ++j) {
            printf("    Numéro d'opération : %d, Temps d'exécution : %.2f\n", taches[i].operations[j].numOperation, taches[i].operations[j].executionTime);
        }
        printf("---- Fin de la tâche ----\n");
    }
}



/*
    -----------------A mettre dans le main------------------
    int nombreOperations = 0;
    Operation* operations = lireOperations(&nombreOperations);

    // Triez les opérations par ordre croissant en fonction de leur temps d'exécution
    trierOperations(operations, nombreOperations);

    // Afficher les opérations triées
    afficherOperations(operations, nombreOperations);

    // Créer des tâches à partir des opérations triées
    int nombreTaches = 0;
    Tache* taches = creerTaches(operations, nombreOperations, &nombreTaches);

    // Afficher les tâches créées
    afficherTaches(taches, nombreTaches);

    // Libérer la mémoire allouée
    free(operations);
    for (int i = 0; i < nombreTaches; ++i) {
        free(taches[i].operations);
    }
    free(taches);

    return 0;
*/
