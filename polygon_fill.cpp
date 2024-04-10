#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printV(vector<vector<float>> v)
{
    for (auto &&v1 : v)
    {
        for (auto &&i : v1)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    // cout << endl;
}

bool functor(vector<float> a, vector<float> b)
{
    return (a[0] < b[0]);
}

void find_y_min_max(vector<vector<float>> v, int &ymin, int &ymax)
{
    ymin = v[0][1];
    ymax = v[0][1];
    for (auto &&v1 : v)
    {
        if (v1[1] > ymax)
            ymax = v1[1];
        if (v1[1] < ymin)
            ymin = v1[1];
    }
}

// 0 : match x
// 1 : match y
vector<vector<float>> points_at_coord(vector<vector<float>> points, int coordinte, int type = 0)
{
    vector<vector<float>> result;
    for (auto &&pt : points)
    {
        if (pt[type] == coordinte)
            result.push_back(pt);
    }
    return result;
}

vector<vector<float>> edge_points(vector<vector<float>> points, vector<float> point)
{
    int idx = 0;
    for (auto &&pt : points)
    {
        if ((pt[0] == point[0]) && (pt[1] == point[1]))
            break;
        idx++;
    }
    int n = points.size();
    vector<vector<float>> edge_pts;
    if (idx == 0)
        edge_pts = {points[n - 1], points[1]};
    else if (idx == n - 1)
        edge_pts = {points[0], points[n - 2]};
    else
        edge_pts = {points[idx - 1], points[idx + 1]};

    vector<vector<float>> final_pts;

    if (edge_pts[0][1] > point[1])
        final_pts.push_back(edge_pts[0]);

    if (edge_pts[1][1] > point[1])
        final_pts.push_back(edge_pts[1]);

    return final_pts;
}

vector<float> compute_get_entry(vector<float> pt, vector<float> edge)
{
    float one_over_m = float(edge[0] - pt[0]) / (edge[1] - pt[1]);
    float ymax = (pt[1] > edge[1]) ? pt[1] : edge[1];
    float xmin = (pt[1] > edge[1]) ? edge[0] : pt[0];
    return {ymax, xmin, one_over_m};
}

void build_GET(vector<vector<vector<float>>> &GET, vector<vector<float>> og_points, vector<vector<float>> points, int ymin, int ymax, int offset)
{

    for (int y = ymin; y <= ymax; y++)
    {
        vector<vector<float>> points_at_y = points_at_coord(points, y, 1);

        for (auto &pt : points_at_y)
        {
            vector<vector<float>> edge_list = edge_points(og_points, pt);
            vector<vector<float>> entries;
            for (auto &edge : edge_list)
            {
                vector<float> entry = compute_get_entry(pt, edge);
                entries.push_back(entry);
            }
            cout << "Entries for pt " << pt[0] << "," << pt[1] << endl;
            sort(entries.begin(), entries.end(), functor);
            printV(entries);
        }

        cout << endl;
    }
}

int main()
{
    vector<vector<float>> points;
    vector<vector<float>> og_points;
    int n;
    cout << "Enter number of points ";
    cin >> n;
    float a, b;
    for (int i = 0; i < n; i++)
    {

        cin >> a >> b;
        vector<float> v = {a, b};
        points.push_back(v);
        og_points.push_back(v);
    }

    sort(points.begin(), points.end(), functor);

    int ymin, ymax;
    find_y_min_max(points, ymin, ymax);

    int offset = ymin;
    // yth = y - offset
    vector<vector<vector<float>>> GET(ymax - ymin + 1);

    // vector<vector<float>> res = points_at_coord(points, 1);
    build_GET(GET, og_points, points, ymin, ymax, offset);

    return 0;
}