
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
pair<int, int> resolver(vector<vector<int>> const &tablero, int dim)
{
    vector<pair<int, int>> a(dim), b(dim), *first = &a, *second = &b, *aux;

    for (int i = 0; i < dim; i++)
    {
        (*first)[i] = {tablero[dim - 1][i], i + 1};
    }

    for (int i = dim - 2; i >= 0; i--)
    {
        for (int j = 0; j < dim; j++)
        {
            (*second)[j].first = 0;
            if (j > 0 && tablero[i][j] + (*first)[j - 1].first > (*second)[j].first)
            {
                (*second)[j] = (*first)[j - 1];
                (*second)[j].first += tablero[i][j];
            }
            if (tablero[i][j] + (*first)[j].first > (*second)[j].first)
            {
                (*second)[j] = (*first)[j];
                (*second)[j].first += tablero[i][j];
            }
            if (j + 1 < dim && tablero[i][j] + (*first)[j + 1].first > (*second)[j].first)
            {
                (*second)[j] = (*first)[j + 1];
                (*second)[j].first += tablero[i][j];
            }
        }
        aux = first;
        first = second;
        second = aux;
    }
    pair<int, int> best = (*first)[0];
    for (int i = 1; i < dim; i++)
    {
        if ((*first)[i].first > best.first)
            best = (*first)[i];
    }
    return best;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    // leer los datos de la entrada
    int dim;
    cin >> dim;
    if (!std::cin) // fin de la entrada
        return false;

    vector<vector<int>> tablero(dim, vector<int>(dim));

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            cin >> tablero[i][j];
        }
    }

    pair<int, int> sol = resolver(tablero, dim);

    // escribir sol

    cout << sol.first << ' ' << sol.second << '\n';
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
