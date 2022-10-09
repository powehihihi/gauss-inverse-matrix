#ifndef MATRIX_H
#define MATRIX_H
int readMatrix (double * a, int n, int m, const char * name);
void printMatrix (double * a, int n, int m, int p);
void initMatrix (double * a, int n, int m, int k);
double init1 (int n, int m, int i, int j);
double init2 (int n, int m, int i, int j);
double init3 (int n, int m, int i, int j);
double init4 (int n, int m, int i, int j);
void initB (double * a, double * b, int n);
void initE (double * a, int n);
void initSwap(int * swap, int n);
double result(double * a, double * x, int n);
double matrixNorm (double * a, int n);
int diagCheck(double * a, int n);
#endif
