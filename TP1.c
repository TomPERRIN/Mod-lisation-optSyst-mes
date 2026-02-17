#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "TP1Functions.h"
#include "Tests.h"

void print_menu()
{
	printf("\n");
	printf("========================================\n");
	printf("  KNAPSACK PROBLEM - MENU PRINCIPAL\n");
	printf("========================================\n");
	printf("1. Tester une instance spécifique\n");
	printf("2. Tests TP1 (Greedy & LP)\n");
	printf("3. Tests TP2 (Dynamic Programming)\n");
	printf("4. Tests TP3 (Preprocessing)\n");
	printf("5. Générer instances de test\n");
	printf("0. Quitter\n");
	printf("========================================\n");
	printf("Votre choix: ");
}

int main(int argc, char **argv)
{
	int rval = 0;
	
	// Fichier instance par défaut
	char instance_file[1024];
	snprintf(instance_file, 1024, "%s", "test.csv");

	// Parsing des arguments en ligne de commande
	char c;
	while((c = getopt(argc, argv, "F:h")) != EOF) {
		switch(c) {
			case 'F':
				snprintf(instance_file, 1024, "%s", optarg);
				break;
			case 'h':
				fprintf(stderr, "Usage: ./TP1 [options]\n");
				fprintf(stderr, "Options:\n");
				fprintf(stderr, "  -F <file>  Fichier instance à charger (défaut: %s)\n", instance_file);
				fprintf(stderr, "  -h         Afficher cette aide\n");
				return 0;
			default:
				exit(0);
		}
	}

	// Mode interactif si aucun argument
	if(argc == 1) {
		int choice = -1;
		
		while(choice != 0) {
			print_menu();
			scanf("%d", &choice);
			
			switch(choice) {
				case 1: {
					// Test d'une instance spécifique
					printf("\nFichier instance (défaut: %s): ", instance_file);
					char temp[1024];
					scanf("%s", temp);
					if(strlen(temp) > 0) {
						snprintf(instance_file, 1024, "%s", temp);
					}
					
					dataSet data;
					FILE* fin = fopen(instance_file, "r");
					if(!fin) {
						fprintf(stderr, "Erreur: impossible d'ouvrir %s\n", instance_file);
						break;
					}
					read_TP1_instance(fin, &data);
					fclose(fin);

					printf("\n=== Résolution avec tous les algorithmes ===\n");
					printf("\n--- Algorithme Glouton ---\n");
					KP_Greedy(&data);
					
					printf("\n--- Relaxation Linéaire ---\n");
					KP_LP(&data);
					
					printf("\n--- Programmation Dynamique ---\n");
					KP_DynamicProgramming(&data);
					
					printf("\n--- Preprocessing ---\n");
					KP_Preprocessing(&data);
					
					free(data.c);
					free(data.a);
					free(data.s);
					break;
				}
				
				case 2: {
					// Tests TP1
					printf("\nTests TP1 - Complexité Greedy & LP\n");
					TestTP1_FixedN_VaryingB(instance_file, "results_tp1_fixed_n.csv");
					TestTP1_FixedB_VaryingN(instance_file, "results_tp1_fixed_b.csv");
					break;
				}
				
				case 3: {
					// Tests TP2
					printf("\nTests TP2 - Complexité Dynamic Programming\n");
					TestTP2_FixedN_VaryingB(instance_file, "results_tp2_fixed_n.csv");
					TestTP2_FixedB_VaryingN(instance_file, "results_tp2_fixed_b.csv");
					break;
				}
				
				case 4: {
					// Tests TP3
					printf("\nTests TP3 - Analyse du Preprocessing\n");
					TestTP3_PreprocessingAnalysis(instance_file, "results_tp3_preprocessing.csv");
					break;
				}
				
				case 5: {
					// Générer instances de test
					generate_test_instances(100, 1000);
					break;
				}
				
				case 0:
					printf("Au revoir!\n");
					break;
					
				default:
					printf("Choix invalide!\n");
			}
		}
	} else {
		// Mode ligne de commande classique
		dataSet data;
		FILE* fin = fopen(instance_file, "r");
		if(!fin) {
			fprintf(stderr, "Erreur: impossible d'ouvrir %s\n", instance_file);
			return 1;
		}
		read_TP1_instance(fin, &data);
		fclose(fin);

		printf("\n=== Résolution de l'instance %s ===\n", instance_file);
		
		printf("\n--- Algorithme Glouton ---\n");
		KP_Greedy(&data);
		
		printf("\n--- Relaxation Linéaire ---\n");
		KP_LP(&data);
		
		printf("\n--- Programmation Dynamique ---\n");
		KP_DynamicProgramming(&data);
		
		printf("\n--- Preprocessing ---\n");
		KP_Preprocessing(&data);
		
		free(data.c);
		free(data.a);
		free(data.s);
	}

	return rval;
}
