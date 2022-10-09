#include "task.h"
#include "matrix.h"


int Gauss(double * a, double * x, int * swap, int n)
{
    int i, j, k, line_max, column_max;
    double temp, denominator, eps, max;
    double * line4;
    double * line3;
    double * line2;
    double * line1;

    eps = EPS * matrixNorm(a, n);
    for (i=0; i<n; ++i)
    {
        max = fabs(a[i*n+i]);
        line_max = i;
        column_max = i;
        for (k=i; k<n; ++k)
        {
            for (j=i; j<n; ++j)
            {
                temp = fabs(a[i*n+j]);
                if (temp>max)
                {
                    max = temp;
                    column_max = j;
                    line_max = i;
                    
                }
            }
        }
        if (max < eps)
        {
            return ERROR_APPLICATION;
        }

        if (i!=line_max)
        {
            line1 = a+i*n;
            line2 = a+line_max*n;
            line3 = x+i*n;
            line4 = x+line_max*n;
            for (j=0; j<n; ++j)  //  optimize
            {
                temp = line2[j];
                line2[j] = line1[j];
                line1[j] = temp;
                temp = line4[j];
                line4[j] = line3[j];
                line3[j] = temp;
            }
        }
        if (i!=column_max)
        {
            line1 = a+i;
            line2 = a+column_max;
            for (k=0; k<n; ++k)
            {
                temp = line1[k*n];
                line1[k*n] = line2[k*n];
                line2[k*n] = temp;
            }
            swap[i] = column_max;
        }

        denominator = a[i*n+i];
        for (j=i+1; j<n; ++j)
        {
            a[i*n+j] /= denominator;
        }
        for (j=0; j<n; ++j)
        {
            x[i*n+j] /= denominator;
        }

        for (k=i+1; k<n; ++k)
        {                            // optimize line1 line2
            line1 = a + k*n;
            line2 = a + i*n;
            line3 = x + k*n;
            line4 = x + i*n;
            temp = line1[i];

            for (j=i+1; j<n; ++j)     // optimize j=i
            {
                line1[j] -= temp*line2[j];
            }
            for (j=0; j<n; ++j)
            {
                line3[j] -= temp*line4[j];
            }

        }
    }


    for (i=n-1; i>0; --i)
    {
        for (k=i-1; k>=0; --k)
        {
            temp = a[k*n+i];
            line1 = x + k*n;
            for (j=0; j<n; ++j)
            {
                line1[j] -= x[i*n+j]*temp;
            }
        }
    }

    for (i=n-1; i>=0; --i)
    {
        if (swap[i]!=i)
        {
            line1 = x + swap[i]*n;
            line2 = x + i*n;
            for (j=0; j<n; j++)
            {
                temp = line1[j];
                line1[j] = line2[j];
                line2[j] = temp;
            }
        }
    }

    return SUCCESS;
}

int main(int argc, char * argv[])
{
    double res1=0, res2=0, t;
    int ret, res, n, p, k;
    char * name = 0;
    double * a;
    double * x;
    int * swap;

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

    swap = (int *)malloc(n*sizeof(int));
    if (!swap)
    {
        printf("Not enough memory for extra vector!\n");
        free(a);
        free(x);
        return ERROR_MALLOC;
    }
    initSwap(swap, n);

    t=clock();
    res = Gauss(a, x, swap, n);
    t = (clock()-t)/CLOCKS_PER_SEC;
    if (res!=SUCCESS)
    {
        printf("The method is not applicable\n");
        free(a);
        free(x);
        free(swap);
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
            free(swap);
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
    free(swap);
    return 0;
}
