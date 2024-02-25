// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<int> const &cubos, int nCubos)
{
    vector<vector<int>> dp(nCubos, vector<int>(nCubos));
    for (int i = 0; i < nCubos; i++)
    {
        dp[i][i] = cubos[i];
    }

    // Diagonal 1
    for (int i = 0; i < nCubos - 1; i++)
    {
        dp[i][i + 1] = max(dp[i][i], dp[i + 1][i + 1]);
        cout << dp[i][i + 1] << ' ';
    }
    cout << '\n';

    for (int d = 2; d < nCubos; d++)
    {
        for (int i = 0; i < nCubos - d; i++)
        {
            int j = i + d;
            int dr = j, iz = i + 1;
            // Primero probamos que se come la i
            if (cubos[dr] > cubos[iz])
            {
                dr--;
            }
            else
            {
                iz++;
            }
            dp[i][j] = dp[iz][dr] + cubos[i];

            dr = j - 1, iz = i;
            // Probamos que se come la j
            if (cubos[dr] > cubos[iz])
            {
                dr--;
            }
            else
            {
                iz++;
            }
            dp[i][j] = max(dp[iz][dr] + cubos[i], dp[i][j]);
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    return dp[0][nCubos - 1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int nCubos;
    // leer los datos de la entrada
    cin >> nCubos;
    if (!nCubos)
        return false;

    vector<int> cubos(nCubos);

    for (int i = 0; i < nCubos; i++)
    {
        cin >> cubos[i];
    }

    int sol = resolver(cubos, nCubos);

    // escribir sol
    cout << sol << '\n';
    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("out.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
#endif
    return 0;
}
