#include <iostream>
#include <graphics.h>
#include "q6_cohen_sutherland_old.h"
using namespace std;

float polygon[100][2];
float polygon_edges[200][2];
int p_size;
int e_size;
float xmin, ymin, xmax, ymax;

/*
0 : polygon
1 : edge list
*/
void print_arr(int type)
{
    switch (type)
    {
    case 0:
        for (int i = 0; i < p_size; i++)
            cout << polygon[i][0] << " , " << polygon[i][1] << endl;
        break;

    case 1:
        for (int i = 0; i < e_size; i++)
            cout << polygon_edges[i][0] << " , " << polygon_edges[i][1] << endl;
        break;

    default:
        break;
    }
}

void plot_results()
{
    int res_pol[1000];
    int j = 0;
    for (int i = 0; i < p_size; i++)
    {
        res_pol[j++] = polygon[i][0];
        res_pol[j++] = polygon[i][1];
    }
    res_pol[j++] = res_pol[0];
    res_pol[j++] = res_pol[1];

    // orignal
    setcolor(14);
    for (int i = 0; i < j; i++)
    {
        cout << res_pol[i] << " ";
    }
    cout << endl;

    drawpoly((j / 2), res_pol);

    // clipped
    setcolor(3);
    for (int i = 0; i < e_size; i = i + 2)
    {
        line(polygon_edges[i][0], polygon_edges[i][1], polygon_edges[i + 1][0], polygon_edges[i + 1][1]);
    }
}

// clip against rectangular window
void poly_clip()
{
    // preparing edges
    e_size = p_size * 2;
    int j = 0;

    for (int i = 0; i < p_size; i++)
    {
        polygon_edges[j][0] = polygon[i][0];
        polygon_edges[j++][1] = polygon[i][1];

        polygon_edges[j][0] = polygon[((i + 1) % p_size)][0];
        polygon_edges[j++][1] = polygon[((i + 1) % p_size)][1];
    }

    cout << "Edges before" << endl;
    print_arr(1);

    for (int i = 0; i < e_size; i = i + 2)
    {
        clip_line(xmin, ymin, xmax, ymax, &(polygon_edges[i][0]), &(polygon_edges[i][1]), &(polygon_edges[i + 1][0]), &(polygon_edges[i + 1][1]));
    }

    cout << endl
         << "Edges After" << endl;
    print_arr(1);

    plot_results();
}

void draw_rec()
{
    line(xmin, ymin, xmin, ymax);
    line(xmin, ymax, xmax, ymax);
    line(xmax, ymax, xmax, ymin);
    line(xmax, ymin, xmin, ymin);
}

int main()
{

    cout << "Enter window coordinates xmin,ymin and xmax,ymax" << endl;
    cin >> xmin >> ymin >> xmax >> ymax;

    cout << "Enter polygon size : " << endl;
    cin >> p_size;
    cout << "Enter coordinates" << endl;
    for (int i = 0; i < p_size; i++)
        cin >> polygon[i][0] >> polygon[i][1];

    int gd = DETECT, gm;
    // initgraph(&gd, &gm, (char *)"");
    initwindow(700, 1000);
    draw_rec();
    poly_clip();

    getch();

    return 0;
}