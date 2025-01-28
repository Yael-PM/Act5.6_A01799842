
/*
Ejercicio 7: heurística mejorada
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
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

// Estructura para representar un nodo en el árbol de soluciones
struct Nodo {
    int nivel;       // Nivel del árbol (índice del peso)
    int suma1;       // Suma del primer subconjunto
    int suma2;       // Suma del segundo subconjunto
    int diferencia;  // Diferencia absoluta entre las dos sumas
    int estimacion;  // Heurística: diferencia actual + estimación futura

    // Sobrecarga para usar Nodo en una cola de prioridad
    bool operator<(const Nodo& otro) const {
        return estimacion > otro.estimacion; // Menor estimación tiene mayor prioridad
    }
};

// Generar una lista de pesos aleatorios sin duplicados
vector<int> pesos_unicos(int cantidad, int min_peso, int max_peso) {
    set<int> unicos_pesos;
    while (unicos_pesos.size() < cantidad) {
        int peso = rand() % (max_peso - min_peso + 1) + min_peso;
        unicos_pesos.insert(peso);
    }
    return vector<int>(unicos_pesos.begin(), unicos_pesos.end());
}

// Calcular la estimación heurística para un nodo
int calcular_estimacion(const Nodo& nodo, const vector<int>& pesos, int nivel) {
    int suma_restante = 0;
    for (int i = nivel; i < pesos.size(); i++) {
        suma_restante += pesos[i];
    }
    return nodo.diferencia + suma_restante; // Diferencia actual + suma de pesos restantes
}

// Implementación iterativa de Branch and Bound con heurística mejorada
int branch_and_bound_heuristica(const vector<int>& pesos, bool shortcicuits, bool stopearly) {
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0, 0}); // Nodo raíz
    int min_dif = INT_MAX;

    while (!pq.empty()) {
        Nodo actual = pq.top();
        pq.pop();

        if (actual.nivel == pesos.size()) {
            if (actual.diferencia < min_dif) {
                min_dif = actual.diferencia;
                if (shortcicuits && min_dif == 0) return min_dif;
            }
            continue;
        }

        // Generar nodo incluyendo el peso actual en el primer subconjunto
        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2,
                      abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        nodo1.estimacion = calcular_estimacion(nodo1, pesos, actual.nivel + 1);
        pq.push(nodo1);

        // Generar nodo incluyendo el peso actual en el segundo subconjunto
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

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Solicitar al usuario los parámetros de entrada
    int cantidad, min_peso, max_peso;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> cantidad;
    cout << "Ingrese el peso minimo: ";
    cin >> min_peso;
    cout << "Ingrese el peso maximo: ";
    cin >> max_peso;

    // Validar que se puedan generar suficientes pesos únicos
    if (max_peso - min_peso + 1 < cantidad) {
        cout << "Error: El rango de pesos no permite generar suficientes valores únicos." << endl;
        return 1;
    }

    // Generar lista de pesos únicos
    vector<int> pesos = pesos_unicos(cantidad, min_peso, max_peso);

    // Ordenar pesos de manera descendente para mejorar la eficiencia
    sort(pesos.rbegin(), pesos.rend());

    // Mostrar los pesos generados
    cout << "Pesos generados (ordenados): ";
    for (int peso : pesos) {
        cout << peso << " ";
    }
    cout << endl;

    // Seleccionar opciones del algoritmo
    char opcionshortcicuits, opcionstopearly;
    cout << "¿Desea habilitar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿Desea habilitar 'stop early'? (s/n): ";
    cin >> opcionstopearly;

    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');

    // Calcular la partición mínima
    int min_dif = particion_min(pesos, shortcicuits, stopearly);

    // Mostrar el resultado
    cout << "La diferencia mínima entre las particiones es: " << min_dif << endl;

    return 0;
}
