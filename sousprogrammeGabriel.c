//
// Created by gabri on 21/11/2023.
//
#include "header.h"



Noeud* creerNoeud(int sommet) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->sommet = sommet;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

Graphe* creerGraphe(int nbsommet) {
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe->nbsommet = nbsommet;
    graphe->listeAdjacence = (Noeud**)malloc(nbsommet * sizeof(Noeud*));

    for (int i = 0; i < nbsommet; ++i) {
        graphe->listeAdjacence[i] = NULL;
    }

    return graphe;
}

FILE* ouvrirFichier(char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    return fichier;
}

void fermerFichier(FILE* fichier) {
    fclose(fichier);
}


void ajouterArete(Graphe* graphe, int depart, int arrive) {
    // Ajouter l'arc dest -> src (inverse de la direction)
    Noeud* nouveauNoeud = creerNoeud(depart);
    nouveauNoeud->suivant = graphe->listeAdjacence[arrive];
    graphe->listeAdjacence[arrive] = nouveauNoeud;
}

void PredecesseursRecursif(Graphe* graphe, int sommet, int sommetInitial, int visite[]) {
    visite[sommet] = 1;

    // Liste des prédécesseurs pour le sommet courant
    if (sommet != sommetInitial) {
        printf("%d ", sommet + 1);
    }

    Noeud* courant = graphe->listeAdjacence[sommet];
    while (courant != NULL) {
        if (!visite[courant->sommet]) {
            PredecesseursRecursif(graphe, courant->sommet, sommetInitial, visite);
        }
        courant = courant->suivant;
    }

    // Liste des prédécesseurs des prédécesseurs
    if (sommet != sommetInitial) {
        Noeud* noeudPred = graphe->listeAdjacence[sommet];
        while (noeudPred != NULL) {
            if (!visite[noeudPred->sommet]) {
                PredecesseursRecursif(graphe, noeudPred->sommet, sommetInitial, visite);
            }
            noeudPred = noeudPred->suivant;
        }
    }
}

void Predecesseurs(Graphe* graphe) {
    int visite[graphe->nbsommet];

    for (int i = 0; i < graphe->nbsommet; ++i) {
        printf("Sommet %d : ", i + 1);
        for (int j = 0; j < graphe->nbsommet; ++j) {
            visite[j] = 0;
        }
        PredecesseursRecursif(graphe, i, i, visite);
        printf("\n");
    }
}


int totalaretes (char *nomFichier){
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int nombre;
    int totalaretes = 0;
    // Lire chaque caractère du fichier
    while ((nombre = fgetc(fichier)) != EOF) {
        // Si le caractère est un saut de ligne, incrémenter le compteur de lignes
        if (nombre == '\n') {
            totalaretes++;
        }
    }

    // Fermer le fichier
    fclose(fichier);


    return totalaretes; // Retourne le nombre total d'aretes
}


int totalSommet(char *nomFichier,int totalaretes){
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int nombretest = 0;
    for (int i = 0; i < totalaretes; ++i) {
        int depart, arrive;
        if (fscanf(fichier, "%d %d", &depart, &arrive) == 2) {
            if (nombretest<depart){
                nombretest=depart;
            }
            if (nombretest<arrive){
                nombretest=arrive;
            }
        } else {
            printf("Erreur de lecture de l'arc %d\n", i + 1);
        }
    }
    fclose(fichier);

    return nombretest;
}


void algorithemPertsanspoids() {
    char* nomFichier = "algo_gab.txt";

    FILE* fichier = ouvrirFichier(nomFichier);

    //trouver le moyen de voir le nombre d'arrete sans l'imposer
    int nbAretes= totalaretes(nomFichier);

    //Trouver le moyen de prendre ce nombre sans l'imposer
    int totalSommets = totalSommet(nomFichier,nbAretes);
    Graphe* graphe = creerGraphe(totalSommets);




    printf("Nombre d'aretes : %d\n", nbAretes);
    printf("Nombre sommets : %d\n", totalSommets);

    for (int i = 0; i < nbAretes; ++i) {
        int depart, arrive;
        if (fscanf(fichier, "%d %d", &depart, &arrive) == 2) {
            ajouterArete(graphe, depart - 1, arrive - 1);
        } else {
            printf("Erreur de lecture de l'arc %d\n", i + 1);
        }
    }

    printf("\nAffichage des predecesseurs :\n");
    Predecesseurs(graphe);

    fermerFichier(fichier);
}


