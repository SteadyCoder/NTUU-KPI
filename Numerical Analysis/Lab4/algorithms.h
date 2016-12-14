#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;
/*********************
Function:
    ∫( (ln x) ^ 2 / x * dx )
    [1, 23]

Primitive:
    ((ln x) ^ 3) / 3
**********************/

// Methods
double general_trapezoid(double, double, double);
double recalculation_trapezoid(double, double, double, double &);

// Output 
void print_header_one();
void print_row(int amount);
