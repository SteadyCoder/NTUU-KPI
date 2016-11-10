#include "algorithms.h"

std::vector<int> iter_array;
std::vector<int> tangent_array;
/***********************************
   Functions for iterate algorithm
***********************************/
double find_derivative(double x) {
    return ( - 4 * x * x * x - 6 * x * x - cos(x));
}

double f_x(double x) {
    return (- x * x * x * x - 2 * x * x * x - sin(x) - 0.5);
}

double phi(double x, double l) {
    return x - l * f_x(x);
}

double iterate_algorithm(pair<double, double> segment, double eps, double &limit) {
    double M, m;
    double tmp = find_derivative(segment.first);
    double tmp_one = find_derivative(segment.second);
    if (fabs(tmp) > fabs(tmp_one)) {
        M = tmp;
        m = tmp_one;
    } else {
        M = tmp_one;
        m = tmp;
    }
    
    double q = 1 - m / M;
    double lambda = 1 / M;

    double x0 = segment.first;
    double xk = phi(x0, lambda);
    
    limit = ((1 - q) / q) * eps;
    int count = 0;
    while (fabs(xk - x0) > limit) {
        x0 = xk;
        xk = phi(x0, lambda);
        count++;
    }
    iter_array.push_back(count);
    return xk;
}

/***********************************
   Functions for Newton algorithm
***********************************/
double f_x_p(double x) {
    return (x * x * x * x + 2 * x * x * x + sin(x) + 0.5);
}

double first_deriviate(double x) {
    return (4 * x * x * x + 6 * x * x + cos(x));
}

double second_deriviate(double x) {
    return ( 12 * x * x + 12 * x - sin(x));
}

double compute_m1(pair<double, double> segment) {
    double step = 0.01;
    double min = first_deriviate(segment.first);
    double cur_min = min;
    double result = segment.first;
    double i;

    for (i = segment.first; i < segment.second; i += step) {
        cur_min = first_deriviate(i);
        if (fabs(cur_min) < fabs(min)) {
            min = cur_min;
            result = i ;
        }
    }
    
    return result;
}

double compute_xk(pair<double, double> segment) {
    double result = segment.second;
    
    if(second_deriviate(segment.second) * f_x_p(segment.second) > 0) 
        result = segment.second;
    if (second_deriviate(segment.first) * f_x_p(segment.first) > 0) 
        result = segment.first;
    
    return result;
}


double tangent_algorithm(pair<double, double> segment, double eps, double &limit) {
    double xk = compute_xk(segment);
    double m1 = compute_m1(segment) ;
    int count = 0;
    while ( fabs(f_x_p(xk) / m1) > eps) {
        xk = xk - f_x_p(xk) / first_deriviate(xk);
        count++;
    }
    limit = fabs(f_x_p(xk) / m1); 
    tangent_array.push_back(count);
    return xk;
}

/***********************************
   Functions for output
***********************************/

void print_line() {
    printf("---------------------------------------------------------------\n");
}

void table_one(pair<double, double> segment) {
    printf("\nIterative method\n");
    print_line();
    printf(" eps \t|\t Значение корня\t|\tОценка точности методом И|\t\n");
    print_line();
    double eps = 1e-2, result, lim;

    for (int i = 0; i < 4; ++i) {
        result = iterate_algorithm(segment, eps, lim);
        printf(" %g |\t %.11g\t|\t%11.g\t|\n", eps, result, lim);
        print_line();
        eps = eps * 1e-3;
    }
}

void table_two(pair<double, double> segment) {
    printf("\n Newtow method\n");
    print_line();
    printf(" eps \t|\t Значение корня\t|\tОценка точности методом Д|\t\n");
    print_line();
    double eps = 1e-2, result, lim;

    for (int i = 0; i < 4; ++i) {
        result = tangent_algorithm(segment, eps, lim);
        printf(" %g |\t %.11g\t|\t%.11g\t|\n", eps, result, lim);
        print_line();
        eps = eps * 1e-3;
    }
}

void table_three() {
    double eps = 1e-2;
    printf("\nComparing\n");
    print_line();
    printf(" eps \t|Количество итераций методом И\t|Количество итераций методом Д|\t\n");
    for (int i = 0; i < 4; ++i) {
        printf(" %g\t|\t\t%d\t\t|\t%d\t\t|\n", eps, iter_array[i], tangent_array[i]);
        eps = eps * 1e-3;
        print_line();
    }
   
}

