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

    void clip_line(vector<float> a, vector<float> b)
    {
        string c1 = this->compute_code(a);
        string c2 = this->compute_code(b);

        bool done = false, accept = false;

        do
        {
            // completely inside window so accept
            if (compute_or(c1, c2) == "0000")
            {
                accept = true;
                done = true;
            }

            // completely outside window and ignore
            else if (compute_and(c1, c2) != "0000")
                done = true;

            else
            {

                // clipping from the point which is outside
                float slope = (b[1] - a[1]) / (b[0] - a[0]);

                string code_out = (c1 != "0000") ? c1 : c2;

                // TBRL check
                // top intersection

                float temp_x, temp_y;

                if (code_out[0] == '1') // intersection on top
                {
                    temp_x = a[0] + (ymax - a[1]) / slope;
                    temp_y = ymax;
                }
                else if (code_out[1] == '1') // intersection on bottom
                {
                    temp_x = a[0] + (ymin - a[1]) / slope;
                    temp_y = ymin;
                }
                else if (code_out[2] == '1') // intersection on right
                {
                    temp_y = a[1] + (xmax - a[0]) * slope;
                    temp_x = xmax;
                }
                else //  (code_out[3] == '1') // intersection on left
                {
                    temp_y = a[1] + (xmin - a[0]) * slope;
                    temp_x = xmin;
                }
                // update the outside pt to intersection
                if (code_out == c1)
                {
                    a[0] = temp_x;
                    a[1] = temp_y;
                    c1 = compute_code(a);
                }
                else
                {
                    b[0] = temp_x;
                    b[1] = temp_y;
                    c2 = compute_code(b);
                }
            }

        } while (done == false);

        // line accepted
        if (accept)
        {
            cout << "Line accepted / clipped" << endl;
            setcolor(14);
            line(a[0], a[1], b[0], b[1]);
        }
        else
            cout << "Line Rejected" << endl;
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

    // 2 pt intersection
    vector<float> A = {10, 30};
    vector<float> B = {80, 90};

    // 1 pt intersection
    vector<float> C = {55, 45};
    vector<float> D = {100, 100};

    // Completely outside
    vector<float> E = {20, 200};
    vector<float> F = {100, 100};

    setcolor(3);
    line(A[0], A[1], B[0], B[1]);
    line(C[0], C[1], D[0], D[1]);
    line(E[0], E[1], F[0], F[1]);
    rectangle(x_wmin, y_wmax, x_wmax, y_wmin);

    setcolor(14);
    P.clip_line(A, B);
    P.clip_line(C, D);
    P.clip_line(E, F);

    getch();

    return 0;
}