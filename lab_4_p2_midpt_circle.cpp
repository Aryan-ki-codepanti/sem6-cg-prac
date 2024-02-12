#include <iostream>
#include <graphics.h>
using namespace std;

void plot_circle_points(int x, int y, int center_x, int centre_y, int color)
{
    putpixel(center_x + x, centre_y + y, color);
    putpixel(center_x + x, centre_y - y, color);
    putpixel(center_x - x, centre_y + y, color);
    putpixel(center_x - x, centre_y - y, color);
    putpixel(center_x + y, centre_y + x, color);
    putpixel(center_x - y, centre_y + x, color);
    putpixel(center_x + y, centre_y - x, color);
    putpixel(center_x - y, centre_y - x, color);
}

void plot_circle(int radius, int centre_x, int centre_y, int color)
{
    int x = 0;
    int y = radius;

    float d = 1.25 - radius;

    while (y >= x)
    {

        if (d < 0) // select E
            d += 2 * x + 3;

        else // select SE
        {
            d += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
        plot_circle_points(x, y, centre_x, centre_y, color);
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    // defined center
    int centre_x = getmaxx() / 2;
    int centre_y = getmaxy() / 2;

    plot_circle(100, centre_x, centre_y, GREEN);
    plot_circle(150, centre_x, centre_y, RED);
    plot_circle(200, centre_x, centre_y, WHITE);

    getch();
    return 0;
}