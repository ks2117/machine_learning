#include "stdafx.h"
#include "matrices.h"
#include<stdlib.h>
#include<cstdbool>
#include<math.h>
#include<limits.h>
#include<float.h>
#define _CRT_SECURE_NO_WARNINGS

//some basic functions to pass as arguments

double add(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double mult(double a, double b) {
	return a * b;
}

double divlf(double a, double b) {
	return a / b;
}

double cle(double a, double b) {
	return a < b;
}

double cleq(double a, double b) {
	return a <= b;
}

double cge(double a, double b) {
	return a > b;
}

double cgeq(double a, double b) {
	return a >= b;
}

double ceq(double a, double b) {
	return a == b;
}

double id(double x) {
	return x;
}

double sqr(double x) {
	return x * x;
}

//allocates memory for a matrix
matrix_t *initMatrix(int m, int n) {
	double **array;
	matrix_t *matrix = malloc(sizeof(matrix_t));

	array = (double**)malloc(m * sizeof(double));
	if (!array) {
		return NULL;
	}

	array[0] = (double *)malloc(m * n * sizeof(double));

	if (!array[0]) {
		free(array);
		return NULL;
	}

	for (int i = 1; i < m; i++) {
		array[i] = array[i - 1] + n;
	}

	matrix->height = m;
	matrix->width = n;
	matrix->matrix = array;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix->matrix[i][j] = 0;
		}
	}

	return matrix;
}

//frees memory allocated to a matrix
void freeM(matrix_t *a) {
	free(a->matrix[0]);
	free(a);
}

//creates an identity matrix
matrix_t *eye(int n) {
	matrix_t *matrix = initMatrix(n, n);
	for (int i = 0; i < n; i++) {
		matrix->matrix[i][i] = 1;
	}

	return matrix;
}

//returns a matrix that contains the size of a matrix
matrix_t *size(matrix_t *a) {
	matrix_t *size = initMatrix(2, 1);
	size->matrix[0][0] = a->height;
	size->matrix[1][0] = a->width;

	return size;
}

//adds two matrices
matrix_t *addM(matrix_t *a, matrix_t *b) {
	assert(a->width == b->width && a->height == b->height && "Mismatch of dimensions in matrices.add");

	matrix_t *c = initMatrix(a->height, a->width);
	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			c->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];
		}
	}

	return c;
}

//substracts two matrices
matrix_t *subM(matrix_t *a, matrix_t *b) {
	assert(a->width == b->width && a->height == b->height && "Mismatch of dimensions in matrices.sub");

	matrix_t *c = initMatrix(a->height, a->width);
	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			c->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];
		}
	}

	return c;
}

//multiplies two matrices
matrix_t *multM(matrix_t *a, matrix_t *b) {
	if (a->width != b->height) {
		printf("a == (%i, %i), b == (%i, %i)\n", a->height, a->width, b->height, b->width);
	}
	assert(a->width == b->height && "Dimensions of matrices in matrices.multM do not match");
	int m = a->height;
	int n = a->width;
	int k = b->width;
	matrix_t *matrix = initMatrix(m, k);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			for (int q = 0; q < n; q++) {
				matrix->matrix[i][j] += a->matrix[i][q] * b->matrix[q][j];
			}
		}
	}

	return matrix;
}

//returns the matrix as a column. Same funcitonality as the a(:) function in MatLab
matrix_t *column(matrix_t *a) {
	matrix_t *matrix = initMatrix(a->height * a->width, 1);
	for (int i = 0; i < a->width; i++) {
		for (int j = 0; j < a->height; j++) {
			matrix->matrix[i * a->height + j][0] = a->matrix[j][i];
		}
	}

	return matrix;
}

//returns a matrix filled with '1'
matrix_t *ones(int x, int y) {
	matrix_t *matrix = initMatrix(x, y);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			matrix->matrix[i][j] = 1;
		}
	}

	return matrix;
}

//initialises a matrix and sets all of its elements to p
matrix_t *setM(int x, int y, double p) {
	matrix_t *matrix = initMatrix(x, y);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			matrix->matrix[i][j] = p;
		}
	}

	return matrix;
}

//applies a unary function to every element of a matrix
matrix_t *applyUnary(double(*fun)(double), matrix_t *a) {
	matrix_t *matrix = initMatrix(a->height, a->width);

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			matrix->matrix[i][j] = fun(a->matrix[i][j]);
		}
	}

	return matrix;
}

