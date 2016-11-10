#include "algorithms.h"

int main() {
    // Answers
    double x1 = -2.0455;
    double x2 = -0.405015;
    
//    printf("%.11g\n", tangent_algorithm(segment_two, 1e-11));
//    printf("%.11g\n", tangent_algorithm(segment_one, 1e-11));

    table_one(segment_one);
    table_one(segment_two);

    table_two(segment_one);
    table_two(segment_two);
    
    table_three();

    return 0;
}
