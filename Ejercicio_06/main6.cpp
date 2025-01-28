
/*
Ejercicio 6: Particiones con Branch and Bound mejorada del ejercico 5
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
 * Fecha de creación: 27/01/25
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <fstream>
using namespace std;

// Estructura para representar un nodo en el árbol de soluciones
struct Nodo {
    int nivel;
    int suma1;
    int suma2;
    int diferencia;
    bool operator<(const Nodo& otro) const {
        return diferencia > otro.diferencia;
    }
};

// Variables globales para contar nodos visitados
int nodos_exhaustivo = 0;
int nodos_branch_bound = 0;

// Implementación recursiva de búsqueda exhaustiva
void particiones(const vector<int>& pesos, int indice, int suma1, int suma2, int& min_dif) {
    nodos_exhaustivo++;
    if (indice == pesos.size()) {
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif) {
            min_dif = diferencia;
        }
        return;
    }
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif);
    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif);
}

// Implementación iterativa de Branch and Bound
int branch_and_bound_iterativo(const vector<int>& pesos) {
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0});
    int min_dif = INT_MAX;

    while (!pq.empty()) {
        Nodo actual = pq.top();
        pq.pop();
        nodos_branch_bound++;

        if (actual.nivel == pesos.size()) {
            if (actual.diferencia < min_dif) {
                min_dif = actual.diferencia;
            }
            continue;
        }

        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2, abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        pq.push(nodo1);

        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel], abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        pq.push(nodo2);
    }

    return min_dif;
}

// Función principal para experimentar con particiones
void realizar_experimentos() {
    ofstream archivo("resultados.csv");
    archivo << "Tamaño,Nodos_Exhaustivo,Nodos_BranchBound\n";

    for (int n = 1; n <= 25; ++n) {
        vector<int> pesos(n);
        for (int i = 0; i < n; ++i) {
            pesos[i] = i + 1;
        }

        // Reseteo de contadores
        nodos_exhaustivo = 0;
        nodos_branch_bound = 0;

        // Ejecutar métodos
        int min_dif_exh = INT_MAX;
        particiones(pesos, 0, 0, 0, min_dif_exh);
        branch_and_bound_iterativo(pesos);

        // Escribir resultados en el archivo
        archivo << n << "," << nodos_exhaustivo << "," << nodos_branch_bound << "\n";
        cout << "n = " << n
             << ", Exhaustivo nodos = " << nodos_exhaustivo
             << ", Branch & Bound nodos = " << nodos_branch_bound << endl;
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados.csv'" << endl;
}

int main() {
    realizar_experimentos();
    return 0;
}
