#include "TP1Functions.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>

// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

int read_TP1_instance(FILE*fin, dataSet* dsptr)
{
	int rval = 0;

	// Capacité b et nombre d'objets n
	int b, n;
	rval = fscanf(fin, "%d,%d\n", &n, &b);
	dsptr->b = b;
	dsptr->n = n;
	dsptr->c = (int*)malloc(sizeof(int)*n);
	dsptr->a = (int*)malloc(sizeof(int)*n);

	int i;
	for(i = 0; i < n; i++)
		rval = fscanf(fin, "%d,%d\n", &(dsptr->c[i]), &(dsptr->a[i]));

	fprintf(stderr, "\nInstance file read, we have capacity %d and there is %d items of values/weights:\n", b, n);
	for(i = 0; i < n; i++)
		fprintf(stderr, "%d,%d\n", dsptr->c[i], dsptr->a[i]);
	fprintf(stderr, "\n");

	return rval;
}

void printIntArray(int tab[], int n)
{
	printf("[ ");
	for(int i = 0; i < n; i++) {
		printf("%d ", tab[i]);
	}
	printf("]\n");
}

void printFloatArray(float tab[], int n)
{
	printf("[ ");
	for(int i = 0; i < n; i++) {
		printf("%.2f ", tab[i]);
	}
	printf("]\n");
}

float minFloat(float a, float b)
{
	return (a <= b) ? a : b;
}

float maxFloat(float a, float b)
{
	return (a >= b) ? a : b;
}

int maxInt(int a, int b)
{
	return (a >= b) ? a : b;
}

// Tri des objets par ratio décroissant c[i]/a[i]
void sortByRatio(int values[], int weights[], int n)
{
	float tempValue, tempWeight, tempRatio;
	float ratio[n];
	
	// Calcul des ratios
	for(int i = 0; i < n; i++) {
		ratio[i] = (float)values[i] / (float)weights[i];
	}

	// Tri à bulles basé sur le ratio (décroissant)
	for(int i = 0; i < n - 1; i++) {
		for(int j = 0; j < n - i - 1; j++) {
			if(ratio[j] < ratio[j + 1]) {
				// Échanger les ratios
				tempRatio = ratio[j];
				ratio[j] = ratio[j + 1];
				ratio[j + 1] = tempRatio;

				// Échanger les valeurs
				tempValue = values[j];
				values[j] = values[j + 1];
				values[j + 1] = tempValue;

				// Échanger les poids
				tempWeight = weights[j];
				weights[j] = weights[j + 1];
				weights[j + 1] = tempWeight;
			}
		}
	}
}

// ============================================================================
// TP1 - ALGORITHME GLOUTON (GREEDY)
// ============================================================================

int KP_Greedy(dataSet* dsptr)
{
	int objective_value = 0;
	int remaining_capacity = dsptr->b;
	int num_items = dsptr->n;
	
	// Allocation de la solution
	dsptr->s = (float*)malloc(sizeof(float) * num_items);
	for(int i = 0; i < num_items; i++) {
		dsptr->s[i] = 0;
	}

	// Tri par ratio décroissant
	sortByRatio(dsptr->c, dsptr->a, num_items);

	// Algorithme glouton
	for(int i = 0; i < num_items; i++) {
		if(remaining_capacity == 0) {
			break;
		}
		if(remaining_capacity >= dsptr->a[i]) {
			dsptr->s[i] = 1;
			remaining_capacity -= dsptr->a[i];
			objective_value += dsptr->c[i];
		}
	}

	printf("Solution KP_Greedy : %d\n", objective_value);
	dsptr->z_greedy = objective_value;
	return objective_value;
}

// ============================================================================
// TP1 - RELAXATION LINÉAIRE (LP)
// ============================================================================

int KP_LP(dataSet* dsptr)
{
	float objective_value = 0;
	int remaining_capacity = dsptr->b;
	int num_items = dsptr->n;
	
	// Allocation de la solution
	dsptr->s = (float*)malloc(sizeof(float) * num_items);
	for(int i = 0; i < num_items; i++) {
		dsptr->s[i] = 0;
	}

	// Tri par ratio décroissant
	sortByRatio(dsptr->c, dsptr->a, num_items);

	// Relaxation linéaire
	for(int i = 0; i < num_items; i++) {
		if(remaining_capacity == 0) {
			break;
		}
		dsptr->s[i] = minFloat((float)remaining_capacity / (float)dsptr->a[i], 1.0);
		remaining_capacity = remaining_capacity - (int)(dsptr->s[i] * dsptr->a[i]);
		objective_value += dsptr->s[i] * dsptr->c[i];
	}

	printf("Solution KP_LP (relaxation linéaire) : %.2f\n", objective_value);
	dsptr->z_bar = objective_value;
	return (int)objective_value;
}

// ============================================================================
// TP2 - PROGRAMMATION DYNAMIQUE (DYNAMIC PROGRAMMING)
// ============================================================================

