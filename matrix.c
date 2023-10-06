#include <stdio.h>
#include <math.h>

#include "matrix.h"

//#define MAX_OUTPUT_SIZE 5

static float f(int i, int j)
{
	return 1.0 / (i + j + 1.0);
}


int InputMatrix(int n, float* a, int inputMode, FILE* fin)
{
	int i;
	int j;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i){
			for (j = 0; j < n; ++j){
				int scanned = fscanf(fin, "%f", &a[i * n + j]);
				//printf("%lf ", a[i*n+j]);
				if (!scanned){
					
					return -1;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				a[i * n + j] = f(i, j);
	}

	return 0;
}


void PrintMatrix(int n, float* a)
{
	int i;
	int j;
//	int nPrint;

//	nPrint = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;

	for (i = 0; i < n; ++i) 
	{
		printf("| ");
		for (j = 0; j < n; ++j)
			printf("%10.3g ", a[i * n + j]);
		printf("|\n");
	}
}


float SolutionError(int n, float* a, float* x)
{	
	//printf("Calculating error\n");
	int i;
	int j;
	int k;
	float tmp;
	float rezult;
	float c;

	rezult = 0.0;
	for (i = 0; i < n; ++i) 
	{
		for (j = 0; j < n; ++j) 
		{
			tmp = 0.0;
			for (k = 0; k < n; ++k) 
			{
				c = a[i * n + k] * x[k * n + j];
				tmp += c;
				//printf("c[%d][%d][%d] = %f * %f = %f\n tmp = %f\n\n", i, j, k, a[i*n+k], x[k*n+j], c, tmp);
			}


			if (i == j)
				tmp -= 1.0;

			rezult += tmp * tmp;
		}
	}

	return sqrt(rezult);
}

