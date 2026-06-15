#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../simd-lib/src/simdlib.h"

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

int main() {
	double h[2], scalar_time, simd_time;
	double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

	double w1[2][2] = {
		{20, 20},
		{20, 20}};
	double w2[2] = {20, -20};

	double b1[2] = {-10, -30};
	double b2 = -10;
	clock_t start, end;

	start = clock();
	for (int i = 0; i < 4; i++) {
		// Hidden layer
		h[0] = dot_product(input[i], w1[0], 2) + b1[0];
		h[1] = dot_product(input[i], w1[1], 2) + b1[1];
		h[0] = sigmoid(h[0]);
		h[1] = sigmoid(h[1]);

		// Output layer
		double out = dot_product(h, w2, 2) + b2;
		out = sigmoid(out); // Confidence score of it being 1
		double zero = 1 - out; // Confidence score of it being 0
		printf("1: %lf, 0: %lf \n", out, zero);
	}
	end = clock();
	scalar_time = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Scalar time: %lf \n\n", scalar_time);


	start = clock();
	for (int i = 0; i < 4; i++) {
		// Hidden layer
		h[0] = simd_dot_product(input[i], w1[0], 2) + b1[0];
		h[1] = simd_dot_product(input[i], w1[1], 2) + b1[1];
		h[0] = sigmoid(h[0]);
		h[1] = sigmoid(h[1]);

		// Output layer
		double out = simd_dot_product(h, w2, 2) + b2;
		out = sigmoid(out); // Confidence score of it being 1
		double zero = 1 - out; // Confidence score of it being 0
		printf("1: %lf, 0: %lf \n", out, zero);
	}
	end = clock();
	simd_time = (double)(end-start)/CLOCKS_PER_SEC;
	printf("SIMD time: %lf \n\n", simd_time);
	printf("Ratio: %lf \n", scalar_time/ simd_time);

	return 0;
}
