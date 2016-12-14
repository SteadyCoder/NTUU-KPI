#include "algorithms.h"
/********************
Function:
    ∫( (ln x) ^ 2 / x * dx )
    [1, 23]

Primitive:
    ((ln x) ^ 3) / 3
*********************/

const double a = 1.0;
const double b = 23.0;

double primitive(double x) {
    return ( log(x) * log(x) * log(x) / 3 );
}

double second_primitive(double x) {
    return ( (1 - log(x) ) / x * x );
}

int main() {
    // Exact value 
    double answer = primitive(b) - primitive(a);
    double M2 = fabs(second_primitive(b));
    double eps = 1e-2;
    double h = sqrt((12 * eps) / (b - a) * M2) - 0.1;
    int precision;
    double result = 0.0;

    cout << "General method " << endl;
    print_header_one();
    vector <double> delta;
    double d = 0.0;
    while (eps > 1e-10) {
        precision = 14;
        result = general_trapezoid(a, b, h);
        cout << "| " << setprecision(0) << std::scientific << eps << " |";
        cout << setprecision(precision) << std::fixed << answer << "  | ";
        cout << result << " |";
        cout << h << " | ";
        
        d = fabs(answer - result);
        delta.push_back(d);

        cout << d << " |";
        cout << endl;
        eps = eps * 1e-1;
        h = sqrt(12 * eps / (b - a) * M2);
    }
    print_row(85);
/*
    cout << "Deltas " << endl;
    for (int i = 0; i < delta.size(); ++i) {
        cout << delta[i] << " ";
    }   
*/
  //  cout << endl;

    eps = 1e-2;
    cout << "Method with two recalculations" << endl;
    print_header_one();
    for (int i = 0; i < delta.size(); ++i) {
        precision = 14;
        eps = delta[i];
        result = recalculation_trapezoid(a, b, eps, h);
        cout << "| " << setprecision(0) << std::scientific << eps << " |";
        cout << setprecision(precision) << std::fixed << answer << "  | ";
        cout << result << " |";
        cout << h << " | ";
        cout << fabs(answer - result) << " |";
        cout << endl;
        eps = eps * 1e-1;
    }
    print_row(85);
    
    return 0;
}
