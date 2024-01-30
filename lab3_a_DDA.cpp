#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

void DDA(float start_x, float start_y, float end_x, float end_y)
{

    float slope = (end_y - start_y) / (end_x - start_x);
    float x = start_x, y = start_y;

    while ((x < end_x) && (y < end_y))
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

    DDA(20, 10, 60, 100);

    getch();
    closegraph();
    return 0;
}