#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

// TP1 - Tests de complexité pour Greedy et LP
void TestTP1_FixedN_VaryingB(char* instance_file, char* output_csv);
void TestTP1_FixedB_VaryingN(char* instance_file, char* output_csv);

// TP2 - Tests de complexité pour Dynamic Programming
void TestTP2_FixedN_VaryingB(char* instance_file, char* output_csv);
void TestTP2_FixedB_VaryingN(char* instance_file, char* output_csv);

// TP3 - Tests de preprocessing
void TestTP3_PreprocessingAnalysis(char* instance_file, char* output_csv);

// Utilitaires
void generate_test_instances(int max_n, int max_b);

#endif
