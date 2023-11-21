#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H


//Programme Gabriel 1.2

typedef struct Noeud {
    int sommet;
    struct Noeud* suivant;
} Noeud;

typedef struct Graphe {
    int nbsommet;
    Noeud** listeAdjacence;
} Graphe;

Noeud* creerNoeud(int sommet);
Graphe* creerGraphe(int nbsommet);
FILE* ouvrirFichier(char* nomFichier);
void fermerFichier(FILE* fichier);
void ajouterArete(Graphe* graphe, int src, int dest);
void PredecesseursRecursif(Graphe* graphe, int sommet, int sommetInitial, int visite[]);
void Predecesseurs(Graphe* graphe);
void algorithemPertsanspoids();