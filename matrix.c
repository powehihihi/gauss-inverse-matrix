#include "matrix.h"
#include "task.h"

int readMatrix (double * a, int n, int m, const char * name)
{
    int k = n*m;
    int i;
    FILE * fp;

    fp = fopen(name, "r");
    if (!fp)
    {
        return ERROR_OPEN;
    }

    for (i=0; i<k; i++)
    {
        if (fscanf(fp, "%lf", a+i)!=1)
        {
            fclose(fp);
            return ERROR_READ;
        }
    }

    fclose(fp);
    return SUCCESS;

}
void printMatrix (double * a, int n, int m, int p)
{
    int np = n<p ? n : p;
    int mp = m<p ? m : p;
    double * line;
    int i, j;

    for (i=0; i<np; i++)
    {
        line = a + i*m;
        for (j=0; j<mp; j++)
        {
            printf(" %10.3e", line[j]);
        }
        printf("\n");
    }
}
double init1 (int n, int m, int i, int j)
{
    return ((n>m ? n : m) - (i>j ? i : j) + 1);
}
double init2 (int n, int m, int i, int j)
{
    (void)n;
    (void)m;
    return (i>j ? i : j);
}
double init3 (int n, int m, int i, int j)
{
    (void)n;
    (void)m;
    return (i>j ? (i-j) : (j-i));
}
double init4 (int n, int m, int i, int j)
{
    (void)n;
    (void)m;
    return (1./(i+j-1));
}
void initMatrix (double * a, int n, int m, int k)
{
    double (*fun[]) (int, int, int, int) = {init1, init2, init3, init4};
    double (*f) (int, int, int, int);
    int num = sizeof(fun)/sizeof(f);
    int i, j;
    double * line;

    if (k<1 || k>num)
    {
        return;
    }

    f = fun[k-1];

    for (i=0; i<n; i++)
    {
        line = a+i*m;
        for (j=0; j<m; j++)
        {
            line[j] = f(n, m, i+1, j+1);
        }
    }
}

void initB (double * a, double * b, int n)
{
    int i, k, sup = (n-1)/2;
    double temp;
    double * line;

    for (i=0; i<n; i++)
    {
        line = a + i*n;
        for (k=0, temp=0; k<=sup; k++)
        {
            temp += line[2*k];
        }
        b[i] = temp;
    }
}

void initSwap(int * swap, int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        swap[i] = i;
    }
}

void initE (double * a, int n)
{
    int i, j;
    double * line;

    for (i=0; i<n; i++)
    {
        line = a + i*n;
        for (j=0; j<i; j++)
        {
            line[j]=0;
        }
        line[j]=1;
        for (j=i+1; j<n; j++)
        {
            line[j]=0;
        }
    }
}

double result(double * a, double * x, int n)
{
    int i, j, k;
    double temp, max=0, sum;

    for (j=0; j<n; j++)
    {
        sum=0;
        for (i=0; i<j; i++)
        {
            for (k=0, temp=0; k<n; k++)
            {
                temp += a[i*n+k]*x[k*n+j];
            }
            sum += ABS(temp);
        }
            for (k=0, temp=0; k<n; k++)
            {
                temp += a[i*n+k]*x[k*n+j];
            }
            sum += ABS(temp-1);
        for (i=j+1; i<n; i++)
        {
            for (k=0, temp=0; k<n; k++)
            {
                temp += a[i*n+k]*x[k*n+j];
            }
            sum += ABS(temp);
        }

        if (max<sum)
        {
            max = sum;
        }
    }

    return max;
}

double matrixNorm (double * a, int n)
{
    int i, j;
    double temp, max=0, sum;

    for (j=0; j<n; j++)
    {
        for (i=0, sum=0; i<n; i++)
        {
            temp = a[i*n+j];
            sum += ABS(temp);
        }
        if (max<sum)
        {
            max = sum;
        }
    }

    return max;
}

int diagCheck(double * a, int n)
{
    int i;
    double temp;
    for (i=0; i<n; i++)
    {
        temp = a[i*n+i];
        if (!(temp>0 || temp<0))
        {
            return (i+1);
        }
    }
    return SUCCESS;
}