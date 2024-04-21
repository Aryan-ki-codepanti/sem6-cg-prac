using namespace std;

int TOP = 8;
int BOTTOM = 4;
int RIGHT = 2;
int LEFT = 1;

int get_region_code(float x, float y, float xmin, float ymin, float xmax, float ymax)
{
    int code = 0;
    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;
    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;
    return code;
}

void clip_line(float xmin, float ymin, float xmax, float ymax, float *x1, float *y1, float *x2, float *y2)
{

    bool accept = false;
    bool done = false;
    int rcode1 = get_region_code(*x1, *y1, xmin, ymin, xmax, ymax);
    int rcode2 = get_region_code(*x2, *y2, xmin, ymin, xmax, ymax);

    do
    {

        // completely inside window : accept
        if ((rcode1 | rcode2) == 0)
        {
            accept = true;
            done = true;
        }
        // completely outside window : reject
        else if (rcode1 & rcode2)
            done = true;

        // clipping case
        else
        {
            float x, y, slope = (*y2 - *y1) / (*x2 - *x1);
            int rcodeout = rcode1 ? rcode1 : rcode2;

            if (rcodeout & TOP)
            {
                x = *x1 + (1 / slope) * (ymax - *y1);
                y = ymax;
            }
            else if (rcodeout & BOTTOM)
            {
                x = *x1 + (1 / slope) * (ymin - *y1);
                y = ymin;
            }
            else if (rcodeout & RIGHT)
            {
                y = *y1 + slope * (xmax - *x1);
                x = xmax;
            }
            else
            {
                y = *y1 + slope * (xmin - *x1);
                x = xmin;
            }

            // updating the outside point to clipped point
            if (rcodeout == rcode1)
            {
                *x1 = x;
                *y1 = y;
                rcode1 = get_region_code(*x1, *y1, xmin, ymin, xmax, ymax);
            }
            else
            {
                *x2 = x;
                *y2 = y;
                rcode2 = get_region_code(*x2, *y2, xmin, ymin, xmax, ymax);
            }
        }
    } while (!done);

    if (accept)
    {

        cout << "updated Coords" << endl;
        // setcolor(14);
        // line(*x1, *y1, *x2, *y2);
    }

    else
    {
        cout << "rejected Coords" << endl;
        //     setcolor(3);
        //     line(*x1, *y1, *x2, *y2);
    }
}
