#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef vector<vector<float>> matrix;

void print_vec(matrix v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
    cout << "*********************" << endl
         << endl;
}

matrix vec_mul(matrix A, matrix B)
{
    matrix C;
    int m1 = A.size();
    int n1 = A[0].size();
    int m2 = B.size();
    int n2 = B[0].size();

    // Cant multiply matrices
    if (n1 != m2)
        return C;

    for (int i = 0; i < m1; i++)
    {
        vector<float> row;
        for (int j = 0; j < n2; j++)
        {
            float temp = 0;
            for (int k = 0; k < n1; k++)
                temp += (A[i][k] * B[k][j]);
            row.push_back(temp);
        }
        C.push_back(row);
    }
    return C;
}

inline double radians(double deg)
{
    return deg * (M_PI / 180.0);
}