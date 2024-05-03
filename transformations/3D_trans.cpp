#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Vertex 1:
// Vertex 2:
// Vertex 3:
// Vertex 4:
// Vertex 5:
// Vertex 6:
// Vertex 7:
// Vertex 8:

typedef float matrix[4][4];
typedef float cube[8][4];

inline float radians(float deg)
{
    return deg * (M_PI / 180.0);
}

// c1 = r2
void matrix_mul(matrix A, matrix B, matrix &C)
{
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += (A[i][k] * B[k][j]);
        }
    }
}

void transform_mul(cube A, matrix B, cube &res)
{
    int r1 = 8;
    int n = 4, c2 = 4;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < n; k++)
                res[i][j] += (A[i][k] * B[k][j]);
        }
    }
}

void add_edge(int i, int j, cube o)
{

    line(o[i][0] / o[i][3], o[i][1] / o[i][3], o[j][0] / o[i][3], o[j][1] / o[i][3]);
}

void plot_cube_proj_z(cube o, const char *title = "Cube", int col = 1)
{
    initwindow(600, 600, title);
    setcolor(col);
    add_edge(0, 1, o);
    add_edge(1, 2, o);
    add_edge(2, 3, o);
    add_edge(3, 0, o);

    add_edge(4, 5, o);
    add_edge(5, 6, o);
    add_edge(6, 7, o);
    add_edge(7, 4, o);

    add_edge(0, 4, o);
    add_edge(1, 5, o);
    add_edge(2, 6, o);
    add_edge(3, 7, o);
}

void print_cube(cube o)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << o[i][j] << " ";
        cout << endl;
    }
}

void print_mat(matrix o)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << o[i][j] << " ";
        cout << endl;
    }
}

void transformation1(cube obj)
{
    // translate to centre
    float centre_x = 0, centre_y = 0, centre_z = 0;
    for (int i = 0; i < 8; i++)
    {
        centre_x += obj[i][0];
        centre_y += obj[i][1];
        centre_z += obj[i][2];
    }
    centre_x /= 8.0;
    centre_y /= 8.0;
    centre_z /= 8.0;
    cout << centre_x << endl;
    cout << centre_y << endl;
    cout << centre_z << endl;

    matrix T_trans = {0};
    matrix T_trans_back = {0};
    T_trans[0][0] = 1;
    T_trans[1][1] = 1;
    T_trans[2][2] = 1;
    T_trans[3][3] = 1;

    T_trans[3][0] = -centre_x;
    T_trans[3][1] = -centre_y;
    T_trans[3][2] = -centre_z;

    print_mat(T_trans);

    T_trans_back[0][0] = 1;
    T_trans_back[1][1] = 1;
    T_trans_back[2][2] = 1;
    T_trans_back[3][3] = 1;

    T_trans_back[3][0] = centre_x;
    T_trans_back[3][1] = centre_y;
    T_trans_back[3][2] = centre_z;

    cout << "Translated cube" << endl;
    cube res1 = {0};
    transform_mul(obj, T_trans, res1);
    print_cube(res1);

    // "Rotated about centre (about y)"
    cout << "Rotated about centre (about y)" << endl;
    matrix rotate_y = {0};
    float theta = radians(45);

    rotate_y[0][0] = 1;
    rotate_y[1][1] = 1;
    rotate_y[2][2] = 1;
    rotate_y[3][3] = 1;

    rotate_y[0][0] = cos(theta);
    rotate_y[0][2] = -sin(theta);
    rotate_y[2][0] = sin(theta);
    rotate_y[2][2] = cos(theta);

    matrix concat_T1 = {0};
    matrix concat_T2 = {0};
    matrix concat_T3 = {0};
    cube res2 = {0};
    matrix_mul(T_trans, rotate_y, concat_T1);
    matrix_mul(concat_T1, T_trans_back, concat_T2);

    transform_mul(obj, concat_T2, res2);
    cout << "Rotated about centre (about y)" << endl;
    print_cube(res2);

    // green
    plot_cube_proj_z(res2, "Rotated about centre (about y)", 2);

    // 2nd  rotation in  x
    matrix rotate_x = {0};
    float t2 = radians(30);
    rotate_x[0][0] = 1;
    rotate_x[1][1] = 1;
    rotate_x[2][2] = 1;
    rotate_x[3][3] = 1;

    rotate_x[1][1] = cos(t2);
    rotate_x[1][2] = sin(t2);
    rotate_x[2][1] = -sin(t2);
    rotate_x[2][2] = cos(t2);

    cube res3 = {0};
    matrix_mul(concat_T1, rotate_x, concat_T2);
    matrix_mul(concat_T2, T_trans_back, concat_T3);
    transform_mul(obj, concat_T3, res3);
    cout << "Rotated about centre (about y) and then (about x)" << endl;
    print_cube(res3);
    plot_cube_proj_z(res3, "Rotated about centre (about y) and then (about x)", 3); // CYAN

    // Overall Scaling about centre reducing size by 1/2
    matrix scale_T = {0};
    scale_T[0][0] = 1;
    scale_T[1][1] = 1;
    scale_T[2][2] = 1;

    scale_T[3][3] = 2;

    matrix concat_T4 = {0};
    cube res4 = {0};
    matrix_mul(concat_T2, scale_T, concat_T3);
    matrix_mul(concat_T3, T_trans_back, concat_T4);

    transform_mul(obj, concat_T4, res4);

    cout << "Rotated about centre (about y) and then (about x) and reduced to half size with overall scaling" << endl;
    print_cube(res4);
    plot_cube_proj_z(res4, "Rotated about centre (about y) and then (about x) reduced to half size with overall scaling", 4); // RED

    // 1pt Perspective projection
    // same thing at zc = 300

    matrix persp_T = {0};
    persp_T[0][0] = 1;
    persp_T[1][1] = 1;
    persp_T[2][2] = 1;
    persp_T[3][3] = 1;

    persp_T[2][3] = -1.0 / 1300;

    matrix concat_T5 = {0};
    cube res5 = {0};
    matrix_mul(concat_T4, persp_T, concat_T5);
    transform_mul(obj, concat_T5, res5);

    cout << "same thing with perspective projecn Zc = 1300" << endl;
    print_cube(res5);
    plot_cube_proj_z(res5, "perspective projecn Zc = 1300", 5); // MAGENTA
}

int main()
{
    cube obj = {0};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
            cin >> obj[i][j];
    }
    cout << "Cube" << endl;
    print_cube(obj);

    // blue
    plot_cube_proj_z(obj, "Orthographic z=0", 1);

    // rotate with x ,y then project about centre
    transformation1(obj);

    getch();
    return 0;
}