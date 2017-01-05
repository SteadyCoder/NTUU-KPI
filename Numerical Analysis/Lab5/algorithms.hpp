#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

// Interval for main function
const double a(2);
const double b(8);

const double eps(1e-5);

double function(double x);

// Function for solving normal system

// Part of equation before '='
double base_member(double x, int n1, int n2);
// Part of equation after '='
double free_member(double x, int n);

// Functions for quadratic approximation 
double chebyshov_polynomial(double x, int n);
double simpson_rule(double a, double b, double h, int n1, int n2 = -1);
double integration(double a, double b, double eps, int n1, int n2 = -1);
std::vector<double> gauss_method(std::vector<std::vector<double> > &matrix);

void remade_matrix(std::vector<std::vector<double> > &matrix, int n, double a, double b, double eps);
double calculate_polynomial(std::vector<double> vect, double x);

// Additinoal functions
double power(double x, int n);
double standart_deviation(double a, double b, std::vector<double> alpha, double eps);
void print_res(double a, double b, std::vector<double> alpha, double eps, FILE *f1, FILE *f2);
