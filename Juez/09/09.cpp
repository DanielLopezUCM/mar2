// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
corte(i, j):

    corte(i, i) = 0;
    corte(i, i+1) = 0;
    corte(i, i+2) = 2 * (cortes[i+2] - corte[i])
    corte(i, j) = 2 * (cortes[j] - corte[i]) + min(cortes(i, k)+cortes(k,j)) para todo k tal que i < k < j, k es por donde cortar
        si i + 2 < j
*/

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(int L, vector<int> const &cortes, int C)
{
    vector<vector<int>> dp(C + 2, vector<int>(C + 2));
    for (int d = 2; d < C + 2; d++)
    {
        for (int i = 0; i < C + 2 - d; i++)
        {
            int j = i + d;
            for (int k = i + 1; k < j; k++)
            {
                int suma = dp[i][k] + dp[k][j] + 2 * (cortes[j] - cortes[i]);
                if (!dp[i][j] || dp[i][j] > suma)
                {
                    dp[i][j] = suma;
                }
            }
        }
    }

    return dp[0][C + 1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int L, C;
    cin >> L >> C;
    // leer los datos de la entrada

    if (L == 0 && C == 0)
        return false;

    vector<int> cortes(C + 2);
    cortes[0] = 0;
    cortes[C + 1] = L;
    for (int i = 1; i <= C; i++)
    {
        cin >> cortes[i];
    }

    int sol = resolver(L, cortes, C);

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