int KP_DynamicProgramming(dataSet* dsptr)
{
	int objective_value = 0;
	int capacity = dsptr->b;
	int num_items = dsptr->n;
	
	// Allocation de la solution
	dsptr->s = (float*)malloc(sizeof(float) * num_items);

	// Tableaux Z et D : taille (capacity + 1) pour indices 0 à b
	int* Z = (int*)calloc(capacity + 1, sizeof(int));
	int* Z_temp = (int*)calloc(capacity + 1, sizeof(int));
	int* D = (int*)calloc(capacity + 1, sizeof(int));

	// Initialisation
	for(int y = 0; y <= capacity; y++) {
		Z[y] = 0;
		D[y] = 0;
	}

	// Tri par ratio décroissant
	sortByRatio(dsptr->c, dsptr->a, num_items);

	// Programmation dynamique
	for(int k = 0; k < num_items; k++) {
		// Copier Z dans Z_temp
		for(int y = 0; y <= capacity; y++) {
			Z_temp[y] = Z[y];
		}

		// Mise à jour de Z et D
		for(int y = dsptr->a[k]; y <= capacity; y++) {
			if(Z_temp[y - dsptr->a[k]] + dsptr->c[k] > Z_temp[y]) {
				D[y] = k;
				Z[y] = Z_temp[y - dsptr->a[k]] + dsptr->c[k];
			}
		}
	}

	printf("Z = ");
	printIntArray(Z, capacity + 1);
	printf("D = ");
	printIntArray(D, capacity + 1);

	// Initialiser la solution à 0
	for(int j = 0; j < num_items; j++) {
		dsptr->s[j] = 0;
	}

	// Reconstruction de la solution optimale
	int y = capacity;
	while(y > 0) {
		while(y > 0 && Z[y] == Z[y - 1]) {
			y--;
		}
		if(y > 0) {
			dsptr->s[D[y]] = 1;
			y -= dsptr->a[D[y]];
		}
	}

	printf("Solution optimale x* = ");
	printFloatArray(dsptr->s, num_items);

	// Calcul de la valeur objectif
	for(int i = 0; i < num_items; i++) {
		objective_value += dsptr->s[i] * dsptr->c[i];
	}

	printf("Valeur optimale KP_DynamicProgramming : %d\n", objective_value);

	free(Z);
	free(Z_temp);
	free(D);

	return objective_value;
}

// ============================================================================
// TP3 - PREPROCESSING / RÉDUCTION
// ============================================================================

