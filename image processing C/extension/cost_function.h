#pragma once

#ifndef EXTENSION_COST_FUNCTION_H
#define EXTENSION_COST_FUNCTION_H
#define _CRT_SECURE_NO_WARNINGS

#include<assert.h>
#include<stdio.h>
#include<cstdbool>
#include "matrices.h"

typedef struct {
	matrix_t *grad;
	matrix_t *j;
} grad_cost_t;
 
grad_cost_t *cost_function(matrix_t *theta, matrix_t *x, matrix_t *y);

matrix_t *train(matrix_t *x, matrix_t *y, int num_classes);

//void example();

void fmincg_cost_function(float* xVec, float* cost, float* gradVec, matrix_t *x, matrix_t *y);

void costFunc(float* xVec, float* cost, float* gradVec);

#endif EXTENSION_MATRICES_H