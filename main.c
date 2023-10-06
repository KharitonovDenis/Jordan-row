#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "matrix.h"
#include "task.h"
#include "io.h"


int main(int argc, char *argv[])
{
	int inputMode;
	int n;
	FILE* fin;
	char* filename;
	
	if(argc < 2 || argc > 3){
		printf("Incorrect number of command line arguments");
	} else if(argc == 3){
		char* c;
		n = strtol(argv[1], &c, 10);
		inputMode = 1;
		filename = argv[2];
		fin = fopen(filename, "r");
		if (fin == NULL) {
        	printf("Error with reading the file");
			return -1;
    	}


	} else {
		char* c;
		n = strtol(argv[1], &c, 10);
		inputMode = 2;
	}
	

	int rezult;
	
	
	
	
	int* index = (int*)malloc(n * sizeof(int));
	float* a = (float*)malloc(n * n * sizeof(float));
	float* x = (float*)malloc(n * n * sizeof(float));
	
	clock_t t;

	if (n < 1)
	{
		printf("Incorrect N!\n");

		if (inputMode == 1)
			fclose(fin);

		return -2;
	}

	if (!(index && a && x))
	{
		printf("Not enough memory!\n");

		if (index)
			free(index);
		if (a)
			free(a);
		if (x)
			free(x);

		if (inputMode == 1)
			fclose(fin);

		return -3;
	}

	rezult = InputMatrix(n, a, inputMode, fin);

	if (inputMode == 1)
		fclose(fin);

	if (rezult == -1)
	{
		printf("Error in reading from file!\n");

		free(index);
		free(a);
		free(x);

		return -4;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, a);
	printf("\n");

	printf("Calculating...\n");

	t = clock();
	rezult = InvertMatrix(n, a, x, index);
	t = clock() - t;

	switch (rezult)
	{
	case -1:
		printf("Can't invert - matrix is deteriorated.\n");

		break;
	case 0:
		printf("\nMatrix A^{-1}:\n");
		PrintMatrix(n, x);
		printf("\n");

		printf("Inversion time\t\t= %.2f sec.\n\n", (double)t / CLOCKS_PER_SEC);

		fclose(fin);
		fin = fopen(filename, "r");
		InputMatrix(n, a, inputMode, fin);

		if (inputMode == 1)
			fclose(fin);


		printf("Solution ||A * A^{-1} - E||\t= %f\n", SolutionError(n, a, x));

		break;
	default:
		printf("Unknown error!\n");

		break;
	}

	free(index);
	free(a);
	free(x);

	return 0;
}
