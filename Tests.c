#include "Tests.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>
#include "TP1Functions.h"
#include <time.h>

int write_file_n_and_b(char* instance_file, int n, int b){
    FILE *in = fopen(instance_file, "r");
    FILE *out = fopen("temp.csv", "w");

    if (!in || !out) return 1;

    // Ignorer la première ligne
    fscanf(in, "%*d,%*d\n");

    // Écrire les nouvelles valeurs
    fprintf(out, "%d,%d\n", n, b);

    // Copier le reste du fichier
    char buffer[256];
    while (fgets(buffer, sizeof buffer, in)) {
        fputs(buffer, out);
    }

    fclose(in);
    fclose(out);

    remove(instance_file);
    rename("temp.csv", instance_file);
    return 0;
}


void TestsKP_FixedN(char* instance_file, double* resultsKP_LR, double* resultsKP_Greedy, double* resultsKP_DynamicProgramming){
    int n = 50;
    int nbTests = 10;
    
    clock_t start, end;
    dataSet data;

    for (int i=1; i <= nbTests; i++){
        write_file_n_and_b(instance_file, n, i*100);
        
        FILE* fin = fopen(instance_file,"r");    
        read_TP1_instance(fin,&data);
        fclose(fin);
        
        start = clock();
        KP_LP(&data);
        end = clock();
        resultsKP_LR[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
        start = clock();
        KP_Greedy(&data);
        end = clock();
        resultsKP_Greedy[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
        start = clock();
        KP_DynamicProgramming(&data);
        end = clock();
        resultsKP_DynamicProgramming[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
    }
}

void TestsKP_FixedB(char* instance_file, double* resultsKP_LR, double* resultsKP_Greedy, double* resultsKP_DynamicProgramming){
    int b = 500;
    int nbTests = 10;
    
    clock_t start, end;
    dataSet data;

    for (int i=1; i <= nbTests; i++){
        write_file_n_and_b(instance_file, i*10, b);
        
        FILE* fin = fopen(instance_file,"r");    
        read_TP1_instance(fin,&data);
        fclose(fin);
        
        start = clock();
        KP_LP(&data);
        end = clock();
        resultsKP_LR[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
        start = clock();
        KP_Greedy(&data);
        end = clock();
        resultsKP_Greedy[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
        start = clock();
        KP_DynamicProgramming(&data);
        end = clock();
        resultsKP_DynamicProgramming[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
    }
}

int main(){
    return 0;
}