#include "Tests.h"
#include "TP1Functions.h"
#include <sys/time.h>

// ============================================================================
// UTILITAIRES
// ============================================================================

double get_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

// Modifier les valeurs n et b dans un fichier instance
int modify_instance_params(char* instance_file, int new_n, int new_b)
{
	FILE *in = fopen(instance_file, "r");
	FILE *out = fopen("temp.csv", "w");

	if(!in || !out) {
		fprintf(stderr, "Erreur: impossible d'ouvrir les fichiers\n");
		return 1;
	}

	// Ignorer la première ligne
	fscanf(in, "%*d,%*d\n");

	// Écrire les nouvelles valeurs
	fprintf(out, "%d,%d\n", new_n, new_b);

	// Copier le reste du fichier
	char buffer[256];
	int count = 0;

	while(fgets(buffer, sizeof buffer, in)) {
		fputs(buffer, out);
		count++;
	}

	fclose(in);
	fclose(out);

	remove(instance_file);
	rename("temp.csv", instance_file);
	return 0;
}

// ============================================================================
// TP1 - TESTS DE COMPLEXITÉ
// ============================================================================

void TestTP1_FixedN_VaryingB(char* instance_file, char* output_csv)
{
	printf("\n========== TEST TP1: n fixé, b variable ==========\n");
	
	int fixed_n = 50;
	int num_tests = 10;
	int b_start = 100;
	int b_step = 100;
	
	FILE* fout = fopen(output_csv, "w");
	fprintf(fout, "b,time_greedy_ms,time_lp_ms,value_greedy,value_lp\n");
	
	for(int i = 0; i < num_tests; i++) {
		int b = b_start + i * b_step;
		
		modify_instance_params(instance_file, fixed_n, b);
	
		dataSet data;
		FILE* fin = fopen(instance_file, "r");
		read_TP1_instance(fin, &data);
		fclose(fin);
		
		double start = get_time_ms();
		int value_greedy = KP_Greedy(&data);
		double time_greedy = get_time_ms() - start;

		start = get_time_ms();
		int value_lp = KP_LP(&data);
		double time_lp = get_time_ms() - start;
		
		fprintf(fout, "%d,%.6f,%.6f,%d,%d\n", b, time_greedy, time_lp, value_greedy, value_lp);
		printf("b=%d: Greedy=%.3fms LP=%.3fms\n", b, time_greedy, time_lp);
		
		free(data.c);
		free(data.a);
		free(data.s);
	}
	
	fclose(fout);
	printf("Résultats sauvegardés dans %s\n", output_csv);
}

void TestTP1_FixedB_VaryingN(char* instance_file, char* output_csv)
{
	printf("\n========== TEST TP1: b fixé, n variable ==========\n");
	
	int fixed_b = 500;
	int num_tests = 10;
	int n_start = 10;
	int n_step = 10;
	
	FILE* fout = fopen(output_csv, "w");
	fprintf(fout, "n,time_greedy_ms,time_lp_ms,value_greedy,value_lp\n");
	
	for(int i = 0; i < num_tests; i++) {
		int n = n_start + i * n_step;
		
		modify_instance_params(instance_file, n, fixed_b);
		
		dataSet data;
		FILE* fin = fopen(instance_file, "r");
		read_TP1_instance(fin, &data);
		fclose(fin);
		
		double start = get_time_ms();
		int value_greedy = KP_Greedy(&data);
		double time_greedy = get_time_ms() - start;
		
		start = get_time_ms();
		int value_lp = KP_LP(&data);
		double time_lp = get_time_ms() - start;
		
		fprintf(fout, "%d,%.6f,%.6f,%d,%d\n", n, time_greedy, time_lp, value_greedy, value_lp);
		printf("n=%d: Greedy=%.3fms LP=%.3fms\n", n, time_greedy, time_lp);
		
		free(data.c);
		free(data.a);
		free(data.s);
	}
	
	fclose(fout);
	printf("Résultats sauvegardés dans %s\n", output_csv);
}

// ============================================================================
// TP2 - TESTS DE COMPLEXITÉ POUR PROGRAMMATION DYNAMIQUE
// ============================================================================

