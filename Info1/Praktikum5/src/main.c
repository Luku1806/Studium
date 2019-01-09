/*
 * main.c
 *
 *  Created on: Dec 2, 2018
 *      Author: Lukas
 */
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int sizeAx = 5, sizeBx = 3, sizeCx = 3, sizeDx = 2, sizeEx = 5, sizeFx = 3;
int sizeAy = 3, sizeBy = 4, sizeCy = 3, sizeDy = 2, sizeEy = 5, sizeFy = 3;


double a1[] = { 0.5, -1.0, -1.0 };
double a2[] = { -1.0, 1.0, 2.0 };
double a3[] = { -1.0, 2.0, 1.0 };
double a4[] = { 2.0, 3.0, 1.0 };
double a5[] = { 0.5, 2.0, 1.0 };

double b1[] = { 0.5, 0.0, 1.5, -3 };
double b2[] = { 5.0, -0.5, -3.0, 2.0 };
double b3[] = { -1.0, -1.0, -0.75, 4.0 };

double c1[] = { 1.0, 1.0, 3.0 };
double c2[] = { 5.0, 2.0, 6.0 };
double c3[] = { -2.0, -1.0, -3.0 };

double d1[] = { 2, 1 };
double d2[] = { 0, 2 };

double e1[] = { 0, 0, 0, 0, 16.0 };
double e2[] = { (3.0 / 4.0), 0, 0, 0, 0 };
double e3[] = { 0, (2.0 / 3.0), 0, 0, 0 };
double e4[] = { 0, 0, (1.0 / 2.0), 0, 0 };
double e5[] = { 0, 0, 0, (1.0 / 4.0), 0 };

double f1[] = { 0.5, -1.0, -1.0 };
double f2[] = { -1.0, 1.0, 2.0 };
double f3[] = { -1.0, 2.0, 1.0 };

double* A[] = { a1, a2, a3, a4, a5 };
double* B[] = { b1, b2, b3 };
double* C[] = { c1, c2, c3 };
double* D[] = { d1, d2 };
double* E[] = { e1, e2, e3, e4, e5 };
double* F[] = { f1, f2, f3 };

Matrix matrixA, matrixB, matrixC, matrixD, matrixE, matrixF;

void test() {
	matrixA = *newMatrix(sizeAx, sizeAy);
	matrixB = *newMatrix(sizeBx, sizeBy);
	matrixC = *newMatrix(3, 3);
	matfill(&matrixA, A);
	matfill(&matrixB, B);
	matfill(&matrixC, B);

	printf("\n---------------Test---------------\n");

	printf("Matrix A:\n");
	matprint(matrixA);
	printf("Matrix B:\n");
	matprint(matrixB);

	printf("\n\nmatplus\n");
	Matrix matRes1 = matplus(matrixA, matrixA);
	matprint(matRes1);

	printf("\nmatmul:\n");
	Matrix matRes2 = matmul(matrixA, matrixB);
	matprint(matRes2);

	printf("\nmatpow:\n");
	Matrix matRes3 = matpowI(matrixC, 3);
	matprint(matRes3);

	printf("\nmatpowR:\n");
	Matrix matRes4 = matpowI(matrixC, 3);
	matprint(matRes4);

	printf("\nmatpowI:\n");
	Matrix matRes5 = matpowI(matrixC, 2);
	matprint(matRes5);
}

void testPowers() {
	matrixC = *newMatrix(sizeCx, sizeCy);
	matrixD = *newMatrix(sizeDx, sizeDy);
	matrixE = *newMatrix(sizeEx, sizeEy);
	matrixF = *newMatrix(sizeFx, sizeFy);
	matfill(&matrixC, C);
	matfill(&matrixD, D);
	matfill(&matrixE, E);
	matfill(&matrixF, F);

	//Matrix C^3
	printf("\nC^3:\n");
	printf("\nmatpow:\n");
	Matrix matResC1 = matpow(matrixC, 3);
	matprint(matResC1);
	//delMatrix(&matResC1);

	printf("\nmatpowR:\n");
	Matrix matResC2 = matpowR(matrixC, 3);
	matprint(matResC2);
	//delMatrix(&matResC2);

	printf("\nmatpowI:\n");
	Matrix matResC3 = matpowI(matrixC, 3);
	matprint(matResC3);
	//delMatrix(&matResC3);

	//Matrix D ^ 8
	printf("\nD^8:\n");
	printf("\nmatpow:\n");
	Matrix matResD1 = matpow(matrixD, 8);
	matprint(matResD1);
	//delMatrix(&matResD1);

	printf("\nmatpowR:\n");
	Matrix matResD2 = matpowR(matrixD, 8);
	matprint(matResD2);
	//delMatrix(&matResD2);

	printf("\nmatpowI:\n");
	Matrix matResD3 = matpowI(matrixD, 8);
	matprint(matResD3);
	//delMatrix(&matResD3);

	//Matrix E^1-6
	for (int i = 1; i <= 6; i++) {
		printf("\nE^%d:\n", i);
		printf("\nmatpow:\n");
		Matrix matResE1 = matpow(matrixE, i);
		matprint(matResE1);

		printf("\nmatpowR:\n");
		Matrix matResE2 = matpowR(matrixE, i);
		matprint(matResE2);

		printf("\nmatpowI:\n");
		Matrix matResE3 = matpowI(matrixE, i);
		matprint(matResE3);
	}

	//Matrix F^5
	printf("\nF^5:\n");
	printf("\nmatpow:\n");
	Matrix matResF1 = matpow(matrixF, 5);
	matprint(matResF1);
	//delMatrix(&matResF1);

	printf("\nmatpowR:\n");
	Matrix matResF2 = matpowR(matrixF, 5);
	matprint(matResF2);
	//delMatrix(&matResF2);

	printf("\nmatpowI:\n");
	Matrix matResF3 = matpowI(matrixF, 5);
	matprint(matResF3);
	//delMatrix(&matResF3);
}

int main(int argc, char* argv[]) {
	testPowers();
	return 0;
}
