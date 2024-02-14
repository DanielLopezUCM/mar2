// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
// Usamos el algoritmo de floyd ya que se basa en saber la maxima distancia entre dos puntos de un mismo grafo.
// Tambien comprobando si se puede ir de todos los nodos a todos los nodos lo que comprobamos mirando la distancia entre cada par de vertices
// y viendo si esta es INF (ya que distancia infinita significa que pertenecen a componentes conexas distintas)

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <limits.h>

#define INF (1000)

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<vector<int>> &grafo, int V)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                grafo[i][j] = min(grafo[i][j], grafo[i][k] + grafo[k][j]);
            }
        }
    }

    int maxDist = grafo[0][1];
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (grafo[i][j] == INF)
            {
                return -1;
            }
            maxDist = max(maxDist, grafo[i][j]);
        }
    }
    return maxDist;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int V, E;
    cin >> V >> E;

    // leer los datos de la entrada

    if (!std::cin) // fin de la entrada
        return false;

    vector<vector<int>> grafo(V, vector<int>(V, INF));
    unordered_map<string, int> nombres;
    int contNombres = 0;
    string nombre1, nombre2;
    for (int i = 0; i < E; i++)
    {
        cin >> nombre1 >> nombre2;
        if (!nombres.count(nombre1))
        {
            nombres[nombre1] = contNombres++;
        }
        if (!nombres.count(nombre2))
        {
            nombres[nombre2] = contNombres++;
        }
        grafo[nombres[nombre1]][nombres[nombre2]] = 1;
        grafo[nombres[nombre2]][nombres[nombre1]] = 1;
    }

    int sol = -1;
    if (contNombres == V && E + 1 >= V)
    {
        sol = resolver(grafo, V);
    }

    // escribir sol
    if (sol == -1)
    {
        cout << "DESCONECTADA\n";
    }
    else
    {
        cout << sol << '\n';
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
