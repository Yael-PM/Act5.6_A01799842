
/*
Ejercicio 5: Particiones con Branch and Bound
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
 *   - José Eduardo Rosas Ponciano - A017
 * Fecha de creación: 27/01/25
 */

#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <queue>
using namespace std;

//nodo en el árbol de soluciones
struct Nodo{
    int nivel;
    int suma1;
    int suma2;
    int diferencia;
    bool operator<(const Nodo& otro) const{ //sobrecarga para usar Nodo en una cola de prioridad
        return diferencia > otro.diferencia; //menor diferencia tiene mayor prioridad
    }
};

/*
 * @brief Genera una lista de pesos aleatorios únicos dentro de un rango dado.
 * @param cantidad Número de pesos a generar.
 * @param min_peso Valor mínimo del peso.
 * @param max_peso Valor máximo del peso.
 * @return vector de pesos únicos.
 */
vector<int> pesos_unicos(int cantidad, int min_peso, int max_peso){
    set<int> unicos_pesos;
    while (unicos_pesos.size() < cantidad){
        int peso = rand() % (max_peso - min_peso + 1) + min_peso;
        unicos_pesos.insert(peso);
    }
    return vector<int>(unicos_pesos.begin(), unicos_pesos.end());
}

/*
 * @brief Implementa búsqueda exhaustiva recursiva para particionar un conjunto de pesos.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @param indice Índice actual en la recursión.
 * @param suma1 Suma actual del primer subconjunto.
 * @param suma2 Suma actual del segundo subconjunto.
 * @param min_dif Referencia a la diferencia mínima encontrada.
 */

void particiones(const vector<int>& pesos, int indice, int suma1, int suma2, int& min_dif, bool shortcicuits, bool stopearly){
    if (indice == pesos.size()) {
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif) {
            min_dif = diferencia;
            if (shortcicuits && min_dif == 0) return;
        }
        return;
    }
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif, shortcicuits, stopearly); //peso actual en el primer subconjunto

    // Si stop early está habilitado y ya encontramos una solución suficientemente buena
    if (stopearly && min_dif < 5) return; // Ejemplo: detener si diferencia < 5

    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif, shortcicuits, stopearly); //peso actual en el segundo subconjunto
}

/*
 * @brief Implementación iterativa de Branch and Bound usando una cola de prioridad.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @param shortcicuits Activar parada anticipada si se encuentra una solución perfecta.
 * @param stopearly Detener la búsqueda si se encuentra una diferencia menor a un umbral (ej. 5).
 * @return diferencia mínima entre las sumas de los subconjuntos.
 */

int branch_and_bound_iterativo(const vector<int>& pesos, bool shortcicuits, bool stopearly){
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0});
    int min_dif = INT_MAX;
    while (!pq.empty()){
        Nodo actual = pq.top();
        pq.pop();
        if (actual.nivel == pesos.size()){
            if (actual.diferencia < min_dif){
                min_dif = actual.diferencia;
                if (shortcicuits && min_dif == 0) return min_dif;
            }
            continue;
        }

        //genera nodo incluyendo en el peso actual en el primer subconjunto
        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2, abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        pq.push(nodo1);

        //genera nodo incluyendo en el peso actual en el segundo subconjunto
        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel], abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        pq.push(nodo2);
        if (stopearly && min_dif < 5) return min_dif;
    }
    return min_dif;
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly, bool iterativo){
    if (iterativo){
        return branch_and_bound_iterativo(pesos, shortcicuits, stopearly);
    } else{
        int min_dif = INT_MAX;
        particiones(pesos, 0, 0, 0, min_dif, shortcicuits, stopearly);
        return min_dif;
    }
}

int main(){
    srand(static_cast<unsigned int>(time(0)));
    int cantidad, min_peso, max_peso;
    cout << "elementos: ";
    cin >> cantidad;
    cout << "peso minimo: ";
    cin >> min_peso;
    cout << "peso maximo: ";
    cin >> max_peso;

    // Valida los pesos únicos
    if (max_peso - min_peso + 1 < cantidad){
        cout << "el rango no puede generar suficientes valores." << endl;
        return 1;
    }

    //genera lista de pesos únicos
    vector<int> pesos = pesos_unicos(cantidad, min_peso, max_peso);

    //mostrar los pesos generados
    cout << "Pesos generados: ";
    for (int peso : pesos){
        cout << peso << " ";
    }
    cout << endl;

    //opciones del algoritmo
    char opcionshortcicuits, opcionstopearly, opcioniterativo;
    cout << "¿usar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿usar 'stop early'? (s/n): ";
    cin >> opcionstopearly;
    cout << "¿usar el algoritmo iterativo? (s/n): ";
    cin >> opcioniterativo;
    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');
    bool iterativo = (opcioniterativo == 's' || opcioniterativo == 'S');
    int min_dif = particion_min(pesos, shortcicuits, stopearly, iterativo); //calcular la partición mínima
    cout << "solucion: " << min_dif << endl; //solucion
    return 0;
}
