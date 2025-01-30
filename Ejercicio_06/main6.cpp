
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

/*
 * @brief nodo en el árbol de soluciones.
 */

struct Nodo{
    int nivel;
    int suma1;
    int suma2;
    int diferencia;
    bool operator<(const Nodo& otro) const{
        return diferencia > otro.diferencia;
    }
};

//contar nodos visitados
int nodos_exhaustivo = 0;
int nodos_branch_bound = 0;

/*
 * @brief Implementa búsqueda exhaustiva recursiva para particionar un conjunto de pesos.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @param indice Índice actual en la recursión.
 * @param suma1 Suma actual del primer subconjunto.
 * @param suma2 Suma actual del segundo subconjunto.
 * @param min_dif Referencia a la diferencia mínima encontrada.
 */

void particiones(const vector<int>& pesos, int indice, int suma1, int suma2, int& min_dif){
    nodos_exhaustivo++;
    if (indice == pesos.size()){
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif){
            min_dif = diferencia;
        }
        return;
    }
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif); //peso actual en el primer subconjunto
    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif); //peso actual en el segundo subconjunto
}

/*
 * @brief Implementa el algoritmo Branch and Bound de manera iterativa con una cola de prioridad.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @return diferencia mínima entre las sumas de los dos subconjuntos.
 */

int branch_and_bound_iterativo(const vector<int>& pesos){
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0});
    int min_dif = INT_MAX;
    while (!pq.empty()){
        Nodo actual = pq.top();
        pq.pop();
        nodos_branch_bound++; //incrementa el contador de nodos visitados
        if (actual.nivel == pesos.size()){
            if (actual.diferencia < min_dif){
                min_dif = actual.diferencia;
            }
            continue;
        }

        //genera nodo incluyendo en el peso actual en el primer subconjunto
        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2, abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        pq.push(nodo1);

        //genera nodo incluyendo en el peso actual en el segundo subconjunto
        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel], abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        pq.push(nodo2);
    }

    return min_dif;
}

/*
 * @brief Ejecuta experimentos con particiones utilizando ambos métodos y guarda los resultados en un archivo CSV.
 * Se generan conjuntos de pesos de tamaño creciente (1 a 25) y se comparan los nodos visitados en la búsqueda exhaustiva y en el algoritmo Branch and Bound iterativo.
 */

void realizar_experimentos(){
    ofstream archivo("resultados.csv");
    archivo << "Tamaño,Nodos_Exhaustivo,Nodos_BranchBound\n";
    for (int n = 1; n <= 25; ++n){
        vector<int> pesos(n);
        for (int i = 0; i < n; ++i){
            pesos[i] = i + 1;
        }
        nodos_exhaustivo = 0;
        nodos_branch_bound = 0;

        //ejecuta métodos
        int min_dif_exh = INT_MAX;
        particiones(pesos, 0, 0, 0, min_dif_exh);
        branch_and_bound_iterativo(pesos);

        //escribe los resultados en el archivo
        archivo << n << "," << nodos_exhaustivo << "," << nodos_branch_bound << "\n";
        cout << "n = " << n
             << ", Exhaustivo nodos = " << nodos_exhaustivo
             << ", Branch & Bound nodos = " << nodos_branch_bound << endl;
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados.csv'" << endl;
}

/*
 * @brief Función principal que ejecuta los experimentos de partición.
 */

int main(){
    realizar_experimentos();
    return 0;
}
