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
	if (rows <= 0 || cols <= 0)
		exit(-1);
	// allocate a matrix structure
	Matrix * m = (Matrix *) malloc(sizeof(Matrix));

	// set dimensions
	m->rows = rows;
	m->cols = cols;

	// allocate data pointers
	//allocate memory for rows
	m->data = (double **) malloc(rows * sizeof(double));
	//for each row allocate memory for columns
	for (int i = 0; i < rows; i++) {
		m->data[i] = (double *) malloc(cols * sizeof(int));
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

Matrix matmult(Matrix A, Matrix B) {
	if (A.rows != B.cols) {
		printf(
				"Die Anzahl an Zeilen von Matrix A muess mit der Anzahl der Spalten von Matrix B uebereinstimmen!");
		exit(-1);
	}
	Matrix *result = newMatrix(A.rows, A.cols);
	//Multiplication
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			for (int k = 0; k < B.rows; k++) {
				result->data[i][j] = A.data[i][k] + B.data[k][j];
			}
		}
	}
	return *result;
}

Matrix matpowR(Matrix A, unsigned int k) {
	if (k == 1) {
		//TODO Einheitsmatrix return
		return matunity(A.rows, A.cols);
	}
	return matmult(A, matpowR(A, k - 1));
}

Matrix matpowI(Matrix A, unsigned int k) {
	Matrix result = matcpy(A);
	for (int i = 0; i < k; i++) {
		result = matmult(result, A);
	}
	return result;
}
