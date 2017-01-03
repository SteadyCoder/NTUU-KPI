#include "algorithms.hpp"

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

double function(double x) { return 0.5 * exp ( pow(x, 1 / 3.0) ) * sin (3 * x); }

double chebyshov_polynomial(double x, int n) 
{
	if (n == 0) return 1;
	if (n == 1) return x;

	double t_prev = 1;
	double t_curr = x;
	double tmp;

	for (int i = 2; i <= n; ++i) 
    {
		tmp = t_curr;
		t_curr = 2 * x * t_curr - t_prev;
		t_prev = tmp;
	}
	return t_curr;
}

// Part of equation before '=' in normal system
double base_member(double x, int n1, int n2) 
{
	return chebyshov_polynomial(x, n1) * chebyshov_polynomial(x, n2);
}

// Part of equation after '=' in normal system
double free_member(double x, int n) 
{
	return function(x) * chebyshov_polynomial(x, n);
}


double simpson_rule(double a, double b, double h, int n1, int n2)
{
	int n = (int)((b - a) / h);
	h = (b - a) / n;
	double result = 0;

	double x0 = a;
	double x1 = a + h;
	double half_h = h / 2.0;
	if (n2 != -1)
    {
		for (int i = 0; i <= n - 1; ++i)
        {
			result += base_member(x0, n1, n2) + 4.0 * base_member(x0 + half_h, n1, n2) + base_member(x1, n1, n2);
			x0 += h;
			x1 += h;
		}
	}
	else 
    {
		for (int  i = 0; i <= n - 1; ++i)
        {
			result += free_member(x0, n1) + 4.0 * free_member(x0 + half_h, n1) + free_member(x1, n1);
			x0 += h;
			x1 += h;
		}
	}
	return (h / 6.0) * result;
}

double integration(double a, double b, double eps, int n1, int n2) 
{
	double h = sqrt(sqrt(eps));
	double result;
	double curr_sum = 0;

	if (n2 == -1) 
    {
 		result  = simpson_rule(a, b, h, n1);
		while (eps <= fabs(result - curr_sum) / result) 
        {
			curr_sum = result;
			h = h / 2.0;
			result = simpson_rule(a, b, h, n1);
		}
	}
	else 
    {
 		result  = simpson_rule(a, b, h, n1, n2);
		while (eps <= fabs(result - curr_sum) / result)
        {
			curr_sum = result;
			h = h / 2.0;
			result = simpson_rule(a, b, h, n1, n2);
		}
	}
	return result;
}


void remade_matrix(std::vector<std::vector<double> > &matrix, int n, double a, double b, double eps) 
{
	int columns = n + 2;
	matrix.resize(n + 1);
	for (int i = 0; i <= n; ++i) 
    {
		matrix[i].resize(columns);
		for (int j = 0; j <= n; ++j)
			matrix[i][j] = integration(a, b, eps, j, i);

		matrix[i][n + 1] = integration(a, b, eps, i);
	} 
}



std::vector<double> gauss_method(std::vector<std::vector<double> > &matrix)
{
	int k = 0;
	int columns = matrix[0].size();
	int n = matrix.size();
	int free_el = columns - 1;
	double diagonal_element;
	std::vector<double> tmp;
	std::vector<double> result(n);

	while (k < n)
    {
		diagonal_element = matrix[k][k]; 

        for (int column = 0; column < columns; ++column)
			matrix[k][column] = matrix[k][column] / diagonal_element;

		for (int i = 0; i < n; ++i)
        {
			if (i == k) continue;
            
			tmp = matrix[k];
			std::transform(tmp.begin(), tmp.end(), tmp.begin(),
				std::bind1st(std::multiplies<double>(), matrix[i][k]));

			std::transform(matrix[i].begin(), matrix[i].end(), tmp.begin(), matrix[i].begin(), std::minus<double>());
		}
		++k;
	}

	for (int i = 0; i < n; ++i)
		result[i] = matrix[i][free_el];

	return result;
}


double power(double x, int n) 
{
	if (n == 0) return 1;
	if (n == 1) return x;

	double res = 1;
	for (int i = 0; i < n; ++i)
		res *= x;

	return res;
}


double calculate_polynomial(std::vector<double> vect, double x) 
{
	double P_x = 0;
	for (auto i = 0; i < vect.size(); ++i)
		P_x += vect[i] * chebyshov_polynomial(x, i);

	return P_x;
}


double standart_deviation(double a, double b, std::vector<double> alpha, double eps) {
	double x = a;
	double tmp;
	double result = 0;
	double h = sqrt(eps);
	int n = (int)((b - a) / h);
	h = (b - a) / n;

	for (int i = 0; i < n; ++i) 
    {
		tmp = function(x)  - calculate_polynomial(alpha, x);
		result += tmp * tmp;
		x += h;
	}
	return sqrt(result/(n + 1));
}


void print_res(double a, double b, std::vector<double> alpha, double eps, FILE *f1, FILE *f2) 
{
	double x = a;
	double tmp;
	double h = sqrt(eps);
	int n = (int)((b - a) / h);
	h = (b - a) / n;
	for (int i = 0; i < n; ++i) 
    {
		tmp = calculate_polynomial(alpha, x); 
		fprintf(f1, "%.3g\n", x);
		fprintf(f2, "%.3g\n", tmp);
		x += h;
	}
}

