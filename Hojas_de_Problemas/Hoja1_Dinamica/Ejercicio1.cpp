#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> l = {1, 2, 3};
vector<int> p = {1, 2, 3};

bool apartadoA(vector<int> const &longitudes, vector<int> const &precios, int longitudObjetivo)
{
    vector<vector<int>> dinamica(longitudes.size() + 1, vector<int>(longitudObjetivo + 1));

    for (int i = 0; i < longitudes.size(); i++)
    {
        for (int j = 1; j <= longitudObjetivo; j++)
        {
            if (longitudes[i] > j)
            {
                dinamica[i + 1][j] = dinamica[i][j];
            }
            else
            {
                dinamica[i + 1][j] = max(dinamica[i][j], dinamica[i][j - longitudes[i]] + longitudes[i]);
            }
            cout << dinamica[i + 1][j] << ' ';
        }
        cout << '\n';
    }

    return dinamica[longitudes.size()][longitudObjetivo] == longitudObjetivo;
}

int main()
{
    cout << apartadoA(l, p, 3);
    return 0;
}