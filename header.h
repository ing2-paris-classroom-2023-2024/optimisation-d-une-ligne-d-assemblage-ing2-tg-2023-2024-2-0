#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_OPERATIONS 35
#define MAX_CONSTRAINTS 100

/////////////////////////////////////////////Programme Gabriel 1.2//////////////////////////////////////////////////////
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
int totalaretes (char *nomFichier);
int totalSommet(char *nomFichier,int totalaretes);


////////////////////////////////Programme Maxime//////////////////////////////
struct AssignmentProblem {
    int stations[NUM_OPERATIONS];
    struct ExclusionConstraint {
        int operation1;
        int operation2;
    } exclusionConstraints[MAX_CONSTRAINTS];
    int numConstraints;
};

void initialisation_stations(struct AssignmentProblem *problem);
int nbr_stations(const int *stations);
int affectation_valide(const int *stations, const struct ExclusionConstraint *constraints, int numConstraints, int currentOperation, int currentStation);
int station_min_conflit(const int *stations, const struct ExclusionConstraint *constraints, int numConstraints, int currentOperation);
void probleme_affectation(struct AssignmentProblem *problem);

////////////////////////////////Programme Julien//////////////////////////////

// Structure pour représenter une opération
typedef struct {
    int numOperation;
    float executionTime;
} Operation;

// Structure pour représenter une tâche
typedef struct {
    int numeroTache;
    Operation* operations;
    int nombreOperations;
} Tache;

Operation* lireOperations(int *nombreOperations);
void trierOperations(Operation* operations, int nombreOperations);
void afficherOperations(Operation* operations, int nombreOperations);
Tache* creerTaches(Operation* operations, int nombreOperations, int* nombreTaches);
void afficherTaches(Tache* taches, int nombreTaches);
float lireTempsDeCycle();

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_2_0_HEADER_H