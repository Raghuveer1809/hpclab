#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 2

static long steps = 1000000000;
double step;

int main(int argc, const char* argv[]) {

	int i, j;
	double x;
	double pi, sum = 0.0;
	double start, delta;

	step = 1.0 / (double)steps;

	// Compute parallel compute times for 1-MAX_THREADS
	for (j = 1; j <= MAX_THREADS; j++) {

		printf(" running on %d threads: ", j);

		// This is the beginning of a single PI computation
		omp_set_num_threads(j);

		sum = 0.0;
		double start = omp_get_wtime();


#pragma omp parallel for reduction(+:sum) private(x)
		for (i = 0; i < steps; i++) {
			x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}

		// Out of the parallel region, finialize computation
		pi = step * sum;
		delta = omp_get_wtime() - start;
		printf("PI = %.16g computed in %.4g seconds\n", pi, delta);

	}


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
