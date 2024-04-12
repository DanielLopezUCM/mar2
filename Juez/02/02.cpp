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
    int puntos;
    int longitudSol;
    int anterior;
};

// función que resuelve el problema
int resolver(int numDianas, vector<int> const &dianas, int objetivo, vector<int> &secuenciaSol)
{
    int sol = 0;
    vector<vector<Datos>> dinamica(numDianas + 1, vector<Datos>(objetivo + 1));

    for (int i = 0; i < numDianas; i++)
    {
        for (int j = 0; j < objetivo; j++)
        {
            dinamica[i + 1][j + 1] = dinamica[i][j + 1];
            if (j + 1 >= dianas[i])
            {
                if (dinamica[i][j + 1 - dianas[i]].puntos + dianas[i] > dinamica[i + 1][j + 1].puntos || (dinamica[i][j + 1 - dianas[i]].puntos + dianas[i] == dinamica[i + 1][j + 1].puntos && dinamica[i][j + 1 - dianas[i]].longitudSol + 1 < dinamica[i + 1][j + 1].longitudSol))
                {
                    dinamica[i + 1][j + 1].puntos = dinamica[i][j + 1 - dianas[i]].puntos + dianas[i];
                    dinamica[i + 1][j + 1].anterior = i;
                    dinamica[i + 1][j + 1].longitudSol = dinamica[i][j + 1 - dianas[i]].longitudSol + 1;
                }
                if (dinamica[i + 1][j + 1 - dianas[i]].puntos + dianas[i] > dinamica[i + 1][j + 1].puntos || (dinamica[i + 1][j + 1 - dianas[i]].puntos + dianas[i] == dinamica[i + 1][j + 1].puntos && dinamica[i + 1][j + 1 - dianas[i]].longitudSol + 1 < dinamica[i + 1][j + 1].longitudSol))
                {
                    dinamica[i + 1][j + 1].puntos = dinamica[i + 1][j + 1 - dianas[i]].puntos + dianas[i];
                    dinamica[i + 1][j + 1].anterior = i;
                    dinamica[i + 1][j + 1].longitudSol = dinamica[i + 1][j + 1 - dianas[i]].longitudSol + 1;
                }
            }
        }
    }
    if (dinamica[numDianas][objetivo].puntos == objetivo)
    {
        int act = dinamica[numDianas][objetivo].anterior;
        sol = dinamica[numDianas][objetivo].longitudSol;
        for (int i = 0; i < dinamica[numDianas][objetivo].longitudSol; i++)
        {
            secuenciaSol.push_back(dianas[act]);
            act = dinamica[act + 1][objetivo - dianas[act]].anterior;
        }
    }

    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    // leer los datos de la entrada
    int objetivo, numDianas;
    cin >> objetivo >> numDianas;
    if (!std::cin)
        return false;

    vector<int> dianas(numDianas);
    for (int i = 0; i < numDianas; i++)
    {
        cin >> dianas[i];
    }

    vector<int> secuenciaSol;
    int sol = resolver(numDianas, dianas, objetivo, secuenciaSol);

    // escribir sol
    if (sol)
    {
        cout << sol << ":";
        for (int i = 0; i < sol; i++)
        {
            cout << " " << secuenciaSol[i];
        }
        cout << '\n';
    }
    else
    {
        cout << "Imposible\n";
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