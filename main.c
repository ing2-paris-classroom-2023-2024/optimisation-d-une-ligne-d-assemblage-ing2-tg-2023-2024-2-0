#include "header.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_OPERATIONS 35
#define MAX_CONSTRAINTS 100

// Structure représentant le problème d'affectation
struct AssignmentProblem {
    int stations[NUM_OPERATIONS];
    struct ExclusionConstraint {
        int operation1;
        int operation2;
    } exclusionConstraints[MAX_CONSTRAINTS];
    int numConstraints;
};

// Initialise toutes les stations à zéro
void initialisation_stations(int *stations) {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        stations[i] = 0;
    }
}

// Compte le nombre de stations distinctes utilisées
int nbr_stations(const int *stations) {
    int uniqueStations[NUM_OPERATIONS] = {0};
    int count = 0;

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int station = stations[i];

        if (station != 0 && uniqueStations[station - 1] == 0) {
            uniqueStations[station - 1] = 1;
            count++;
        }
    }

    return count;
}

// Vérifie si une affectation est valide en tenant compte des contraintes d'exclusion
int affectation_valide(const int *stations, const struct ExclusionConstraint *constraints, int numConstraints, int currentOperation, int currentStation) {
    for (int i = 0; i < numConstraints; ++i) {
        if ((currentOperation + 1 == constraints[i].operation1 && stations[constraints[i].operation2 - 1] == currentStation) ||
            (currentOperation + 1 == constraints[i].operation2 && stations[constraints[i].operation1 - 1] == currentStation)) {
            return 0; // Affectation invalide
        }
    }

    return 1; // Affectation valide
}

// Trouve la station avec le minimum de conflits pour une opération donnée
int station_min_conflit(const int *stations, const struct ExclusionConstraint *constraints, int numConstraints, int currentOperation) {
    int minConflicts = NUM_OPERATIONS + 1; // Initialisation du nombre minimum de conflits
    int minConflictStation = 1; // Initialisation de la station avec le minimum de conflits

    for (int currentStation = 1; currentStation <= NUM_OPERATIONS; ++currentStation) {
        if (affectation_valide(stations, constraints, numConstraints, currentOperation, currentStation)) {
            int conflicts = 0; // Compteur de conflits pour la station actuelle

            // Parcours des contraintes pour compter les conflits
            for (int i = 0; i < numConstraints; ++i) {
                if ((currentOperation + 1 == constraints[i].operation1 && stations[constraints[i].operation2 - 1] == currentStation) ||
                    (currentOperation + 1 == constraints[i].operation2 && stations[constraints[i].operation1 - 1] == currentStation)) {
                    conflicts++;
                }
            }

            // Mise à jour de la station minimisant le nombre de conflits
            if (conflicts < minConflicts) {
                minConflicts = conflicts;
                minConflictStation = currentStation;
            }
        }
    }

    return minConflictStation;
}

// Résout le problème d'affectation
void probleme_affectation(struct AssignmentProblem *problem) {
    initialisation_stations(problem->stations);

    // Ouverture du fichier contenant les contraintes
    FILE *file = fopen("exclusions.txt", "r");

    // Vérifie si l'ouverture du fichier a réussi
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Lecture des contraintes depuis le fichier
    while (fscanf(file, "%d %d", &problem->exclusionConstraints[problem->numConstraints].operation1,
                  &problem->exclusionConstraints[problem->numConstraints].operation2) == 2) {
        problem->numConstraints++;

        // Vérifie si le nombre de contraintes dépasse la limite
        if (problem->numConstraints >= MAX_CONSTRAINTS) {
            printf("Trop de contraintes, ajustez la taille du tableau.\n");
            exit(1);
        }
    }

    // Ferme le fichier après lecture
    fclose(file);

    // Affectation des opérations aux stations
    for (int currentOperation = 0; currentOperation < NUM_OPERATIONS; ++currentOperation) {
        int minConflictStation = station_min_conflit(problem->stations, problem->exclusionConstraints, problem->numConstraints, currentOperation);
        problem->stations[currentOperation] = minConflictStation;
    }

    // Affichage des résultats
    printf("Affectation des operations aux stations :\n");
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        printf("Operation %d -> Station %d\n", i + 1, problem->stations[i]);
    }

    printf("Nombre de stations utilisees : %d\n", nbr_stations(problem->stations));
}

// Fonction principale
int main() {
    // Crée une instance de la structure AssignmentProblem
    struct AssignmentProblem problem;

    // Résout le problème d'affectation
    probleme_affectation(&problem);

       return 0;
}
