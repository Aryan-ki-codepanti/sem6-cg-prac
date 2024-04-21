#include <iostream>

using namespace std;

typedef float vertex[2];
typedef vertex edge[2];
int max = 10000;
typedef vertex vertexArray[10000];

bool Inside(vertex testVertex, edge clipBoundary)
{
    return ((clipBoundary[0][0] <= testVertex[0]) && (testVertex[0] <= clipBoundary[1][0]) && (clipBoundary[0][1] <= testVertex[1]) && (testVertex[1] <= clipBoundary[1][1]));
}

//          1       2           3,4
void Intersect(vertex a, vertex b, edge clipBoundary, vertex &intersect)
{
    float inter_x = ((a[0] * b[1] - a[1] * b[0]) * (clipBoundary[0][0] - clipBoundary[1][0]) - (a[0] - b[0]) * (clipBoundary[0][0] * clipBoundary[1][1] - clipBoundary[0][1] * clipBoundary[1][0])) / ((a[0] - b[0]) * (clipBoundary[0][1] - clipBoundary[1][1]) - (a[1] - b[1]) * (clipBoundary[0][0] - clipBoundary[1][0]));

    float inter_y = (a[0] * b[1] - a[1] * b[0]) * (clipBoundary[0][0] - clipBoundary[1][0]) - (a[0] - b[0]) * (clipBoundary[0][0] * clipBoundary[1][1] - clipBoundary[0][1] * clipBoundary[1][0]);

    intersect[0] = inter_x;
    intersect[1] = inter_y;
}

int main()
{
    vertex a = {2, 5};
    int arr[2] = {1, 2};
    return 0;
}