/*
 * matrix.h
 *
 *  Created on: 05.01.2019
 *      Author: Lukas Reining
 */

#ifndef MATRIX_H_
#define MATRIX_H_

/**
 * Matrix struct
 */
typedef struct Matrix {
	int rows, cols;
	double ** data;
} Matrix;

/**
 * Matrix generation
 */
Matrix * newMatrix(int rows, int cols);

/**
 * Matrix deletion
 */
void delMatrix(Matrix *m);

/**
 * Copy matrix
 */
Matrix matcpy(Matrix m);

/**
 *unity matrix
 */
Matrix matunity(int rows, int cols);

/**
 * Fill matrix with two dimensional array
 */
void matfill(Matrix *m, double *data[]);

/**
 * Prints a Matrix
 */
void matprint(Matrix m);

/** Addition/multiplication like before */
Matrix matplus(Matrix A, Matrix B);

Matrix matmul(Matrix A, Matrix B);

/**
 * Calculate the k-th power A**k of matrix A,
 * returning the result, optimized version.
 * @param A the input matrix
 * @param k the power coefficient
 * @return the result A**k
 */
Matrix matpow(Matrix A, unsigned int k);

/**
 * Calculate the k-th power A**k of matrix A,
 * returning the result in matrix C, naive recursion.
 * @param A the input matrix
 * @param k the power coefficient
 * @return the result A**k
 */
Matrix matpowR(Matrix A, unsigned int k);

/**
 * Calculate the k-th power A**k of matrix A,
 * returning the result in matrix C, iterative version.
 * @param A the input matrix
 * @param k the power coefficient
 * @return the result A**k
 */
Matrix matpowI(Matrix A, unsigned int k);

#endif /* MATRIX_H_ */
