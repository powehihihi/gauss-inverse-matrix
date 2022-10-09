#include "task.h"
#include "matrix.h"

int GaussSimple(double * a, double * x, int n);
int GaussSimple(double * a, double * x, int n)
{
    int i, j, k;
    double temp, denominator, eps;
    double * line_x;
    double * line_a;

    eps = EPS * matrixNorm(a, n);

    for (i=0; i<n; ++i)
    {
        temp = a[i*n+i];

        if (ABS(temp)<eps)
        {
            printf("I = %d temp = %lf eps = %lf\n", i, temp, eps);
            return ERROR_APPLICATION;
        }
        denominator = 1/temp;
        for (j=i+1; j<n; ++j)
        {
            a[i*n+j] *= denominator; /* multiplication is faster but division is more accurate */
        }
        for (j=0; j<i; j++)
        {
            x[i*n+j] *= denominator;
        }
        x[i*n+i] = denominator;


        for (k=i+1; k<n; ++k)
        {
            line_a = a + k*n;
            line_x = x + k*n;
            temp = line_a[i];
            for(j=i+1; j<n; ++j)
            {
                line_a[j] -= a[i*n+j]*temp;
            }
            for (j=0; j<i; ++j)
            {
                line_x[j] -= x[i*n+j]*temp;
            }
            line_x[i] = -x[i*n+i]*temp;
        }
    }

    i=n-1;
    for (k=i-1; k>=0; --k)
    {
        temp = a[k*n+i];
        line_x = x + k*n;
        for (j=0; j<=k; ++j)
        {
            line_x[j] -= x[i*n+j]*temp;
        }
        for (j=k+1; j<n; ++j)
        {
            line_x[j] = -x[i*n+j]*temp;
        }
    }
    for (i=n-2; i>=1; --i)
    {
        for (k=i-1; k>=0; --k)
        {
            temp = a[k*n+i];
            line_x = x + k*n;
            for (j=0; j<n; ++j)
            {
                line_x[j] -= x[i*n+j]*temp;
            }
        }
    }


    return SUCCESS;
}

int main(int argc, char * argv[])
{
    double res1, res2, t;
    int ret, res, n, p, k;
    char * name = 0;
    double * a;
    double * x;

    if (argc==4)
    {
        if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1
              && sscanf(argv[3], "%d", &k)==1 && n>0 && k>=1 && k<=4))
        {
            printf("Usage: n p k filename\n");
            return ERROR_ARGS;
        }
    }
    else if (argc==5)
    {
        if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1
              && sscanf(argv[3], "%d", &k)==1 && n>0 && k==0))
        {
            printf("Usage: n p k filename\n");
            return ERROR_ARGS;
        }
        name = argv[4];
    }
    else
    {
        printf("Usage: n p k filename\n");
        return ERROR_ARGS;
    }

    a = (double *)malloc(n*n*sizeof(double));
    if (!a)
    {
        printf("Not enough memory for A\n");
        return ERROR_MALLOC;;
    }

    if (name)
    {
        ret = readMatrix(a, n, n, name);
        if (ret!=SUCCESS)
        {
            switch (ret)
            {
                case ERROR_READ:
                    printf("Cannot read %s\n", name);
                    break;
                case ERROR_OPEN:
                    printf("Cannot open %s\n", name);
                    break;
                default:
                    printf("Unknown Error %d\n", ret);
            }
            free(a);
            return ERROR_READ;
        }
        printf("Read matrix A:\n");
    }
    else
    {
        initMatrix(a, n, n, k);
        printf("Initialized matrix A:\n");
    }
    printMatrix(a, n, n, p);

    x = (double *) malloc(n*n*sizeof(double));
    if (!x)
    {
        printf("Not enough memory for X\n");
        free(a);
        return ERROR_MALLOC;
    }
    initE(x, n);

    t=clock();
    res = GaussSimple(a, x, n);
    t = (clock()-t)/CLOCKS_PER_SEC;
    if (res!=SUCCESS)
    {
        printf("The method is not applicable\n");
        free(a);
        free(x);
        return -1;
    }
    printf("Inverse matrix:\n");
    printMatrix(x, n, n, p);

    if (name)
    {
        ret = readMatrix(a, n, n, name);
        if (ret!=SUCCESS)
        {
            switch (ret)
            {
                case ERROR_READ:
                    printf("Cannot read %s\n", name);
                    break;
                case ERROR_OPEN:
                    printf("Cannot open %s\n", name);
                    break;
                default:
                    printf("Unknown Error %d\n", ret);
            }
            free(a);
            free(x);
            return ERROR_READ;
        }
    }
    else
    {
        initMatrix(a, n, n, k);
    }

    if (n<=4000)
    {
        res1 = result(a, x, n);
        res2 = result(x, a, n);
    }


    printf ("%s : N = %d K = %d\nRes1 = %e Res2 = %e Time = %.2f \n",
            argv[0], n, k, res1, res2, t);

    free(a);
    free(x);
    return 0;
}
