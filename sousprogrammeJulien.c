#include "header.h"

// Fonction pour lire les opérations depuis le fichier
Operation* lireOperations() {
    char* nomFichier = "temps_cycle.txt";
    FILE* fichier = ouvrirFichier(nomFichier);

    int numOperation;
    float executionTime;
    Operation* operations = NULL;

    // Compter le nombre d'opérations dans le fichier
    int nombreOperations = 0;
    while (fscanf(fichier, "%d %f", &numOperation, &executionTime) == 2) {
        (nombreOperations)++;
    }

    // Allouer de la mémoire pour le tableau d'opérations
    operations = (Operation*)malloc(nombreOperations * sizeof(Operation));

    // Revenir au début du fichier
    fseek(fichier, 0, SEEK_SET);

    // Lire les opérations et les enregistrer dans le tableau
    for (int i = 0; i < nombreOperations; ++i) {
        fscanf(fichier, "%d %f", &((operations)[i].numOperation), &((operations)[i].executionTime));
    }

    fclose(fichier);

    return operations;
}


float lireTempsDeCycle() {
    char* nomFichier = "operations.txt";
    FILE* fichier = ouvrirFichier(nomFichier);

    float tempsCycle;
    fscanf(fichier, "%f", &tempsCycle);

    fclose(fichier);
    return tempsCycle;
}