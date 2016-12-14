#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <functional>   

using namespace std;

vector<double> gauss_jordan_method(vector< vector<double> > a, const int n, const int m);

vector<double> seidel(vector< vector<double> > m, const int n, double eps);

void print_matrix(vector< vector<double> >, const int, const int);
void print_vector(vector<double>, int precision = 3);
