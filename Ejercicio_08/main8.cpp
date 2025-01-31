
/*
Ejercicio 7: heurística mejorada
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
#include <algorithm>
using namespace std;

/*
 * @brief nodo en el árbol de soluciones para el algoritmo Branch and Bound.
 */
struct Nodo{
    int nivel;
    int suma1;
    int suma2;
    int diferencia;
    int estimacion;  // Heurística: diferencia actual + estimación futura

    bool operator<(const Nodo& otro) const{ //sobrecarga para usar Nodo en una cola de prioridad
        return estimacion > otro.estimacion; //menor estimación tiene mayor prioridad
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
 * @brief Calcula una estimación heurística para minimizar la diferencia entre subconjuntos.
 * @param nodo Nodo actual en el árbol de soluciones.
 * @param pesos Vector de pesos originales.
 * @param nivel Nivel actual en el árbol de búsqueda.
 * @return diferencia mínima posible.
 */

int calcular_estimacion(const Nodo& nodo, const vector<int>& pesos, int nivel){
    int suma_restante = 0;
    for (int i = nivel; i < pesos.size(); i++){
        suma_restante += pesos[i];
    }
    return nodo.diferencia + suma_restante;
}

/*
 * @brief Implementa el algoritmo Branch and Bound con heurística mejorada para encontrar la partición mínima.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @param shortcicuits Habilita la optimización de atajos si se encuentra una solución óptima temprana.
 * @param stopearly Finaliza si la diferencia mínima encontrada es menor a un umbral definido.
 * @return diferencia mínima entre las sumas de los dos subconjuntos.
 */

int branch_and_bound_heuristica(const vector<int>& pesos, bool shortcicuits, bool stopearly){
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0, 0}); // Nodo raíz
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
        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2,
                      abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        nodo1.estimacion = calcular_estimacion(nodo1, pesos, actual.nivel + 1);
        pq.push(nodo1);

        //genera nodo incluyendo en el peso actual en el segundo subconjunto
        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel],
                      abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        nodo2.estimacion = calcular_estimacion(nodo2, pesos, actual.nivel + 1);
        pq.push(nodo2);
        if (stopearly && min_dif < 5) return min_dif;
    }
    return min_dif;
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly) {
    return branch_and_bound_heuristica(pesos, shortcicuits, stopearly);
}

/*
 * @brief Función principal que solicita parámetros de entrada, genera los pesos y ejecuta el algoritmo.
 * @return ejecución exitosa.
 */

int main(){
    srand(static_cast<unsigned int>(time(0)));
    int cantidad, min_peso, max_peso;
    cout << "elementos: ";
    cin >> cantidad;
    cout << "peso minimo: ";
    cin >> min_peso;
    cout << "peso maximo: ";
    cin >> max_peso;
    if (max_peso - min_peso + 1 < cantidad){ //valida los pesos
        cout << "el rango no puede generar suficientes valores." << endl;
        return 1;
    }
    vector<int> pesos = pesos_unicos(cantidad, min_peso, max_peso);
    sort(pesos.rbegin(), pesos.rend()); //ordenar pesos en orden decreciente para mayor eficiencia
    cout << "Pesos generados (heuristica mejorada): ";
    for (int peso : pesos){
        cout << peso << " ";
    }
    cout << endl;

    //opciones del algoritmo
    char opcionshortcicuits, opcionstopearly;
    cout << "¿usar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿usar 'stop early'? (s/n): ";
    cin >> opcionstopearly;
    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');
    int min_dif = particion_min(pesos, shortcicuits, stopearly); //particion minima
    cout << "Solucion: " << min_dif << endl; //solución
    return 0;
}
