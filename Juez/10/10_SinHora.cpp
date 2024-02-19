// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Pelicula
{
    int inicio;
    int duracion;
    int getFin() const
    {
        return inicio + duracion;
    }
};

istream &operator>>(istream &cin, Pelicula &pelicula)
{
    char aux;
    int auxHoras;
    cin >> auxHoras >> aux >> pelicula.inicio >> pelicula.duracion;
    pelicula.inicio += auxHoras * 60;
    return cin;
}

bool ordenar(Pelicula const &a, Pelicula const &b)
{
    return (a.getFin() < b.getFin() || (a.getFin() == b.getFin() && a.inicio < b.inicio));
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<Pelicula> const &peliculas)
{
    int n = peliculas.size();
    int mejor = 0;
    int mejorParcial;
    pair<int, int> aux;
    vector<pair<int, int>> dp(n + 1);
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (dp[j].first > peliculas[i].inicio)
        {
            j--;
        }

        mejorParcial = dp[j].second + peliculas[i].duracion;
        while (j >= 0)
        {
            if (mejorParcial < dp[j].second + peliculas[i].duracion)
                mejorParcial = dp[j].second + peliculas[i].duracion;
            j--;
        }

        dp[i + 1] = {peliculas[i].getFin() + 10, mejorParcial};
        aux = dp[i + 1];
        if (mejor < dp[i + 1].second)
            mejor = dp[i + 1].second;
    }
    return mejor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    // leer los datos de la entrada
    int nPelis;
    cin >> nPelis;

    if (!nPelis)
        return false;

    vector<Pelicula> peliculas(nPelis);
    for (int i = 0; i < nPelis; i++)
    {
        cin >> peliculas[i];
    }
    sort(peliculas.begin(), peliculas.end(), ordenar);

    int sol = resolver(peliculas);

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
