#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generer_csv(const char *nom_fichier, int max1, int max2)
{
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        perror("Erreur ouverture fichier");
        return;
    }

    // Initialisation du générateur aléatoire
    srand(time(NULL));

    for (int i = 0; i < 100; i++)
    {
        int val1 = rand() % (max1 + 1);
        int val2 = rand() % (max2 + 1);

        // Deux colonnes remplies, puis colonnes vides
        fprintf(f, "%d,%d,,,\n", val1, val2);
    }

    fclose(f);
}

int main()
{
    generer_csv("test.csv", 50, 100);
    return 0;
}
