#include "algorithms.hpp"

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

const char *x_file = "x_values.txt";
const char *y_file = "y_values.txt";

int main() 
{
	std::vector<std::vector<double> > matrix;
    // Filled my gauss method
	std::vector<double> alpha;
	FILE *f1 = fopen(x_file, "w");
	FILE *f2 = fopen(y_file, "w");
	
    const double exit_state = 0.01;
	
	double deviation = 1;
	int polynomial_degree = 3;
	printf("Degree\t Deriviative\n");

    while (deviation > exit_state) {
		remade_matrix(matrix, polynomial_degree, a, b, eps);
		alpha = gauss_method(matrix);
		deviation = standart_deviation(a, b, alpha, eps);
		printf("%2i\t%10.4g\n", polynomial_degree, deviation);
		++polynomial_degree;
	}

	print_res(a, b, alpha, eps, f1, f2);
	fclose(f2);
	fclose(f1);
	return 0;

}