//applies a binary function to the elements of two matrices. 
//F.e. applyBinary((-), a,b) = a - b, where (-) is a binary function that takes in 2 elements 
//and returns their difference and a and b are matrices
matrix_t *applyBinary(double(*fun)(double, double), matrix_t *a, matrix_t *b) {
	assert(a->width == b->width && a->height == b->height && "Mismatch of dimensions in matrices.applyBinary");
	matrix_t *matrix = initMatrix(a->height, a->width);

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			matrix->matrix[i][j] = fun(a->matrix[i][j], b->matrix[i][j]);
		}
	}

	return matrix;
}

//returns the transpose of a given matrix
matrix_t *transpose(matrix_t *a) {
	matrix_t *matrix = initMatrix(a->width, a->height);

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			matrix->matrix[j][i] = a->matrix[i][j];
		}
	}

	return matrix;
}

//returns true if the matrix is a single variable
bool isVar(matrix_t *a) {
	return a->height == 1 && a->width == 1;
}


//converts a 1x1 matrix to a float
float toVar(matrix_t * a)
{
	if (isVar(a)) {
		return (float) a->matrix[0][0];
	}
	else {
		perror("Argument of toVar is not a 1x1 matrix");
		EXIT_FAILURE;
		return 0;
	}
}

//returns true if the matrix is a vector, 1x1 matrix is not considered a vector
bool isVec(matrix_t *a) {
	return a->height == 1 || a->width == 1 && !isVar(a);
}

//converts a matrix to a vector, the matrices.column will be called to ensure the output is a vector
float *toVec(matrix_t * a)
{
	a = column(a);

	float *v = malloc(sizeof(float) * a->height);

	for (int i = 0; i < a->height; i++) {
		v[i] = (float) a->matrix[i][0];
	}

	return v;
}

//returns a 1xn vector with elements from 1 to n
matrix_t *vec_to_n(int n) {
	matrix_t *matrix = initMatrix(1, n);

	for (int i = 0; i < n; i++) {
		matrix->matrix[0][i] = i + 1;
	}

	return matrix;
}

//converts a one-dimensional array of floats to a matrix_t
matrix_t *vec_to_M(float *v, int length) {
	matrix_t *matrix = initMatrix(length, 1);

	for (int i = 0; i < length; i++) {
		matrix->matrix[i][0] = (double) v[0];
	}

	return matrix;
}

//given a vector returns it without its first element 
matrix_t *vec_trunc(matrix_t *v) {
	assert(isVec(v) && "You can only truncate a vector in matrices.vec_trunc");
	int dim = v->height == 1;
	matrix_t *vt;

	if (dim == 0) {
		vt = initMatrix(v->height - 1, 1);
		for (int i = 0; i < vt->height; i++) {
			vt->matrix[i][0] = v->matrix[i + 1][0];
		}
	}
	else {
		vt = initMatrix(1, v->width);
		for (int i = 0; i < vt->width; i++) {
			vt->matrix[0][i] = v->matrix[0][i + 1];
		}
	}

	return vt;
}

//substitutes a vector into a matrix at specified index
void substituteM(matrix_t * x, matrix_t * v, int ind, int dim)
{
	if (dim == 0 && x->height != v->height || dim == 1 && x->width != v->width || !isVec(v)) {
		perror("Cannot substitute the second argument of matrices.substituteM in the first argument");
		EXIT_FAILURE;
	}

	if ((dim == 0 && ind >= x->width) || (dim == 1 && ind >= x->height) || ind < 0 || (dim != 0 && dim != 1)) {
		perror("Invalid index number in matrices.substituteM");
		EXIT_FAILURE;
	}

	if (dim == 0) {
		for (int i = 0; i < x->height; i++) {
			x->matrix[i][ind] = v->matrix[i][0];
		}
	}
	else {
		for (int i = 0; i < x->width; i++) {
			x->matrix[ind][i] = v->matrix[0][i];
		}
	}
}

//returns the sum of every column or row based on the value of dim
matrix_t *sum(matrix_t *a, int dim) {
	matrix_t *matrix;
	double sum;

	assert(dim == 0 || dim == 1 && "Wrong dimension number in matrices.sum");

	if (dim == 1) {
		matrix = initMatrix(a->height, 1);
		for (int i = 0; i < a->height; i++) {
			sum = 0;
			for (int j = 0; j < a->width; j++) {
				sum += a->matrix[i][j];
			}
			matrix->matrix[i][0] = sum;
		}
	}
	else {
		matrix = initMatrix(1, a->width);
		for (int i = 0; i < a->width; i++) {
			sum = 0;
			for (int j = 0; j < a->height; j++) {
				sum += a->matrix[j][i];
			}
			matrix->matrix[0][i] = sum;
		}
	}

	return matrix;
}

