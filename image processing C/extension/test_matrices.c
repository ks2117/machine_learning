// testing.c : checks some basic functionality of the matrices.h
//

#include "stdafx.h"
#include "matrices.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "fmincg/fmincg.h"
#define _CRT_SECURE_NO_WARNINGS

void test_visual()
{
	int m, n;
	matrix_t *matrix;

	printf("Enter the dimensions of the matrix: \n");
	scanf_s("%i", &m);
	scanf_s("%i", &n);
	matrix = initMatrix(m, n);

	printf("Please enter your matrix: \n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%lf", &matrix->matrix[i][j]);
		}
	}

	matrix = applyUnary(sqrt, applyBinary(add, matrix, matrix));

	printM(matrix);

	printM(column(matrix));

	printM(applyUnary(sqr, matrix));

	printM(multM(matrix, transpose(applyUnary(sqr, matrix))));

	printM(maxM(matrix, 0));

	fwriteM(matrix, "myMatrix.txt");

	system("pause");

	freadM("myMatrix.txt");

	freeM(matrix);

	printM(ones(10, 2));

	printM(vec_to_n(10));

	system("pause");
}