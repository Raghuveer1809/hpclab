#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
	int i, N;
	float* array, * check;

	printf("Enter the size\n");
	scanf_s("%d", &N);

	if (N <= 0) {
		printf("Array Size Should Be Of Postive Sign \n");
		exit(1);
	}

	array = (float*)malloc(sizeof(float) * N);
	check = (float*)malloc(sizeof(float) * N);

	for (i = 0; i < N; i++) {
		array[i] = i * 1;
		check[i] = i * 1;
	}

	printf("The Input Array Is\n");

	for (i = 0; i < N; i++)
		printf("%f\t", array[i]);

#pragma omp parallel for
	for (i = 1; i < N; i++) {
#pragma omp critical
		array[i] = (array[i - 1] + array[i]) / 2;
	}
	for (i = 1; i < N; i++)
		check[i] = (check[i - 1] + check[i]) / 2;

	for (i = 0; i < N; i++) {
		if (check[i] == array[i])
			continue;
		else {
			printf("There is a difference in the parallel and serial calculation \n");
			exit(1);
		}
	}
	printf("\nThe Array Calculation Is Same Using Serial And OpenMP Directives\n");
	printf("The Output Array Is \n");
	for (i = 0; i < N; i++)
		printf("\n %f \t", array[i]);

	printf("\n");
	/* Freeing The Memory */

	free(array);
	free(check);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
