#include "stdafx.h"
#include "matrices.h"
#include<stdlib.h>
#include<cstdbool>
#include<math.h>
#include<limits.h>
#include<float.h>
#include "cost_function.h"
#include "fmincg/fmincg.h"
#define _CRT_SECURE_NO_WARNINGS
#define lambda 0.1
#define LENGTH 401
#define MAX_ITER 50



double sigmoid(double x) {
	return 1 / 1 - exp(-x);
}

grad_cost_t *cost_function(matrix_t *theta, matrix_t *x, matrix_t *y) {
	int m = max(y->height, y->width);
	int n = max(theta->height, theta->width);
	matrix_t *j, *alpha1, *alpha2, *beta1, *beta2, *gamma1, *gamma2, *kappa1, *kappa2;
	matrix_t *grad = initMatrix(theta->height, theta->width);
	matrix_t *hx;

	hx = applyUnary(sigmoid, multM(transpose(theta), transpose(x)));

	//j = (1 / m) * (- log(hx) * y - log(1 - hx) * (1 - y));
	alpha1 = multM(applyUnary(log, hx), y);

	alpha2 = subM(initMatrix(alpha1->height, alpha1->width), alpha1);

	freeM(alpha1);

	beta1 = subM(ones(hx->height, hx->width), hx);

	beta2 = applyUnary(log, beta1);

	freeM(beta1);

	gamma1 = subM(ones(y->height, y->width), y);

	beta1 = multM(beta2, gamma1);

	freeM(beta2);

	alpha1 = subM(alpha2, beta1);

	freeM(alpha2, beta1);

	alpha2 = setM(alpha1->height, alpha1->width, 1.0 / m);

	j = applyBinary(mult, alpha2, alpha1);

	freeM(alpha1);
	freeM(alpha2);

	//j = j + (lambda / (2 * m)) * ((theta(2:n) .^ 2)' * ones(n - 1, 1));

	kappa1 = vec_trunc(theta);

	kappa2 = applyUnary(sqr, kappa1);

	freeM(kappa1);

	kappa1 = transpose(kappa2);

	freeM(kappa2);

	gamma1 = ones(n - 1, 1);

	kappa1 = multM(kappa1, gamma1);

	freeM(gamma1);

	kappa2 = setM(kappa1->height, kappa1->width, lambda / (2 * m));

	gamma1 = applyBinary(mult, kappa2, kappa1);

	freeM(kappa1);
	freeM(kappa2);

	j = addM(j, gamma1);

	freeM(gamma1);

	//grad = (1 / m) * (x' * (hx' - y)) + (lambda / m) * theta;

	alpha1 = transpose(x);
	beta1 = transpose(hx);
	beta2 = subM(beta1, y);
	
	freeM(beta1);

	alpha2 = multM(alpha1, beta2);

	freeM(alpha1);
	freeM(beta2);

	beta1 = setM(alpha2->height, alpha2->width, 1.0 / m);

	alpha1 = applyBinary(mult, beta1, alpha2);

	freeM(alpha2);
	freeM(beta1);

	beta1 = setM(theta->height, theta->width, lambda / m);
	beta2 = applyBinary(mult, beta1, theta);

	alpha2 = addM(alpha1, beta2);

	freeM(alpha1);
	freeM(beta2);
	freeM(beta1);
	
	alpha2->matrix[0][0] = alpha2->matrix[0][0] * lambda / m;

	grad = column(alpha2);


	grad_cost_t *result = malloc(sizeof(grad_cost_t));
	result->grad = grad;
	result->j = j;

	freeM(alpha2);

	return result;
}

void fmincg_cost_function(float* xVec, float* cost, float* gradVec, matrix_t *x, matrix_t *y) {
	grad_cost_t *pipe = cost_function(vec_to_M(xVec, LENGTH), x, y);

	*cost = toVar(pipe->j);
	gradVec = toVec(pipe->grad);

	free(pipe->grad);
	free(pipe->j);
	free(pipe);
}

matrix_t *train(matrix_t *x, matrix_t *y, int num_classes) {
	
	int m = x->height;
	int n = x->width;
	float *initial_theta;
	matrix_t *theta = initMatrix(num_classes, n + 1);
	matrix_t *alpha, *beta;
	x = concatX(ones(m, 1), x);

	for (int i = 0; i < num_classes; i++) {
		initial_theta = malloc(sizeof(float) * (x->width));
		for (int i = 0; i < x->width; i++) {
			initial_theta[i] = 0.0;
		}
		fmincg(&fmincg_cost_function, initial_theta, x->width, MAX_ITER, x, y);
		alpha = vec_to_M(initial_theta, n + 1);
		beta = transpose(alpha);
		printM(beta);
		substituteM(theta, beta, i, 1);
		free(initial_theta);
		freeM(alpha);
		freeM(beta);
	}
	
	return theta;
}

void costFunc(float* xVec, float* cost, float* gradVec)
{
	// f(x,y) = (x-10)^4 + (y-4)^2

	*cost = (xVec[0] - 10)*(xVec[0] - 10)*(xVec[0] - 10)*(xVec[0] - 10) + (xVec[1] - 4)*(xVec[1] - 4);

	gradVec[0] = 4 * (xVec[0] - 10)*(xVec[0] - 10)*(xVec[0] - 10);
	gradVec[1] = 2 * (xVec[1] - 4);
}

//void example()
//{
//	float x[] = { 0,0 }; // initial guess
//
//	int ret = fmincg(&costFunc, x, 2, 1000); // nDim = 2 , maxCostFunctionCalls = 1000
//
//	printf("X-optim = (%f,%f). Return value = %d \n", x[0], x[1], ret);
//}