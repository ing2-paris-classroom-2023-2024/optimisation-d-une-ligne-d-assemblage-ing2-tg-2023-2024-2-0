#include "header.h"

int main(){

    ////////////////Sous Programme Julien/////////////////
    int nombreOperations = 0;
    Operation* operations = lireOperations(&nombreOperations);

    // Triez les opérations par ordre croissant en fonction de leur temps d'exécution
    trierOperations(operations, nombreOperations);

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

////////////////Sous Programme Gabriel/////////////////
    algorithemPertsanspoids();

//////////////////Sous Programme Maxime/////////
    struct AssignmentProblem problem;
    probleme_affectation(&problem);
    return 0;
}
