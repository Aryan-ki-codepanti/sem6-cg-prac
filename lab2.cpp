#include <iostream>
#include <graphics.h>
using namespace std;

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    int vertices[] = {
        100, 100,
        200, 400,
        410, 300,
        100, 100};
    drawpoly(4, vertices);

    circle(100, 100, 40);
    line(1, 1, getmaxx(), getmaxy());
    cout << "A";
    getch();
    return 0;
}