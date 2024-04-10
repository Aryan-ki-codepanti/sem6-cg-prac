#include <iostream>
#include <vector>
using namespace std;

class line_clip
{

public:
    vector<vector<float>> points;
    vector<string> codes;
    float xmax, xmin, ymax, ymin;
    int n;

    line_clip(int n, float xmax, float xmin, float ymax, float ymin)
    {
        this->xmax = xmax;
        this->xmin = xmin;
        this->ymax = ymax;
        this->ymin = ymin;
        this->n = n;
    }

    void input_coords()
    {
        float a, b;
        cout << "Enter points" << endl;

        for (int i = 0; i < n; i++)
            points.push_back({a, b});
    }

    string compute_code(vector<float> pt)
    {

        string code;
        code += to_string(pt[1] > ymax); // TOP
        code += to_string(pt[1] < ymin); // Bottom
        code += to_string(pt[0] > xmax); // Right
        code += to_string(pt[0] < xmin); // left
        cout << code << endl;
        return code;
    }

    // void line_clip(vector<float> a, vector<float> b)
    // {
    // }
};

int main()
{
    int n;
    // cout << "Enter number of points : ";
    // cin >> n;

    line_clip P = line_clip(n, 2, -3, 6, 1);

    P.compute_code({-4, 2});
    P.compute_code({-1, 7});
    // cout << (char)(-4 > 1) << endl;

    return 0;
}