void TestTP2_FixedN_VaryingB(char* instance_file, char* output_csv)
{
	printf("\n========== TEST TP2: n fixé, b variable ==========\n");
	
	int fixed_n = 30;
	int num_tests = 10;
	int b_start = 100;
	int b_step = 100;
	
	FILE* fout = fopen(output_csv, "w");
	fprintf(fout, "b,time_dp_ms,value_dp\n");
	
	for(int i = 0; i < num_tests; i++) {
		int b = b_start + i * b_step;
		
		modify_instance_params(instance_file, fixed_n, b);
		
		dataSet data;
		FILE* fin = fopen(instance_file, "r");
		read_TP1_instance(fin, &data);
		fclose(fin);
		
		double start = get_time_ms();
		int value_dp = KP_DynamicProgramming(&data);
		double time_dp = get_time_ms() - start;
		
		fprintf(fout, "%d,%.6f,%d\n", b, time_dp, value_dp);
		printf("b=%d: DP=%.3fms value=%d\n", b, time_dp, value_dp);
		
		free(data.c);
		free(data.a);
		free(data.s);
	}
	
	fclose(fout);
	printf("Résultats sauvegardés dans %s\n", output_csv);
}

void TestTP2_FixedB_VaryingN(char* instance_file, char* output_csv)
{
	printf("\n========== TEST TP2: b fixé, n variable ==========\n");
	
	int fixed_b = 500;
	int num_tests = 10;
	int n_start = 10;
	int n_step = 10;
	
	FILE* fout = fopen(output_csv, "w");
	fprintf(fout, "n,time_dp_ms,value_dp\n");
	
	for(int i = 0; i < num_tests; i++) {
		int n = n_start + i * n_step;
		
		modify_instance_params(instance_file, n, fixed_b);
		
		dataSet data;
		FILE* fin = fopen(instance_file, "r");
		read_TP1_instance(fin, &data);
		fclose(fin);
		
		double start = get_time_ms();
		int value_dp = KP_DynamicProgramming(&data);
		double time_dp = get_time_ms() - start;
		
		fprintf(fout, "%d,%.6f,%d\n", n, time_dp, value_dp);
		printf("n=%d: DP=%.3fms value=%d\n", n, time_dp, value_dp);
		
		free(data.c);
		free(data.a);
		free(data.s);
	}
	
	fclose(fout);
	printf("Résultats sauvegardés dans %s\n", output_csv);
}

// ============================================================================
// TP3 - TESTS DE PREPROCESSING
// ============================================================================

void TestTP3_PreprocessingAnalysis(char* instance_file, char* output_csv)
{
	printf("\n========== TEST TP3: Analyse du Preprocessing ==========\n");
	
	int num_tests = 20;
	
	FILE* fout = fopen(output_csv, "w");
	fprintf(fout, "test_id,n,b,vars_fixed,vars_fixed_percent,time_without_preprocessing_ms,time_with_preprocessing_ms,speedup\n");
	
	for(int i = 0; i < num_tests; i++) {
		int n = 20 + rand() % 80;
		int b = 50 + rand() % 950;
		
		modify_instance_params(instance_file, n, b);
		
		// Test SANS preprocessing (DP direct)
		dataSet data1;
		FILE* fin1 = fopen(instance_file, "r");
		read_TP1_instance(fin1, &data1);
		fclose(fin1);
		
		double start = get_time_ms();
		KP_DynamicProgramming(&data1);
		double time_without = get_time_ms() - start;
		
		// Test AVEC preprocessing
		dataSet data2;
		FILE* fin2 = fopen(instance_file, "r");
		read_TP1_instance(fin2, &data2);
		fclose(fin2);
		
		start = get_time_ms();
		KP_Preprocessing(&data2);
		double time_with = get_time_ms() - start;
		
		int vars_fixed = 0;
		
		double speedup = time_without / time_with;
		
		fprintf(fout, "%d,%d,%d,%d,%.2f,%.6f,%.6f,%.2f\n", 
		        i, n, b, vars_fixed, 0.0, time_without, time_with, speedup);
		
		printf("Test %d: n=%d b=%d | Sans=%.3fms Avec=%.3fms Speedup=%.2fx\n", 
		       i, n, b, time_without, time_with, speedup);
		
		free(data1.c);
		free(data1.a);
		free(data1.s);
		free(data2.c);
		free(data2.a);
		free(data2.s);
	}
	
	fclose(fout);
	printf("Résultats sauvegardés dans %s\n", output_csv);
}

// ============================================================================
// GÉNÉRATION D'INSTANCES DE TEST
// ============================================================================

void generate_test_instances(int max_n, int max_b)
{
	printf("\n========== Génération d'instances de test ==========\n");
	
	// Générer plusieurs instances de tailles différentes
	int test_cases[][2] = {
		{10, 50},
		{20, 100},
		{30, 200},
		{50, 500},
		{75, 750},
		{100, 1000}
	};
	
	int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
	
	for(int i = 0; i < num_cases; i++) {
		int n = test_cases[i][0];
		int b = test_cases[i][1];
		
		char filename[256];
		snprintf(filename, 256, "test_n%d_b%d.csv", n, b);
		
		generate_random_instance(filename, n, b, 20, 15);
	}
	
	printf("Instances générées avec succès!\n");
}
