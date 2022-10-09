#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

#define ABS(X) ((X)>=0 ? (X) : -(X))
#define MAX(X, Y) ((X)>(Y) ? (X) : (Y))
#define MIN(X, Y) ((X)>(Y) ? (Y) : (X))

#define EPS (1e-16)

enum RETURNED
{
    SUCCESS = 0,
    ERROR_OPEN = (-1),
    ERROR_READ = (-2),
    ERROR_MALLOC = (-3),
    ERROR_ARGS = (-4),
    ERROR_APPLICATION = (-5),
};

int Gauss(double * a, double * x, int * swap, int n);

#endif //TASK_H
