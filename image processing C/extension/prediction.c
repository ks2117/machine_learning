#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdafx.h"
#include "cost_function.h"
#include <math.h>
#include "test_matrices.h"

matrix_t *predict(matrix_t *theta, matrix_t *x) {
	matrix_t *p,*a;
	x = concatX(ones(x->height, 1), x);

	p = multM(x, transpose(theta));

	a = maxM(p, 1);

	a = multM(a, ones(1, p->width));

	a = applyBinary(ceq, a, p);

	a = multM(a, column(vec_to_n(a->width)));

	return a;
}

int main() {

	double accuracy = 0;

	test_visual();


	matrix_t *theta = freadM("theta.txt");
	matrix_t *x = freadM("x.txt");
	matrix_t *pred = predict(theta, x);
	matrix_t *y = freadM("y.txt");

	fwriteM_int(pred, "pred.txt");


	//unfortunately this is working too slow now due to the multiple accesses to x.txt which is a big file
	theta = train(x, y, 10);
	fwriteM_int(theta, "theta2.txt");
	pred = predict(theta, x);
	fwriteM_int(pred, "pred2.txt");

	
	for (int i = 0; i < pred->height; i++) {
		if (pred->matrix[i][0] == y->matrix[i][0]) {
			accuracy++;
		}
	}
	accuracy /= pred->height;
	printf("Accuracy is equal to %lf\n", accuracy);
	system("pause");

	//example();

	//system("pause");
	return 0;
}