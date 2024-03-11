#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

void plot_ellipse_points(int x, int y, int center_x, int centre_y, int color)
{
    putpixel(center_x + x, centre_y + y, color);
    putpixel(center_x + x, centre_y - y, color);
    putpixel(center_x - x, centre_y + y, color);
    putpixel(center_x - x, centre_y - y, color);
}

void plot_ellipse(int a, int b, int centre_x, int centre_y, int color)
{
    int x = 0;
    int y = b;

    float d1 = b * b + a * a * (-b + .25);

    // region 1
    while (a * a * (y - .5) >= b * b * (x + 1))
    {
        // choose E
        if (d1 < 0)
            d1 += b * b * (2 * x + 3);
        else // choose SE
        {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }
        x++;
        plot_ellipse_points(x, y, centre_x, centre_y, color);
    }

    // region 2
    float d2 = b * b * pow(x + .5, 2) + a * a * pow(y - 1, 2) - a * a * b * b;
    while (y > 0)
    {
        if (d2 < 0) // choose SE
        {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else // choose E
            d2 += a * a * (-2 * y + 3);
        y--;
        plot_ellipse_points(x, y, centre_x, centre_y, color);
    }

    // region 2
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    // defined center
    int centre_x = getmaxx() / 2;
    int centre_y = getmaxy() / 2;

    plot_ellipse(100, 80, centre_x, centre_y, RED);
    plot_ellipse(80, 150, centre_x, centre_y, GREEN);
    plot_ellipse(150, 150, centre_x, centre_y, WHITE);

    getch();
    return 0;
}