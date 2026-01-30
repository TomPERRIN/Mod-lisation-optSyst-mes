#include "TP1Functions.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include<stdio.h>

int read_TP1_instance(FILE*fin,dataSet* dsptr)
{
	int rval = 0;

	//capacite b
	int b;
	//Nombre d'objets
	int n;
	rval = fscanf(fin,"%d,%d\n",&n,&b);
	dsptr->b = b;
	dsptr->n = n;
	dsptr->c = (int*)malloc(sizeof(int)*n);
	dsptr->a = (int*)malloc(sizeof(int)*n);


	int i;
	for( i = 0 ; i < n ; i++)
		rval = fscanf(fin,"%d,%d\n",&(dsptr->c[i]),&(dsptr->a[i]));

	fprintf(stderr,"\nInstance file read, we have capacity %d and there is %d items of values/weights:\n",
			b,n);
	for( i = 0 ; i < n ; i++)
		fprintf(stderr,"%d,%d\n",dsptr->c[i],dsptr->a[i]);
	fprintf(stderr,"\n");


	return rval;
}

void descendingSorting(float tab[], int n) {
    float temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tab[j] < tab[j + 1]) { // décroissant
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

void trierParRatio(int valeurs[], int poids[], int n) {
    float tempValeur, tempPoids, tempRatio;
    float ratio[n];
    
    // Calcul des ratios
    for (int i = 0; i < n; i++) {
        ratio[i] = valeurs[i] / poids[i];
    }

    // Tri à bulles basé sur le ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparaison des ratios, tri décroissant
            if (ratio[j] < ratio[j + 1]) {
                // Échanger les ratios
                tempRatio = ratio[j];
                ratio[j] = ratio[j + 1];
                ratio[j + 1] = tempRatio;

                // Échanger les valeurs correspondantes
                tempValeur = valeurs[j];
                valeurs[j] = valeurs[j + 1];
                valeurs[j + 1] = tempValeur;

                // Échanger les poids correspondants
                tempPoids = poids[j];
                poids[j] = poids[j + 1];
                poids[j + 1] = tempPoids;
            }
        }
    }
}

void printIntArray(int tab[], int n){
	printf("[ ");
	for (int i = 0; i < n; i++) {
		printf("%d ", tab[i]);
    }
	printf("]\n");
}

float minBtwnFloat(float a, float b){
	if (a <= b){
		return a;
	}
	return b;
}

int KP_greedy(dataSet* dsptr)
{
	int rval = 0; 

	return rval;
}

int KP_LP(dataSet* dsptr)
{
	int rval = 0;
	int capacity = dsptr->b;
	int size = dsptr->n;
	dsptr->s = (float*)malloc(sizeof(float)*size);

	// float ratio [size];
	for (int i=0; i < size; i++){
		// ratio[i] = (float) dsptr->c[i] / dsptr->a[i];
		dsptr->s[i] = 0;
	}
	trierParRatio(dsptr->c, dsptr->a, size);

	// printf("Capacity : %d\n", capacity);
	// printIntArray(dsptr->c, size);
	// printIntArray(dsptr->a, size);

	for (int i=0; i < size; i++){
		if (capacity == 0){
			printf("Solution optimale KP_LP : %d\n", rval);
			return rval;
		}
		dsptr->s[i] = minBtwnFloat(capacity / dsptr->a[i], (float) 1);
		capacity = capacity - dsptr->s[i]*dsptr->a[i];
		rval += dsptr->s[i]*dsptr->c[i];
	}
	printf("Solution optimale KP_LP : %d\n", rval);
	return rval;
}

