#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

// Some constamts
const double a(2);
const double b(8);
const double eps(1e-5);

// function to approximate
double function(double x);

std::vector<double> claculate_a(double a, double b, int N);
std::vector<double> calculate_b(std::vector<double> C, std::vector<double> D, double a, double b, int N);
std::vector<double> calculate_c(double a, double b, int N);
std::vector<double> calculate_d(std::vector<double> C, double a, double b, int N);

// Some actions to make matrix ready for gauss method
void remake_matrix(std::vector<std::vector<double> > &m, int N, double a, double b);

double s_i_calculate(double x, std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D, double a, double b, int N);
std::vector<double> gauss_method(std::vector<std::vector<double> > &m);

// write to file x and y coordinates
void spline(double a, double b, int N, FILE *f1, FILE *f2);