//return the mean value of every column or row depending on the value of dim
matrix_t *mean(matrix_t *a, int dim) {
	matrix_t *matrix;
	double sum;

	assert(dim == 1 || dim == 2 && "Wrong dimension number in matrices.mean");

	if (dim == 1) {
		matrix = initMatrix(a->height, 1);
		for (int i = 0; i < a->height; i++) {
			sum = 0;
			for (int j = 0; j < a->width; j++) {
				sum += a->matrix[i][j];
			}
			matrix->matrix[i][0] = sum / a->width;
		}
	}
	else {
		matrix = initMatrix(1, a->width);
		for (int i = 0; i < a->width; i++) {
			sum = 0;
			for (int j = 0; j < a->height; j++) {
				sum += a->matrix[j][i];
			}
			matrix->matrix[0][i] = sum / a->height;
		}
	}

	return matrix;
}

//converts a 1x1 matrix to a double
double toDouble(matrix_t *a) {
	assert(a->height == 1 && a->width == 1 && "Cannot convert to double since the argument is not a 1x1 matrix");

	return a->matrix[0][0];
}

//merges two matrices along the x axis. Same functionality as [a b] in Matlab 
matrix_t *concatX(matrix_t *a, matrix_t *b) {
	assert(a->height == b->height && "Mismatched dimensions in concatX");

	matrix_t *matrix = initMatrix(a->height, a->width + b->width);
	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < matrix->width; j++) {
			if (j < a->width) {
				matrix->matrix[i][j] = a->matrix[i][j];
			}
			else {
				matrix->matrix[i][j] = b->matrix[i][j - a->width];
			}
		}
	}

	return matrix;
}

//merges two matrices along the y axis. Same functionality as [a; b] in MatLab
matrix_t *concatY(matrix_t *a, matrix_t *b) {
	assert(a->width == b->width && "Mismatched dimensions in concatY");

	matrix_t *matrix = initMatrix(a->height + b->height, a->width);
	for (int i = 0; i < a->width; i++) {
		for (int j = 0; j < matrix->height; j++) {
			if (j < a->height) {
				matrix->matrix[j][i] = a->matrix[j][i];
			}
			else {
				matrix->matrix[j][i] = b->matrix[j - a->height][i];
			}
		}
	}

	return matrix;
}

//returns the variance for every column or row based on dim
matrix_t *var(matrix_t *a, int dim) {
	assert(dim == 0 || dim == 1 && "Incorrect input in matrices.var");

	matrix_t *matrix;
	matrix_t *meanMatrix;

	matrix = mean(a, dim);
	meanMatrix = initMatrix(matrix->height, matrix->width);

	if (dim == 0) {
		for (int i = 1; i < matrix->width; i++) {
			meanMatrix = concatY(matrix, meanMatrix);
		}
	}
	else {
		for (int i = 1; i < matrix->height; i++) {
			meanMatrix = concatX(matrix, meanMatrix);
		}
	}
	matrix = subM(a, meanMatrix);
	matrix = applyUnary(sqr, matrix);
	matrix = mean(a, dim);

	return matrix;
}

//returns the standard deviation of every row or column based on dim
matrix_t *stddev(matrix_t *a, int dim) {
	assert(dim == 0 || dim == 1 && "Incorrect input in matrices.std");

	return applyUnary(sqrt, var(a, dim));
}

//returns the inverse of a matrix
matrix_t *inv(matrix_t *a) {
	//TODO not needed for the extension
	return a;
}

//returns the pseudo inverse of a matrix
matrix_t *pinv(matrix_t *a) {
	//TODO not needed for the extension
	return a;
}

//return the maximum value of each column or row depending on dim
matrix_t *maxM(matrix_t *a, int dim) {
	assert(dim == 0 || dim == 1 && "Incorrect value of dim in matrices.maxM");
	double m;
	matrix_t *matrix;

	if (dim == 0) {
		matrix = initMatrix(1, a->width);
		for (int i = 0; i < a->width; i++) {
			m = -DBL_MAX;
			for (int j = 0; j < a->height; j++) {
				if (a->matrix[j][i] > m) {
					m = a->matrix[j][i];
				}
			}
			matrix->matrix[0][i] = m;
		}
		return matrix;
	}
	if (dim == 1) {
		matrix = initMatrix(a->height, 1);
		for (int i = 0; i < a->height; i++) {
			m = -DBL_MAX;
			for (int j = 0; j < a->width; j++) {
				if (a->matrix[i][j] > m) {
					m = a->matrix[i][j];
				}
			}
			matrix->matrix[i][0] = m;
		}
		return matrix;
	}

	return NULL;
}

