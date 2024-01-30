#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

void bresenham(float start_x, float start_y, float end_x, float end_y)
{

    float del_x = end_x - start_x;
    float del_y = end_y - start_y;

    float D = 2 * del_y - del_x;
    float DNE = 2 * (del_y - del_x);
    float DE = 2 * del_y;

    float x = start_x, y = start_y;

    while ((x < end_x) && (y < end_y))
    {
        cout << x << " , " << y << endl;
        putpixel(x, y, RED);
        if (D <= 0)
            D += DE;
        else
        {
            D += DNE;
            y += 1;
        }
        x += 1;
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    bresenham(20, 10, 60, 100);
    getch();
    closegraph();
    return 0;
}