// Nombre y Apellidos
// Daniel Lopez Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

using Cofre = pair<int, int>;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<Cofre> const &cofres, int capacidad, stack<Cofre> &cofresSolucion)
{
    vector<vector<pair<int, int>>> dp(cofres.size() + 1, vector<pair<int, int>>(capacidad + 1));

    for (int i = 1; i <= cofres.size(); i++)
    {
        for (int j = 1; j <= capacidad; j++)
        {
            int act = 0;
            if (cofres[i - 1].first <= j)
            {
                act = dp[i - 1][j - cofres[i - 1].first].first + cofres[i - 1].second;
            }
            int arriba = dp[i - 1][j].first;
            int iz = dp[i][j - 1].first;
            if (act > arriba && act > iz)
            {
                dp[i][j] = {act, i};
            }
            else if (arriba > iz)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    int ant = dp[cofres.size()][capacidad].second;
    int capAct = capacidad;
    while (ant != 0)
    {
        cofresSolucion.push({cofres[ant - 1].first / 3, cofres[ant - 1].second});
        capAct -= cofres[ant - 1].first;
        ant = dp[ant][capAct].second;
    }

    return dp[cofres.size()][capacidad].first;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int capacidad;
    // leer los datos de la entrada
    cin >> capacidad;
    if (!std::cin) // fin de la entrada
        return false;

    int nCofres;
    cin >> nCofres;

    vector<Cofre> cofres(nCofres);

    for (int i = 0; i < nCofres; i++)
    {
        cin >> cofres[i].first >> cofres[i].second;
        cofres[i].first *= 3;
    }

    stack<Cofre> cofresSolucion;

    int sol = resolver(cofres, capacidad, cofresSolucion);

    // escribir sol

    cout << sol << '\n';

    cout << cofresSolucion.size() << '\n';

    Cofre cofre;
    while (!cofresSolucion.empty())
    {
        cofre = cofresSolucion.top();
        cofresSolucion.pop();
        cout << cofre.first << ' ' << cofre.second << '\n';
    }

    cout << "---\n";

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
