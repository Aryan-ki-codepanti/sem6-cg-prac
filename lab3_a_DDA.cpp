#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

void DDA(float start_x, float start_y, float end_x, float end_y)
{

    // handle vertical case
    if (end_x == start_x)
    {
        for (float i = start_y; i <= end_y; i++)
            putpixel(start_x, i, GREEN);
        return;
    }

    // ensuring going left to right handle
    if (start_x > end_x)
    {
        swap(start_x, end_x);
        swap(start_y, end_y);
    }

    float slope = (end_y - start_y) / (end_x - start_x);

    // slope negative case
    // if (slope < 0)
    // {
    //     swap(start_x, end_x);
    //     swap(start_y, end_y);
    // }

    float x = start_x, y = start_y;

    while ((x <= end_x) && (y <= end_y))
    {

        putpixel(round(x), round(y), YELLOW);

        cout << x << " , " << y << endl;

        if (slope <= 1)
        {
            x += 1;
            y = y + slope;
        }
        else
        {
            y += 1;
            x = x + (1 / slope);
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    // +ve slope case
    // DDA(20, 10, 60, 100);
    // DDA(60, 100, 20, 10);

    // horizontal case
    // DDA(20, 10, 60, 10);
    // DDA(60, 10, 20, 10);

    // vertical case
    // DDA(20, 10, 20, 100);

    // -ve slope case
    DDA(0, 100, 100, 0);

    getch();
    closegraph();
    return 0;
}