int KP_Preprocessing(dataSet* dsptr)
{
	printf("\n========== PREPROCESSING (TP3) ==========\n");
	
	int num_items = dsptr->n;
	int capacity = dsptr->b;
	int original_num_items = num_items;
	int original_capacity = capacity;
	
	// Tri par ratio décroissant
	sortByRatio(dsptr->c, dsptr->a, num_items);
	
	// Étape 1: Calculer une solution gloutonne z_tilde
	int z_tilde = 0;
	int temp_capacity = capacity;
	int* x_tilde = (int*)calloc(num_items, sizeof(int));
	
	for(int i = 0; i < num_items; i++) {
		if(temp_capacity >= dsptr->a[i]) {
			x_tilde[i] = 1;
			temp_capacity -= dsptr->a[i];
			z_tilde += dsptr->c[i];
		}
	}
	
	printf("Solution gloutonne z_tilde = %d\n", z_tilde);
	dsptr->z_greedy = z_tilde;
	
	// Étape 2: Calculer la relaxation linéaire z_bar
	float z_bar = 0;
	temp_capacity = capacity;
	
	for(int i = 0; i < num_items; i++) {
		if(temp_capacity == 0) break;
		float fraction = minFloat((float)temp_capacity / (float)dsptr->a[i], 1.0);
		temp_capacity -= (int)(fraction * dsptr->a[i]);
		z_bar += fraction * dsptr->c[i];
	}
	
	printf("Relaxation linéaire z_bar = %.2f\n", z_bar);
	dsptr->z_bar = z_bar;
	
	// Étape 3: Déterminer l'indice p
	int p = 0;
	int sum_weights = 0;
	for(int j = 0; j < num_items; j++) {
		if(sum_weights > capacity) {
			p = j - 1;
			break;
		}
		sum_weights += dsptr->a[j];
		p = j;
	}
	
	printf("Indice critique p = %d\n", p + 1);
	
	// Ratio critique c_p / a_p
	float critical_ratio = (p < num_items) ? (float)dsptr->c[p] / (float)dsptr->a[p] : 0;
	printf("Ratio critique c[%d]/a[%d] = %.2f\n", p, p, critical_ratio);
	
	// Étape 4: Préprocessing des variables
	int num_fixed = 0;
	int num_fixed_to_1 = 0;
	int num_fixed_to_0 = 0;
	float gap = z_bar - z_tilde;
	
	printf("\nGap (z_bar - z_tilde) = %.2f\n", gap);
	printf("\nAnalyse des variables:\n");
	
	for(int j = 0; j < num_items; j++) {
		float c_bar_j = dsptr->c[j] - critical_ratio * dsptr->a[j];
		
		printf("  Item %d: c_bar = %.2f", j, c_bar_j);
		
		if(c_bar_j >= gap) {
			num_fixed++;
			if(j < p) {
				// Fixer à 1
				x_tilde[j] = 1;
				capacity -= dsptr->a[j];
				num_fixed_to_1++;
				printf(" --> FIXÉE À 1\n");
			} else {
				// Fixer à 0
				x_tilde[j] = 0;
				num_fixed_to_0++;
				printf(" --> FIXÉE À 0\n");
			}
		} else {
			printf(" --> LIBRE\n");
		}
	}
	
	printf("\n========== RÉSULTATS DU PREPROCESSING ==========\n");
	printf("Variables fixées à 1: %d\n", num_fixed_to_1);
	printf("Variables fixées à 0: %d\n", num_fixed_to_0);
	printf("Total variables fixées: %d / %d (%.1f%%)\n", 
	       num_fixed, original_num_items, 
	       100.0 * num_fixed / original_num_items);
	printf("Variables restantes: %d\n", original_num_items - num_fixed);
	printf("Capacité restante: %d / %d\n", capacity, original_capacity);
	
	// Créer le problème réduit
	int num_free_vars = 0;
	for(int j = 0; j < num_items; j++) {
		float c_bar_j = dsptr->c[j] - critical_ratio * dsptr->a[j];
		if(c_bar_j < gap) {
			num_free_vars++;
		}
	}
	
	if(num_free_vars > 0) {
		printf("\n==> Résolution du problème réduit par programmation dynamique...\n");
		
		// Créer une nouvelle instance avec seulement les variables libres
		dataSet reduced_problem;
		reduced_problem.n = num_free_vars;
		reduced_problem.b = capacity;
		reduced_problem.c = (int*)malloc(sizeof(int) * num_free_vars);
		reduced_problem.a = (int*)malloc(sizeof(int) * num_free_vars);
		
		int idx = 0;
		int* mapping = (int*)malloc(sizeof(int) * num_free_vars);
		
		for(int j = 0; j < num_items; j++) {
			float c_bar_j = dsptr->c[j] - critical_ratio * dsptr->a[j];
			if(c_bar_j < gap) {
				reduced_problem.c[idx] = dsptr->c[j];
				reduced_problem.a[idx] = dsptr->a[j];
				mapping[idx] = j;
				idx++;
			}
		}
		
		// Résoudre par programmation dynamique
		int reduced_value = KP_DynamicProgramming(&reduced_problem);
		
		// Reconstruire la solution complète
		dsptr->s = (float*)calloc(num_items, sizeof(float));
		
		// Variables fixées
		for(int j = 0; j < num_items; j++) {
			float c_bar_j = dsptr->c[j] - critical_ratio * dsptr->a[j];
			if(c_bar_j >= gap) {
				dsptr->s[j] = x_tilde[j];
			}
		}
		
		// Variables du problème réduit
		for(int i = 0; i < num_free_vars; i++) {
			dsptr->s[mapping[i]] = reduced_problem.s[i];
		}
		
		// Calculer la valeur totale
		int total_value = 0;
		for(int j = 0; j < num_items; j++) {
			total_value += dsptr->s[j] * dsptr->c[j];
		}
		
		printf("\nValeur optimale FINALE avec preprocessing: %d\n", total_value);
		
		free(reduced_problem.c);
		free(reduced_problem.a);
		free(reduced_problem.s);
		free(mapping);
		
		return total_value;
	} else {
		printf("\n==> Toutes les variables sont fixées !\n");
		
		dsptr->s = (float*)calloc(num_items, sizeof(float));
		for(int j = 0; j < num_items; j++) {
			dsptr->s[j] = x_tilde[j];
		}
		
		int total_value = z_tilde;
		printf("Valeur optimale: %d\n", total_value);
		
		free(x_tilde);
		return total_value;
	}
	
	free(x_tilde);
	return 0;
}

// ============================================================================
// GÉNÉRATION D'INSTANCES ALÉATOIRES
// ============================================================================

void generate_random_instance(char* filename, int n, int b, int max_value, int max_weight)
{
	FILE* fout = fopen(filename, "w");
	if(!fout) {
		fprintf(stderr, "Erreur: impossible de créer le fichier %s\n", filename);
		return;
	}
	
	// Première ligne: n, b
	fprintf(fout, "%d,%d\n", n, b);
	
	// Générer n items aléatoires
	srand(time(NULL));
	for(int i = 0; i < n; i++) {
		int value = 1 + rand() % max_value;
		int weight = 1 + rand() % max_weight;
		fprintf(fout, "%d,%d\n", value, weight);
	}
	
	fclose(fout);
	printf("Instance générée: %s (n=%d, b=%d)\n", filename, n, b);
}
