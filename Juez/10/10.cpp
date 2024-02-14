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

struct Hora
{
    int hora, minuto;
};

bool operator<(Hora const &a, Hora const &b)
{
    return (a.hora < b.hora || (a.hora == b.hora && a.minuto < b.minuto));
}

bool operator==(Hora const &a, Hora const &b)
{
    return a.hora == b.hora && a.minuto == b.minuto;
}

Hora operator+(Hora const &a, int minutos)
{
    return {a.hora + (a.minuto + minutos) / 60, (a.minuto + minutos) % 60};
}

struct Pelicula
{
    Hora inicio;
    int duracion;
    Hora getFin() const
    {
        return inicio + duracion;
    }
};

istream &operator>>(istream &cin, Pelicula &pelicula)
{
    char aux;
    cin >> pelicula.inicio.hora >> aux >> pelicula.inicio.minuto >> pelicula.duracion;
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
    vector<pair<Hora, int>> dp(n + 1);
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (!(dp[j].first < peliculas[i].inicio))
        {
            j--;
        }
        dp[i + 1] = {peliculas[i].getFin(), dp[j].second + peliculas[i].duracion};
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
