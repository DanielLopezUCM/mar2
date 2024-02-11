// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

// Definicion recursiva
/*
    resolver(i, j)
        Donde i son las monedas restantes para comprobar para obtener j de potencia
        Donde j es la potencia que se quiere alcanzar
        0 <= i <= n Siendo n el numero de bombillas
        0 <= j <= intensidadMax

    Tambien necesitamos de un vector que nos indique la potencia y el coste de cada bombilla que lo llamaremos bombillas

    Casos recursivos (i > 0 && j > 0)
        resolver(i, j) = min(resolver(n, j - bombillas[i].potencia) + bombillas[i].coste, resolver(i-1, j))  Si bombillas[i].potencia <= j
        resolver(i, j) = resolver(i - 1, j)                                                                  Si bombillas[i].potencia > j

    Casos base
        resolver(i, 0) = 0
        resolver(0, j) = INF
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;
#define INF INT_MAX

using Bombilla = pair<int, int>;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Bombilla resolver(vector<Bombilla> const &bombillas, int intensidadMax, int intensidadMin)
{
    Bombilla sol = {INF, INF};
    vector<int> dp(intensidadMax + 1, INF);
    dp[0] = 0;

    for (int i = 0; i <= intensidadMax; i++)
    {
        if (dp[i] != INF)
        {

            if (i >= intensidadMin && sol.first > dp[i])
                sol = {dp[i], i};
            for (Bombilla bombilla : bombillas)
            {
                if (i + bombilla.first <= intensidadMax)
                {
                    dp[i + bombilla.first] = min(dp[i + bombilla.first], dp[i] + bombilla.second);
                }
            }
        }
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int nBombillas, intensidadMax, intensidadMin;
    // leer los datos de la entrada
    cin >> nBombillas >> intensidadMax >> intensidadMin;

    if (!std::cin) // fin de la entrada
        return false;

    vector<Bombilla> bombillas(nBombillas);
    for (int i = 0; i < nBombillas; i++)
    {
        cin >> bombillas[i].first;
    }
    for (int i = 0; i < nBombillas; i++)
    {
        cin >> bombillas[i].second;
    }

    Bombilla sol = resolver(bombillas, intensidadMax, intensidadMin);

    // escribir sol
    if (sol.first == INF)
    {
        cout << "IMPOSIBLE\n";
    }
    else
    {
        cout << sol.first << ' ' << sol.second << '\n';
    }

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
