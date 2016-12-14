#include "computing.h"
#define _USE_MATH_DEFINES 

const double a = -6.2;
const double b = 35.7;
const double exponent = M_E;
const char *space = " ";
double eps = 1e-8;

const double x() { return a; }

long double fractional_part(int &n, int x_int, double x, bool flag) {
    long double u = 1;
    long double sum = 1;
    if (flag) {
        int k = 1;
        while (std::abs(u) >= eps / exp(x_int)) {
            u = (x / k) * u;
            k++;
            sum = sum + u;
        } 
        n = k - 1;
    } else if (!flag) {
        int k = 1;
        for (int i = 0; i < n; i++) {
            u = (x / k) * u;
            k++;
            sum = sum + u;
        }
    }

    return sum;
}

double remainder_compute(double x, int n) {
    double fact = 1;
    for(int i = 1; i < n + 1; i++) 
        fact *= i;
    long double pow_x = 1;
    for (int i = 0; i < n + 1; ++i)
        pow_x = pow_x * x; 
    
    long double result = pow_x / (fact * (1 - fabs(x) / (n + 2)));
    return result;
}

long double exp_result(double x, int &n, double &remainder, bool flag) {

    int x_int = (int)x;
    double x_div = x - x_int;

    long double integer_result = exp(x_int);
    long double fractional_result = fractional_part(n, x_int, x_div, flag);

    remainder = remainder_compute(x_div, n);
    
    long double result = integer_result * fractional_result;

    return result;
}

void print_row(double eps, int n, long double ph, double remaind) {
    if (n == 12)
        printf("| %g\t|  %d  |%5s%10.40Lg\t|\t%.15g\t|\n", eps, n, space, ph, remaind);
    else
        printf("| %g\t|  %d  |%5s%10.40Lg\t\t|\t%.15g\t|\n", eps, n, space, ph, remaind);
}

void print_line() {
    printf("--------------------------------------------------------------------------------------------------\n");
}

void table_one(int& series_length) {
    bool fl = true;
    int last_element_number = 0;
    double remaind = 0.0;
    double e = exp(x());
    printf("Table with state interval\n");
    print_line();
    printf("| eps\t|  n   |%5sAbsolute pohibka\t\t\t\t\t|\tZalyhkovyi chlen\t|\n", " ");

    eps = 0.01;
    long double my_e = exp_result(x(), last_element_number, remaind, fl);
    print_row(eps, last_element_number, std::abs(e - my_e), remaind);

    eps = 1e-5;
    my_e = exp_result(x(), last_element_number, remaind, fl);
    print_row(eps, last_element_number, std::abs(e - my_e), remaind);

    eps = 1e-8;
    my_e = exp_result(x(), last_element_number, remaind, fl);
    series_length = last_element_number;
    print_row(eps, last_element_number, std::abs(e - my_e), remaind);

    eps = 1e-14;
    my_e = exp_result(x(), last_element_number, remaind, fl);
    print_row(eps, last_element_number, std::abs(e - my_e), remaind);

    print_line();
    print_line();
    print_line();
    
}

double x_i(int i) {
    return a + (b - a) / 10 * i;
}

void print_row_two(double x, long double abs_pohib, double zal_ch) {
    printf("|\t%g\t|\t%.15Lg\t|\t%.15g\t|\n", x, abs_pohib, zal_ch);
}

void table_two(int length) {
    eps = 1e-8;
    bool fl = false;
    printf("Table with different interval\n");
    print_line();
    printf("|\tx_i\t|\tAbsoulute pohibka\t|\tZalyhkovyi chlen\t|\n");
    for (int i = 0; i < 10; i++) {
        double remaind = 0.0;
        int last = 0;
        long double result = exp_result(x_i(i), length, remaind, fl);
        long double exect_result = exp(x_i(i));
        print_row_two(x_i(i), std::abs(exect_result - result), remaind);
    }
    print_line();

}

