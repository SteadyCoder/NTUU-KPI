#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <vector>

using namespace std;


// First segment 
const pair <double, double> segment_one = std::make_pair(-2.2955, -1.7955);
// Second segment
const pair <double, double> segment_two = std::make_pair(-0.655015, -0.155015);

double iterate_algorithm(pair<double, double> segment, double eps);
double tangent_algorithm(pair<double, double> segment, double eps);

void table_one(pair<double, double> segment);
void table_two(pair<double, double> segment);
void table_three();
