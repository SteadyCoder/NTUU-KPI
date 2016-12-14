#include "algorithms.h"

/*********************
Function:
    ∫( (ln x) ^ 2 / x * dx )
    
    [1, 23]

Primitive:
    ((ln x) ^ 3) / 3
**********************/
// Function
double func(double x) {
    return ( log(x) * log(x) / x );
}

double general_trapezoid(double a, double b, double h) {
    double result = 0.0;
    double x = a;
    int n = (b - a) / h;
    result = (func(a) + func(b)) / 2;   
    h  = (b - a) / n;
    //cout << "p = " << h * n << endl; 
    // Main Loop
    for (int i = 1; i < n; ++i) {
        x = x + h; 
        result = result + func(x);
    }
    result = result * h;
    
    return result;
}


double recalculation_trapezoid(double a, double b, double eps, double &h) {
    double result = 0.0;
    double I_n, I_2n;
    double n = (b - a) / sqrt(eps);
    n = 1 / sqrt(eps);
    h = (b - a) / n;

    I_n = general_trapezoid(a, b, h);

    n *= 2;
    h = (b - a) / n;

    I_2n = general_trapezoid(a, b, h);
    
    // Main loop    
    while (fabs(I_n - I_2n) > 3 * eps) {
        I_n = I_2n;   
        h = h / 2;
        I_2n = general_trapezoid(a, b, h);
    }

    result = I_2n;
            
    return result;
}


void print_row(int amount) {
    for (int i = 0; i < amount; ++i) 
        cout << "-";
    cout << endl;
} 

void print_header_one() {
    print_row(85);
    cout << "| Eps  |" << setw(10) << " I_real" << setw(10) << "|" << setw(10) << "I" << setw(10) << "|" << "h" << setw(17) << "|" << setw(10) << "delta" << setw(9) << "|" << endl;
    print_row(85);
}
