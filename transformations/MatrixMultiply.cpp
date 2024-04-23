#include <iostream>
#include <vector>
using namespace std;

void print_vec(vector<vector<float>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
}

vector<vector<float>> vec_mul(vector<vector<float>> A, vector<vector<float>> B)
{
    vector<vector<float>> C;
    int m1 = A.size();
    int n1 = A[0].size();
    int m2 = B.size();
    int n2 = B[0].size();

    // Cant multiply matrices
    if (n1 != m2)
        return C;

    for (int i = 0; i < m1; i++)
    {
        vector<float> row;
        for (int j = 0; j < n2; j++)
        {
            float temp = 0;
            for (int k = 0; k < n1; k++)
                temp += (A[i][k] * B[k][j]);
            row.push_back(temp);
        }
        C.push_back(row);
    }
    return C;
}

int main()
{
    vector<vector<float>> A, B, C;
    A = {{1, 1},
         {2, 2}};
    B = {{1, 1},
         {2, 2}};

    C = vec_mul(A, B);
    if (!C.size())
        cout << "Not Ok" << endl;
    else
        print_vec(C);

    return 0;
}