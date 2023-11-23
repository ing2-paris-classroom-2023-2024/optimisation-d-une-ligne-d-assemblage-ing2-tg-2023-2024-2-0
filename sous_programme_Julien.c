//
// Created by Julien Bitschenaux--Durand on 23/11/2023.
//

#include "header.h"

FILE* ouvrirFichier(char* nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    return fichier;
}

void algoTempsdeCycle(){
    char* nomFichier = "temps_cycle.txt";

    FILE* fichier = ouvrirFichier(nomFichier);




}