//return the minimum value of each column or row depending on dim
matrix_t *minM(matrix_t *a, int dim) {
	assert(dim == 0 || dim == 1 && "Incorrect value of dim in matrices.maxM");
	double m;
	matrix_t *matrix;

	if (dim == 0) {
		matrix = initMatrix(1, a->width);
		for (int i = 0; i < a->width; i++) {
			m = DBL_MAX;
			for (int j = 0; j < a->height; j++) {
				if (a->matrix[i][j] < m) {
					m = a->matrix[i][j];
				}
			}
			matrix->matrix[0][i] = m;
		}
		return matrix;
	}
	if (dim == 1) {
		matrix = initMatrix(a->height, 1);
		for (int i = 0; i < a->height; i++) {
			m = DBL_MAX;
			for (int j = 0; j < a->width; j++) {
				if (a->matrix[i][j] < m) {
					m = a->matrix[i][j];
				}
			}
			matrix->matrix[i][0] = m;
		}
		return matrix;
	}

	return NULL;
}

//prints a space n times
void printS(int n) {
	for (int i = 0; i < n; i++) {
		printf(" ");
	}
}

//returns the length of the integer part of a number
double num_len(double x) {
	int flag = 0;
	if (x < 0) {
		flag = 1;
	}
	return log10(fabs(x)) + flag + 1;
}

//prints the matrix
void printM(matrix_t *a) {
	matrix_t *matrix = initMatrix(a->height, a->width);
	matrix = applyUnary(num_len, a);
	matrix = maxM(matrix, 0);

	printf("\n");
	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			printS((int) matrix->matrix[0][j] - (int) num_len(a->matrix[i][j]) + 2);
			printf("%lf", a->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//reads a matrix from a file;
//assumes \n represents the end of the row and the elements are separated by spaces
//also assumes the data is well formatted i.e. all rows have the same length
matrix_t *freadM(char *path) {
	FILE *fp;
	int c;
	int m = 1;
	int n = 0;
	int i = 0;
	int j = -1;
	double x;
	matrix_t *matrix;

	fp = fopen(path, "r");
	if (fp == NULL) perror("Error opening file");
	else
	{
		do {
			c = fgetc(fp);
			if (c == '\n') m++;
		} while (c != EOF);
		fclose(fp);
	}

	fp = fopen(path, "r");

	if (fp == NULL) perror("Error opening file");
	else
	{
		do {
			n++;
		} while (fscanf(fp, "%lf", &x) != EOF);
		fclose(fp);
	}
	n /= m;

	matrix = initMatrix(m, n);

	fp = fopen(path, "r");
	
	if (fp == NULL) perror("Error opening file");
	else
	{
		do {
			j++;
			if (j == n) {
				i++;
				j = 0;
			}
		} while (fscanf(fp, "%lf", &matrix->matrix[i][j]) != EOF);
		fclose(fp);
	}

	//printf("%s =\n", path);

	//printM(matrix);

	return matrix;
}

//saves a matrix to the given file
void fwriteM(matrix_t *a, char *path) {
	FILE *fp;
	matrix_t *matrix = initMatrix(a->height, a->width);
	matrix = applyUnary(num_len, a);
	matrix = maxM(matrix, 0);

	if ((fp = fopen(path, "w")) == NULL) {
		perror("Error opening file");
		printf("Error opening file");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			if (j != 0) {
				fputs(" ", fp);
			}
			for (int q = 0; q < (int)matrix->matrix[0][j] - (int)num_len(a->matrix[i][j]); q++) {
				fputs(" ", fp);
			}
			fprintf(fp, "%lf", a->matrix[i][j]);
		}
		if (i < a->height - 1) {
			fputs("\n", fp);
		}
	}

	fclose(fp);
}

//saves the matric as integers
void fwriteM_int(matrix_t *a, char *path) {
	FILE *fp;
	matrix_t *matrix = initMatrix(a->height, a->width);
	matrix = applyUnary(num_len, a);
	matrix = maxM(matrix, 0);

	if ((fp = fopen(path, "w")) == NULL) {
		perror("Error opening file");
		printf("Error opening file");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			if (j != 0) {
				fputs(" ", fp);
			}
			for (int q = 0; q < (int)matrix->matrix[0][j] - (int)num_len(a->matrix[i][j]); q++) {
				fputs(" ", fp);
			}
			fprintf(fp, "%i", (int) a->matrix[i][j]);
		}
		if (i < a->height - 1) {
			fputs("\n", fp);
		}
	}

	fclose(fp);
}

//compares two matrices. If equal returns 1 else returns 0
int equalsM(matrix_t *a, matrix_t *b) {
	if (a->height != b->height || a->width != b->width) {
		return 0;
	}
	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
			if (a->matrix[i][j] != b->matrix[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}