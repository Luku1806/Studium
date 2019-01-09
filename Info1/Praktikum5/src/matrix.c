/*
 * matrix.c
 *
 *  Created on: 05.01.2019
 *      Author: Lukas Reining
 */

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix * newMatrix(int rows, int cols) {
	if (rows <= 0 || cols <= 0) {
		printf("Die Dimensionen der Matrix muessen mindestens 1x1 sein");
		exit(-1);
	}
	// allocate a matrix structure
	Matrix * m = (Matrix *) malloc(sizeof(Matrix));

	// set dimensions
	m->rows = rows;
	m->cols = cols;

	// allocate data pointers
	//allocate memory for rows
	m->data = (double **) malloc(rows * sizeof(double*));
	//for each row allocate memory for columns
	for (int i = 0; i < rows; i++) {
		m->data[i] = (double *) malloc(cols * sizeof(double));
	}

	// set all data to 0
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m->data[i][j] = 0.0;
		}
	}

	return m;
}

void delMatrix(Matrix *m) {
	for (int i = 0; i < m->rows; i++) {
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

Matrix matcpy(Matrix m) {
	Matrix *result = newMatrix(m.rows, m.cols);
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			result->data[i][j] = m.data[i][j];
		}
	}
	return *result;
}

char matcmp(Matrix a, Matrix b) {
	if (a.cols != b.cols || a.rows != b.rows) {
		return 0;
	}
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[i][j] != b.data[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

Matrix matunity(int rows, int cols) {
	Matrix *unity = newMatrix(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) {
				unity->data[i][j] = 1.0;
			}
		}
	}
	return *unity;
}

void matfill(Matrix *m, double* data[]) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->data[i][j] = data[i][j];
		}
	}
}

void matprint(Matrix m) {
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			printf("% f\t", m.data[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix matplus(Matrix A, Matrix B) {
	if (A.rows != B.rows || A.cols != B.cols) {
		printf(
				"Die Dimensionen von Matrix A muessen mit denen von Matrix B uebereinstimmen!");
		exit(-1);
	}
	Matrix *result = newMatrix(A.rows, A.cols);
	//Addition
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			result->data[i][j] = A.data[i][j] + B.data[i][j];
		}
	}
	return *result;
}

Matrix matmul(Matrix A, Matrix B) {
	if (A.cols != B.rows) {
		printf(
				"Die Anzahl an Spalten von Matrix A muss mit der Anzahl der Zeilen von Matrix B uebereinstimmen!");
		exit(-1);
	}
	Matrix *result = newMatrix(A.rows, B.cols);
	//Multiplication
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			for (int k = 0; k < B.rows; k++) {
				result->data[i][j] += A.data[i][k] * B.data[k][j];
			}
		}
	}
	return *result;
}

Matrix matpow(Matrix A, unsigned int k) {
	int q = k / 2;
	if (k == 0) {
		return matunity(A.rows, A.cols);
	} else if (k == 1) {
		return matcpy(A);
	} else if (k % 2 == 0) {
		Matrix b = matpow(A, q);
		Matrix result = matmul(b, b);
		delMatrix(&b);
		return result;
	} else if (k % 2 == 1) {
		Matrix b = matpow(A, q);
		Matrix mult = matmul(b, b);
		Matrix result = matmul(mult, A);
		delMatrix(&b);
		delMatrix(&mult);
		return result;
	}
	return matunity(A.rows, A.cols);
}

Matrix matpowR(Matrix A, unsigned int k) {
	if (k == 0) {
		return matunity(A.rows, A.cols);
	}
	return matmul(A, matpowR(A, k - 1));
}

Matrix matpowI(Matrix A, unsigned int k) {
	Matrix result = matcpy(A);
	for (int i = 1; i < k; i++) {
		Matrix temp = matmul(result, A);
		delMatrix(&result);
		result = matcpy(temp);
		delMatrix(&temp);
	}
	return result;
}
