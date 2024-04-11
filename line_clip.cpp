#include <iostream>
#include <graphics.h>
#include <vector>
using namespace std;

class line_clip
{

public:
    float xmax, xmin, ymax, ymin;

    line_clip(float xmax, float xmin, float ymax, float ymin)
    {
        this->xmax = xmax;
        this->xmin = xmin;
        this->ymax = ymax;
        this->ymin = ymin;
    }

    string compute_code(vector<float> pt)
    {

        string code;
        code += to_string(pt[1] > ymax); // TOP
        code += to_string(pt[1] < ymin); // Bottom
        code += to_string(pt[0] > xmax); // Right
        code += to_string(pt[0] < xmin); // left
        return code;
    }

    vector<vector<float>> clip_line(vector<float> a, vector<float> b)
    {
        string c1 = this->compute_code(a);
        string c2 = this->compute_code(b);

        // C1 or C2 = 0000 (both 0)
        string res_or = compute_or(c1, c2);
        string res_and = compute_and(c1, c2);


        if (res_or == "0000")
            return {a, b};

        // completely outside window and ignore
        if (res_and != "0000")
            return {{-99999}, {-99999}};

        // clipping line
        float slope = (b[1] - a[1]) / (b[0] - a[0]);

        // TBRL check
        // top intersection
        vector<vector<float>> clipped;

        float temp_x, temp_y;

        if (res_or[0] == '1') // intersection on top
        {
            cout << "Top" << endl;
            temp_x = a[0] + (ymax - a[1]) / slope;
            clipped.push_back({temp_x, ymax});
        }
        if (res_or[1] == '1') // intersection on bottom
        {
            cout << "Bottom" << endl;
            temp_x = a[0] + (ymin - a[1]) / slope;
            clipped.push_back({temp_x, ymin});
        }
        if (res_or[2] == '1') // intersection on right
        {
            cout << "Right" << endl;
            temp_y = a[1] + (xmax - a[0]) * slope;
            clipped.push_back({xmax, temp_y});
        }
        if (res_or[3] == '1') // intersection on left
        {
            cout << "Left" << endl;
            temp_y = a[1] + (xmin - a[0]) * slope;
            clipped.push_back({xmin, temp_y});
        }

        return clipped;
    }

    static string compute_and(string c1, string c2)
    {
        string res;
        int a, b;
        for (int i = 0; i < 4; i++)
        {
            a = c1[i] - '0';
            b = c2[i] - '0';
            res += to_string(a & b);
        }
        return res;
    }

    static string compute_or(string c1, string c2)
    {
        string res;
        int a, b;
        for (int i = 0; i < 4; i++)
        {
            a = c1[i] - '0';
            b = c2[i] - '0';
            res += to_string(a | b);
        }
        return res;
    }

    static void print_line(vector<vector<float>> pts)
    {
        cout << pts[0][0] << " , " << pts[0][1] << endl;
        cout << pts[1][0] << " , " << pts[1][1] << endl;
    }
};

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    float x_wmin = 20, x_wmax = 90, y_wmin = 20, y_wmax = 70;

    line_clip P = line_clip(x_wmax, x_wmin, y_wmax, y_wmin);

    vector<float> A = {10, 30};
    vector<float> B = {80, 90};


    vector<float> C = {55, 45};
    vector<float> D = {100, 100};


    setcolor(3);
    line(A[0], A[1], B[0], B[1]);
    // line(C[0], C[1], D[0], D[1]);
    rectangle(x_wmin, y_wmax, x_wmax, y_wmin);

    setcolor(14);
    vector<vector<float>> clipped = P.clip_line(A, B);
    vector<vector<float>> clipped2 = P.clip_line(D,C);

    if (clipped[0].size() == 1)
    {
        cout << "line outside window" << endl;
        return 0;
    }

    line(clipped[0][0], clipped[0][1], clipped[1][0], clipped[1][1]);
    line(clipped2[0][0], clipped2[0][1], clipped2[1][0], clipped2[1][1]);

    line_clip::print_line(clipped2);
    getch();

    return 0;
}