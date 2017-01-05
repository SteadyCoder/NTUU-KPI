#include "algo.hpp"

/****************
Main function:
    0.5 * e^( x^(1 / 3) ) * sin(3 * x)
****************/

int main() {
	int N = 200;
	FILE *f1 = fopen("x_values.txt", "w");
	FILE *f2 = fopen("y_values.txt", "w");;
	
	spline(a, b, N, f1, f2);

	fclose(f2);
	fclose(f1);
	return 0;
}
