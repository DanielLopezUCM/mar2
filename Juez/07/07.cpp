
// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
string resolver(string const &primera, string const &segunda)
{
    int n = primera.size(), m = segunda.size();
    vector<vector<pair<int, pair<int, int>>>> dp(n + 1, vector<pair<int, pair<int, int>>>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int act = dp[i - 1][j - 1].first + (primera[i - 1] == segunda[j - 1]);
            int arriba = dp[i - 1][j].first;
            int iz = dp[i][j - 1].first;
            if (act > arriba && act > iz)
            {
                dp[i][j] = {act, {i, j}};
            }
            else if (arriba > iz || (arriba == iz && dp[i][j - 1].second.first + dp[i][j - 1].second.second > dp[i - 1][j].second.first + dp[i - 1][j].second.second))
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    stack<char> solStack;
    string sol;
    int antI = dp[n][m].second.first, antJ = dp[n][m].second.second;
    int aux;

    while (antI > 0 && antJ > 0)
    {
        solStack.push(primera[antI - 1]);
        aux = dp[antI - 1][antJ - 1].second.first;
        antJ = dp[antI - 1][antJ - 1].second.second;
        antI = aux;
    }

    while (!solStack.empty())
    {
        sol.push_back(solStack.top());
        solStack.pop();
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    string primera, segunda;
    // leer los datos de la entrada

    cin >> primera >> segunda;

    if (!std::cin) // fin de la entrada
        return false;

    string sol = resolver(primera, segunda);

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
