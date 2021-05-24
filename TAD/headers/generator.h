#pragma once


double mean(double* values, int n);
double stddev(double* values, int n);
double* generate(int n, double a, double b, double scale);
double* rayGen(int n, double a, double b, double scale);
int* generateInt(int n, int a, int b);
int* rayGenInt(int n, int a, int b);

