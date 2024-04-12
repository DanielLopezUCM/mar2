// Nombre y Apellidos
// Daniel Lopez

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
    Vamos a resolver este problema con ramificación y poda.
    Nuestro arbol de exploración será para cada persona le asignamos una playa a la que irá a limpiar.
    De esta forma el tamaño del arbol de exploración es m^n, siendo n el numero de personas y m el numero de playas. (tenemos n etapas y para cada etapa m opciones)

    En este caso no vamos a poder hacer uso del esquema optimista-pesimista debido a que con la restricción de que al menos l playas tienen que quedar completamente limpias,
    no podemos asegurar que dada una solucion parcial que podamos llegar a una solución válida.

    La función optimista nos devolverá lo máximo que pueden limpiar las personas restantes.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

vector<int> mejoresLimpiezas;

struct Nodo
{
    int etapa;
    vector<int> basuraPendiente;
    int completamenteLimpias;
    int limpieza;
};

int optimista(Nodo const &a)
{
    return mejoresLimpiezas[a.etapa] + a.limpieza;
}

struct Orden
{
    bool operator()(Nodo const &a, Nodo const &b)
    {
        return optimista(a) < optimista(b);
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
pair<int, int> resolver(int n, int m, int l, vector<int> const &basuras, vector<vector<int>> const &limpiezas, int playasYaLimpias)
{
    pair<int, int> sol;

    priority_queue<Nodo, vector<Nodo>, Orden> pending;
    pending.push({0, basuras, playasYaLimpias, 0});

    while (!pending.empty() && optimista(pending.top()) > sol.first)
    {
        Nodo act = pending.top();
        pending.pop();
        act.etapa++;
        int limpieza;
        for (int i = 0; i < m; i++)
        {
            limpieza = min(act.basuraPendiente[i], limpiezas[act.etapa - 1][i]);

            act.basuraPendiente[i] -= limpieza;
            act.limpieza += limpieza;

            if (act.basuraPendiente[i] == 0 && limpieza > 0)
                act.completamenteLimpias++;

            if (n - act.etapa + act.completamenteLimpias >= l) // Podemos llegar a una solucion, ya que si nos quedan por limpiar por lo menos h playas no quedan sufientes personas para limpiarlas no seremos capaces de limpiarlas
            {
                if (act.etapa == n)
                {
                    if (sol.first < act.limpieza)
                        sol = {act.limpieza, act.completamenteLimpias};
                }
                else
                {
                    pending.push(act);
                }
            }

            if (act.basuraPendiente[i] == 0 && limpieza > 0)
                act.completamenteLimpias--;
            act.limpieza -= limpieza;
            act.basuraPendiente[i] += limpieza;
        }
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
    int n, m, l;
    // leer los datos de la entrada
    cin >> n >> m >> l;
    vector<int> basuras(m);
    vector<vector<int>> limpiezas(n, vector<int>(m));

    int playasYaLimpias = 0;

    for (int i = 0; i < m; i++)
    {
        cin >> basuras[i];
        if (!basuras[i])
            playasYaLimpias++;
    }

    mejoresLimpiezas = vector<int>(n);

    int mejorLimpieza;
    for (int i = 0; i < n; i++)
    {
        mejorLimpieza = 0;
        for (int j = 0; j < m; j++)
        {
            cin >> limpiezas[i][j];
            mejorLimpieza = max(mejorLimpieza, limpiezas[i][j]);
        }
        mejoresLimpiezas[i] = mejorLimpieza;
    }

    for (int i = n - 1; i > 0; i--)
    {
        mejoresLimpiezas[i - 1] += mejoresLimpiezas[i];
    }

    pair<int, int> sol = resolver(n, m, l, basuras, limpiezas, playasYaLimpias);

    // escribir solución
    if (sol.second < l)
    {
        cout << "IMPOSIBLE\n";
    }
    else
    {
        cout << sol.first << ' ' << sol.second << '\n';
    }
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

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

        // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
#endif
    return 0;
}
