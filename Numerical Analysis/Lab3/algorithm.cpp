#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

void print_matrix(vector< vector<double> > a, const int n, const int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m ; ++j) 
            cout << a[i][j] << " ";
        cout << endl;
    }
}

/***********************
    Gauss jordan method
***********************/
vector<double> row_multiplication(vector< vector<double> > a, const int n, const int m, int row_number, double multiplier) {
    vector<double> result(m, 0);

    for (int i = 0; i < m; ++i) {
        result[i] = a[row_number][i] * multiplier;
    }

    return result;
}

void row_substraction(vector< vector<double> > &a, const int n, const int m, int row_number, vector< double > substracted_row) {
    for (int i = 0; i < m; ++i) {
        a[row_number][i] = a[row_number][i] - substracted_row[i];
    }
}

vector<double> gauss_jordan_method(vector< vector<double> > a, const int n, const int m) {
    vector<double> result(n);
    
    for (int row = 0; row < n; ++row) {
        double a_i_j = a[row][row];

        for (int i = 0; i < m; ++i)
            a[row][i] = a[row][i] / a_i_j;
        
        for (int k = 0; k < n; ++k) {
            if (k == row)
                continue;
            vector<double> r = row_multiplication(a, n, m, row, a[k][row]);
            row_substraction(a, n, m, k, r);
        }
    }

    for (int i = 0; i < n; ++i) 
        result[i] = a[i][m - 1];

    return result;
}


/***********************
    Seidel method
***********************/
void print_vector(vector<double> a, int precision) {
    int precision_default = std::cout.precision();
    
    for (int i = 0; i < a.size(); ++i)
        cout << std::setprecision(precision) << std::fixed << a[i] << " ";
    cout << std::setprecision(precision_default) << endl;
}

double vector_sum(vector<double> a) {
    double result = 0.0;

    for (int i = 0; i < a.size(); ++i)
        result = result + fabs(a[i]);

    return result;
}

double find_min(vector<double> v) {
    double result = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] < result) 
            result = v[i];       
    }
    return result;
}

double find_max(vector<double> v) {
    double result = v[0];
    for (int i = 0; i < v.size(); ++i) 
        if (result < v[i] and v[i] < 1)
            result = v[i];
    return result;
}

double find_m_norm(vector< vector<double> > alpha, int n) {
    double result = 0.0;
    vector<double> v_sums(n, 0);
    
    for (int i = 0; i < n; ++i) {
        v_sums[i] = vector_sum(alpha[i]);
    }
    
    result = v_sums[0];
    for (int i = 0; i < n; ++i) {
        if (v_sums[i] < result)
            result = v_sums[i];
    }
    return result;
}

vector<double> seidel(vector< vector<double> > m, const int n, double eps) {
	vector<double> beta(n, 0);
	vector< vector<double> > alpha(n, vector<double>(n, 0));
    vector<double> Xk1(n, 0);
    vector<double> Xk(n, 0);

	double m_norm = 0;
    double sum_a = 0.0;

	for (int i = 0; i < n; ++i) {
		if (m[i][i] == 0) {
			return Xk1;
		}
		beta[i] = m[i][n] / m[i][i];
		for (int j = 0; j < n; ++j) {
			alpha[i][j] = -m[i][j] / m[i][i];
            alpha[i][i] = 0;
		}
	}
    
    m_norm = find_m_norm(alpha, n);

	double eval = 0.0, new_x, sum_one, sum_two;

    // First approximation
    for (int i = 0; i < n; ++i) {
        new_x = beta[i];
        sum_one = 0;
        for (int j = 0; j < n; ++j) 
            sum_one = sum_one + beta[j];
        
        new_x = new_x + sum_one;
        Xk1[i] = new_x;
    }

    vector<double> tmp(n, 0);
    for (int i = 0; i < n; ++i) 
        tmp[i] = fabs(Xk1[i] - beta[i]);
    
    eval = (1 - m_norm) / m_norm + 1;
    Xk = Xk1;
    
    while (eval > eps * (1 - m_norm) / m_norm) {

       for (int i = 0; i < n; ++i) {
            new_x = beta[i];
            sum_one = 0;
            for (int j = 0; j < i; ++j)
                sum_one = sum_one + alpha[i][j] * Xk1[j];

            sum_two = 0;
            for (int j = i; j < n; ++j)
                sum_two = sum_two + alpha[i][j] * Xk[j];

            new_x = new_x + sum_one + sum_two;
            Xk1[i] = new_x;
        }

        eval = 0.0;
        for (int i = 0; i < n; ++i) {
            tmp[i] = fabs(Xk1[i] - Xk[i]);
            eval += tmp[i];
        }
        
        Xk = Xk1;
    }

	return Xk1;
}
