#pragma once

#ifndef EXTENSION_MATRICES_H
#define EXTENSION_MATRICES_H
#define _CRT_SECURE_NO_WARNINGS

#include<assert.h>
#include<stdio.h>
#include<cstdbool>

typedef struct {
	int width, height;
	double **matrix;
} matrix_t;

double add(double a, double b);

double sub(double a, double b);

double mult(double a, double b);

double divlf(double a, double b);

double cle(double a, double b);

double cleq(double a, double b);

double cge(double a, double b);

double cgeq(double a, double b);

double ceq(double a, double b);

double id(double a);

double sqr(double a);

matrix_t *initMatrix(int m, int n);

void freeM(matrix_t *a);

matrix_t *eye(int n);

matrix_t *size(matrix_t *a);

matrix_t *addM(matrix_t *a, matrix_t *b);

matrix_t *subM(matrix_t *a, matrix_t *b);

matrix_t *multM(matrix_t *a, matrix_t *b);

matrix_t *column(matrix_t *a);

matrix_t *ones(int x, int y);

matrix_t *setM(int x, int y, double p);

bool isVar(matrix_t *a);

float toVar(matrix_t *a);

bool isVec(matrix_t *a);

float *toVec(matrix_t *a);

matrix_t *vec_to_n(int n);

matrix_t *vec_to_M(float *v, int length);

matrix_t *vec_trunc(matrix_t *v);

void substituteM(matrix_t *x, matrix_t *v, int ind, int dim);

matrix_t *applyUnary(double(*fun)(double), matrix_t *a);

matrix_t *applyBinary(double(*fun)(double, double), matrix_t *a, matrix_t *n);

matrix_t *transpose(matrix_t *a);

matrix_t *sum(matrix_t *a, int dim);

matrix_t *mean(matrix_t *a, int n);

double toDouble(matrix_t *a);

matrix_t *var(matrix_t *a, int dim);

matrix_t *stddev(matrix_t *a, int dim);

matrix_t *concatX(matrix_t *a, matrix_t *b);

matrix_t *concatY(matrix_t *a, matrix_t *b);

matrix_t *inv(matrix_t *a);

matrix_t *pinv(matrix_t *a);

matrix_t *maxM(matrix_t *a, int dim);

matrix_t *minM(matrix_t *a, int dim);

void printM(matrix_t *a);

matrix_t *freadM(char *path);

void fwriteM(matrix_t *matrix, char *path);

void fwriteM_int(matrix_t *a, char *path);

int equalsM(matrix_t *a, matrix_t *b);

#endif EXTENSION_MATRICES_H