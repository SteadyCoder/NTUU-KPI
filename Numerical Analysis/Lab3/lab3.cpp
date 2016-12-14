#include "algorithm.h"

const int n = 4;
const int m = 5;

int main() {
    //Initial matrix
    vector < vector<double> > matrix { 
        { 3.0, 2.0, 8.0, 3.0, 35.0 },
        { 17.0, 51.0, 13.0, 20.0, 407.0 },
        { 0.0, 3.0, 7.0, 3.0, 28.0 } ,
        { 16.0, 4.0, 20.0, 16.0, 124.0 } 
    };
    cout << "Gauss jordan method" << endl;   
    vector<double> answer = gauss_jordan_method(matrix, n, m);
    print_vector(answer, 0);

    // Matrix with diagonally dominant
    vector< vector<double> > p_matrix {
        {16.0, -8.0, -8.0, 4.0, 12.0},
        {1.0, 47.0, -7.0, 4.0, 283.0},
        {0.0, 6.0, 14.0, 6.0, 56.0},
        {13.0, 2.0, 12.0, 13.0, 89.0}
    };
    
    // Just set this variable to number decimal digitals after comma
    int decimal_part_length = 3;

    double precision = 1;
    for (int i = 0; i < decimal_part_length; ++i) {
        precision *= 0.1;
    }

    cout << "Seidel method" << endl;
    vector<double> answer_two = seidel(p_matrix, n, precision);
    print_vector(answer_two, decimal_part_length);
    
    return 0;
}


