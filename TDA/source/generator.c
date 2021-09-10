#include "source.h"


double mean(double* values, int n)
{
    int i;
    double s = 0;

    for (i = 0; i < n; i++)
        s += values[i];
    return s / n;
}


double stddev(double* values, int n)
{
    int i;
    double average = mean(values, n);
    double s = 0;

    for (i = 0; i < n; i++)
        s += (values[i] - average) * (values[i] - average);
    return sqrt(s / (n - 1));
}


double* generate(int n,double a, double b, double scale)
{
    double* values = (double*)calloc(n, sizeof(double));

    if (values)
    {
        if (a == 0 && b == 0)
        {
            for (int i = 0; i < n; i++) 
            {
                values[i] = ((double)rand() / (double)(RAND_MAX)) * scale;
            }            
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                double scale = rand() / (double)RAND_MAX;
                values[i] = a + scale * (b - a);
            }
        }
    }
    return values;
}


double* rayGen(int n, double a, double b, double scale)
{
    double* bufferA = (double*)calloc(n, sizeof(double));
    double* bufferB = (double*)calloc(n, sizeof(double));
    double* result = (double*)calloc(n, sizeof(double));

    bufferA = generate(n, a, b, scale);
    bufferB = generate(n, a, b, scale);

    double scaleA = stddev(bufferA, n);
    double scaleB = stddev(bufferB, n);

    double rayScale = (scaleA + scaleB) / 2;

    if (result)
    {
        for (int i = 0; i < n; i++)
        {
            result[i] = sqrt(pow(bufferA[i], 2) + pow(bufferB[i], 2));
        }
    }
    
    free(bufferA);
    free(bufferB);

    return result;

}

int* generateInt(int n, int a, int b)
{
    int* values = (int*)calloc(n, sizeof(int));

    if (values)
    {
        for (int i = 0; i < n; i++)
        {
            values[i] = rand() % b + a;
        }
        
    }

    return values;
}

int* rayGenInt(int n, int a, int b)
{
    int* bufferA = (int*)calloc(n, sizeof(int));
    int* bufferB = (int*)calloc(n, sizeof(int));
    int* result = (int*)calloc(n, sizeof(int));

    bufferA = generateInt(n, a, b);
    bufferB = generateInt(n, a, b);
    
    if (result)
    {
        for (int i = 0; i < n; i++)
        {
            
            result[i] = (int)sqrt(pow(bufferA[i], 2) + pow(bufferB[i], 2));
        }
    }

    free(bufferA);
    free(bufferB);

    return result;

}

