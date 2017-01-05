#include "algo.hpp"

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

double function(double x) {
    return 0.5 * exp( pow(x, 1 / 3.0) ) * sin(3 * x);
}

std::vector<double> calculate_a(double a, double b, int N) {
	std::vector<double> result(N);
	double h = (b - a) / N;
	double x = a;
	for (int i = 0; i < N; ++i) {
		result[i] = function(x);
		x += h;
	}
	return result;
}


void remake_matrix(std::vector<std::vector<double> > &m, int N, double a, double b) {
	m.resize(N);
	int columns  = N + 1;
	double h  = (b - a) / N;
	double fcurr, fprev, fnext;
	for (int i = 0; i < N; ++i)
		m[i].resize(columns);

	m[0][0] = 1;
	m[N - 1][N - 1] = 1;
	int n = N - 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (i == j)
				m[i][j] = 2 * h;
			else if ((i - 1) == j || (i + 1) == j)
				m[i][j] = h;
			else if (j == N) {
				fprev = function(a + h * (i - 1));
				fcurr = function(a + h * i);
				fnext = function(a + h * (i + 1));
				m[i][j] = 6 * (fnext - 2 * fcurr + fprev) / h;
			}
			else
				m[i][j] = 0;
		}
	}
}



std::vector<double> gauss_method(std::vector<std::vector<double> > &m){
	int k = 0;
	int columns = m[0].size();
	int n = m.size();
	int free_el = columns - 1;
	double A;
	std::vector<double> tmp;
	std::vector<double> result(n);

	while (k < n) {
		A = m[k][k]; // diagonal element 
		for (int col = 0; col < columns; ++col)
			m[k][col] = m[k][col] / A;

		for (int i = 0; i < n; ++i) {
			if (i == k)
				continue;
			tmp = m[k];
			std::transform(tmp.begin(), tmp.end(), tmp.begin(),
				std::bind1st(std::multiplies<double>(), m[i][k]));

			std::transform(m[i].begin(), m[i].end(), tmp.begin(), m[i].begin(), std::minus<double>());
		}
		++k;
	}

	for (int i = 0; i < n; ++i)
		result[i] = m[i][free_el];

	return result;
}


std::vector<double> calculate_c(double a, double b, int N) {
	std::vector<std::vector<double> > m;
	std::vector<double> result;
	remake_matrix(m, N, a, b);
	result = gauss_method(m);
	return result;
}


std::vector<double> calculate_d(std::vector<double> C, double a, double b, int N) {
	std::vector<double> D(N);
	double h = (b - a) / N;
	D[0] = C[0];
	for (int i = 1; i < N; ++i) 
		D[i] = (C[i] - C[i - 1]) / h;

	return D;
}


std::vector<double> calculate_b(std::vector<double> C, std::vector<double> D, double a, double b, int N) {
	std::vector<double> B(N);
	double h = (b - a) / N;
	double fcurr, fprev;
	B[0] = 0;
	for (int i = 1; i < N; ++i) {
		fcurr = a + h * i;
		fprev = a + h * (i - 1);
		B[i] = h * C[i] / 2 - h * h * D[i] / 6 + (fcurr - fprev) / h;
	}
	return B;
}


double s_i_calculate(double x, std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D, double a, double b, int N) {
	double h = (b - a) / N;
	int i = 0;
	double xi = a + i * h;
	double res, delta;
	while (x > xi) {
		++i;
		xi = a + i * h;
	}
	--i;
	xi = a + i * h;
	delta = x - xi;
	res = A[i] + B[i] * delta + C[i] * delta * delta / 2 + D[i] * delta * delta * delta / 6;
	return res;
}


void spline(double a, double b, int N, FILE *f1, FILE *f2) {
	double h = (b - a) / N;
	double x, y;
	std::vector<double> A = calculate_a(a, b, N);
	std::vector<double> C = calculate_c(a, b, N);
	std::vector<double> D = calculate_d(C, a, b, N);
	std::vector<double> B = calculate_b(C, D, a, b, N);
	x = a + h;
	for (int i = 1; i < N; ++i) {
		y = s_i_calculate(x, A, B, C, D, a, b, N);
		fprintf(f1, "%.3g\n", x);
		fprintf(f2, "%.3g\n", y);
		x += h;	
	}
}
