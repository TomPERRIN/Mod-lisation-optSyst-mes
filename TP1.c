#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "TP1Functions.h"


int main(int argc, char **argv)
{
	int rval =0;	
	//File instance name
	//-F option
        char instance_file[1024];
        snprintf(       instance_file,
                        1024,
                        "%s",
                        "instance1.csv");

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
				fprintf(stderr,"Usage: ./TP1 [options]\nOptions:\n\n");
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
	read_TP1_instance(fin,&data);
	fclose(fin);

	//execute your solution methods on the instance you just read
	KP_greedy(&data);
	KP_LP(&data);
	KP_DynamicProgramming(&data);

	int nbTests = 10;

	float* timeNFixedKP_LR = (float*)malloc(sizeof(float)*nbTests);
	float* timeNFixedKP_Greedy = (float*)malloc(sizeof(float)*nbTests);
	float* timeNFixedKP_DynamicProgramming = (float*)malloc(sizeof(float)*nbTests);
	
	float* timeBFixedKP_Greedy = (float*)malloc(sizeof(float)*nbTests);
	float* timeBFixedKP_LR = (float*)malloc(sizeof(float)*nbTests);
	float* timeBFixedKP_DynamicProgramming = (float*)malloc(sizeof(float)*nbTests);
	
	//n fixed tests
	//modifier csv n = 10
	for (int i = 1; i <= nbTests; i++){
		//modifier csv b = 100*i
		//timeNFixedKP_LR [i-1] = timeof(KP_LP(&data))
		//timeNFixedKP_Greedy [i-1] = timeof(KP_Greedy(&data))
		//timeNFixedKP_DynamicProgramming [i-1] = timeof(KP_DynamicProgramming(&data))
	}
	return rval;
}