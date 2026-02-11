#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <assert.h>




typedef struct dataSet 
{
	//Attributes of the instance
	//Nombre d'objets
	int n;
	//Capacite b
	int b;
	//Tableau d'entiers de taille n contenant la valeur de chacun des objets
	int*c;
	//Tableau d'entiers de taille n contenant le poids de chacun des objets
	int*a;
	//Tableau d'entier de taille n contenant la prise ou non d'un objet (solution)
	float*s;
	//Valeur optimale de la relaxation linéaire
	float z_bar;
	//Valeur de la solution gloutonne
	int z_greedy;

} dataSet;

int read_TP1_instance(FILE*fin,dataSet* dsptr);
int KP_Greedy(dataSet* dsptr);
int KP_LP(dataSet* dsptr);
int KP_DynamicProgramming(dataSet* dsptr);
int KP_Preprocessing(dataSet* dsptr);
void generate_random_instance(char* filename, int n, int b, int max_value, int max_weight);

