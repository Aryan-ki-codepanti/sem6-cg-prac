#include <iostream>
#include <cmath>
#include <graphics.h>
using namespace std;

typedef float matrix[4][4];
matrix basis = {0};

void init_basis()
{
    basis[0][0] = 2;
    basis[0][1] = -2;
    basis[0][2] = 1;
    basis[0][3] = 1;

    basis[1][0] = -3;
    basis[1][1] = 3;
    basis[1][2] = -2;
    basis[1][3] = -1;

    basis[2][2] = 1;
    basis[3][0] = 1;
}

// 4x4 and 4 x 3
void matrix_mul(matrix A, matrix B, matrix &C)
{
    int n = 3;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += (A[i][k] * B[k][j]);
        }
    }
}

void hermite(int steps, matrix G)
{
    matrix temp = {0};

    matrix_mul(basis, G, temp);

    initwindow(600, 600, "Hermite Curve");

    float step_size = 1.0 / steps;
    float t = 0;

    float x, y, z;
    for (int i = 0; i < steps; i++)
    {
        x = pow(t, 3) * temp[0][0] + pow(t, 2) * temp[1][0] + t * temp[2][0] + temp[3][0];
        y = pow(t, 3) * temp[0][1] + pow(t, 2) * temp[1][1] + t * temp[2][1] + temp[3][1];
        z = pow(t, 3) * temp[0][2] + pow(t, 2) * temp[1][2] + t * temp[2][2] + temp[3][2];
        putpixel(x, y, 2);
        t = t + step_size;
        cout << x << " " << y << endl;
    }
}

int main()
{
    init_basis();

    matrix geomtery;
    cout << "Enter geometry vector" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> geomtery[i][j];
    }

    hermite(200, geomtery);
    getch();
    return 0;
}

/*
60 140 0
300 260 0
50 250 0
220 30 0
*/