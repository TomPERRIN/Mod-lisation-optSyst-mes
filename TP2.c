#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "TP2Functions.h"
#include<ilcplex/cplex.h>


int main(int argc, char **argv)
{
	int rval =0;	
	//File instance name
	//-F option
        char instance_file[1024];
        snprintf(       instance_file,
                        1024,
                        "%s",
                        "instance.csv");

	char c;
        while ((c=getopt (argc, argv,"F:h")) != EOF)
	{
		switch(c)
		{
                        case 'F':
				snprintf(       instance_file,
						1024,
						"%s",
						optarg);
				break;

			case 'h':
				fprintf(stderr,"Usage: ./TP2 [options]\nOptions:\n\n");
				fprintf(stderr,"******** INSTANCE DATA ********\n");
				fprintf(stderr,"\t-F Instance file name to load............................(default %s).\n",instance_file);
				break;
			default:
				exit(0);
		}
	}

	dataSet data;

	//Open the instance file
	FILE* fin = fopen(instance_file,"r");
	read_TP2_instance(fin,&data);
	fclose(fin);

	//execute your solution methods on the instance you just read
	//Exact solution
	// solve_1DKP(&data); //0.06 sec
	// printf("------------------------------\n");
	// solve_2DKP(&data); //0.02 sec
	int nbTests = 10;
	float* Solve_time_b_g_fixed = (float*)malloc(sizeof(float)*nbTests);
	float* Solve_time_b_g_fixed2D = (float*)malloc(sizeof(float)*nbTests);
	tests_b_g_fixed(instance_file, Solve_time_b_g_fixed, Solve_time_b_g_fixed2D);

	// float* Solve_time_n_g_fixed = (float*)malloc(sizeof(float)*nbTests);
	// float* Solve_time_n_g_fixed2D = (float*)malloc(sizeof(float)*nbTests);
	// tests_n_g_fixed(instance_file, Solve_time_n_g_fixed, Solve_time_n_g_fixed2D);
	
	// float* Solve_time_n_b_fixed = (float*)malloc(sizeof(float)*nbTests);
	// float* Solve_time_n_b_fixed2D = (float*)malloc(sizeof(float)*nbTests);
	// tests_n_b_fixed(instance_file, Solve_time_n_b_fixed, Solve_time_n_b_fixed2D);

	printf("------------------------------tests------------------------------\n");
	printFloatArray(Solve_time_b_g_fixed, nbTests);
	printFloatArray(Solve_time_b_g_fixed2D, nbTests);
	return rval;
}

