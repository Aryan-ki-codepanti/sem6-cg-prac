#include <iostream>
#include <graphics.h>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

matrix rotation_mat(float degrees)
{
    float theta = radians(degrees);
    matrix rotate({{cos(theta), sin(theta), 0},
                   {-1 * sin(theta), cos(theta), 0},
                   {0, 0, 1}});
    return rotate;
}

matrix scale_mat(float x_scale = 1, float y_scale = 1)
{
    return matrix({
        {x_scale, 0, 0},
        {0, y_scale, 0},
        {0, 0, 1},
    });
}

matrix translate_mat(float x_trans = 0, float y_trans = 0)
{
    return matrix({
        {1, 0, 0},
        {0, 1, 0},
        {x_trans, y_trans, 1},
    });
}

void draw_result(matrix m, char *title, int col)
{

    initwindow(750, 750, title);
    setcolor(col);
    int nxt, n = m.size();
    for (int i = 0; i < n; i++)
    {
        nxt = (i + 1) % n;
        line(m[i][0] / m[i][2], m[i][1] / m[i][2], m[nxt][0] / m[nxt][2], m[nxt][1] / m[nxt][2]);
    }
}

int main()
{
    // Orignal Object
    matrix original_obj({{400, 400, 1}, {400, 300, 1}, {300, 300, 1}});

    draw_result(original_obj, (char *)("Orignal Object"), 5);
    cout << "Orignal Object" << endl;
    print_vec(original_obj);

    // Scaling 1.5 times X and Y
    matrix scale_T = scale_mat(1.5, 1.5);
    matrix scale_res = vec_mul(original_obj, scale_T);
    draw_result(scale_res, (char *)"X and Y scaled to 1.5 times", 6);
    cout << "Scaled Object" << endl;
    print_vec(scale_res);

    // Rotation
    matrix rota_res = vec_mul(original_obj, rotation_mat(45));
    draw_result(rota_res, (char *)("Rotated 45"), 7);
    cout << "Rotated 45 deg" << endl;
    print_vec(rota_res);

    // Translation x by 100 , y by -100
    matrix trans_T = translate_mat(100, -100);
    matrix trans_res = vec_mul(original_obj, trans_T);
    draw_result(trans_res, (char *)("Translated x by 100 , y by -100"), 7);
    cout << "Translated x by 100 , y by -100" << endl;
    print_vec(trans_res);

    getch();
    return 0;
}