// Nombre del alumno
// Daniel Lopez
// Usuario del Juez MAR146

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Datos
{
    int longitud;
    long long int maneras;
    int numCordeles;
    int precio;
};

// función que resuelve el problema
Datos resolver(int numCordeles, vector<int> const &longitudes, vector<int> const &precios, int longitudObjetivo)
{
    vector<vector<Datos>> dinamica(numCordeles + 1, vector<Datos>(longitudObjetivo + 1, {0, 1, 0, 0}));

    for (int i = 0; i < numCordeles; i++)
    {
        for (int j = 0; j < longitudObjetivo; j++)
        {
            if (longitudes[i] > j + 1)
            {
                dinamica[i + 1][j + 1] = dinamica[i][j + 1];
            }
            else
            {
                int ant = dinamica[i][j + 1].longitud;
                int posible = dinamica[i][j + 1 - longitudes[i]].longitud + longitudes[i];
                if (ant > posible)
                {
                    dinamica[i + 1][j + 1] = dinamica[i][j + 1];
                }
                else if (ant < posible)
                {
                    dinamica[i + 1][j + 1] = dinamica[i][j + 1 - longitudes[i]];
                    dinamica[i + 1][j + 1].longitud = posible;
                    dinamica[i + 1][j + 1].numCordeles++;
                    dinamica[i + 1][j + 1].precio += precios[i];
                }
                else
                {
                    dinamica[i + 1][j + 1].longitud = posible;
                    dinamica[i + 1][j + 1].maneras = dinamica[i][j + 1].maneras + dinamica[i][j + 1 - longitudes[i]].maneras;
                    dinamica[i + 1][j + 1].numCordeles = min(dinamica[i][j + 1].numCordeles, dinamica[i][j + 1 - longitudes[i]].numCordeles + 1);
                    dinamica[i + 1][j + 1].precio = min(dinamica[i][j + 1].precio, dinamica[i][j + 1 - longitudes[i]].precio + precios[i]);
                }
            }
        }
    }

    return dinamica[numCordeles][longitudObjetivo];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    // leer los datos de la entrada
    int numCordeles, longitudObjetivo;
    cin >> numCordeles >> longitudObjetivo;
    if (!std::cin)
        return false;

    vector<int> longitudes(numCordeles), costes(numCordeles);

    for (int i = 0; i < numCordeles; i++)
    {
        cin >> longitudes[i] >> costes[i];
    }

    // escribir sol
    Datos sol = resolver(numCordeles, longitudes, costes, longitudObjetivo);

    if (sol.longitud == longitudObjetivo)
    {
        cout << "SI " << sol.maneras << ' ' << sol.numCordeles << ' ' << sol.precio << '\n';
    }
    else
    {
        cout << "NO\n";
    }

    return true;
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
    std::ofstream out("out.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
#endif

    return 0;
}

// Metodo para el matematico (contador de maneras distintas)
// int maneras(int numCordeles, vector<int> const&){}