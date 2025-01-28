
/*
Ejercicio 5: Particiones con Branch and Bound
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
using namespace std;

// Estructura para representar un nodo en el árbol de soluciones
struct Nodo {
    int nivel;       // Nivel del árbol (índice del peso)
    int suma1;       // Suma del primer subconjunto
    int suma2;       // Suma del segundo subconjunto
    int diferencia;  // Diferencia absoluta entre las dos sumas

    // Sobrecarga para usar Nodo en una cola de prioridad
    bool operator<(const Nodo& otro) const {
        return diferencia > otro.diferencia; // Menor diferencia tiene mayor prioridad
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

// Implementación recursiva de Branch and Bound
void particiones(const vector<int>& pesos, int indice, int suma1, int suma2, int& min_dif, bool shortcicuits, bool stopearly) {
    if (indice == pesos.size()) {
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif) {
            min_dif = diferencia;
            if (shortcicuits && min_dif == 0) return;
        }
        return;
    }

    // Explorar incluir el peso actual en el primer subconjunto
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif, shortcicuits, stopearly);

    // Si stop early está habilitado y ya encontramos una solución suficientemente buena
    if (stopearly && min_dif < 5) return; // Ejemplo: detener si diferencia < 5

    // Explorar incluir el peso actual en el segundo subconjunto
    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif, shortcicuits, stopearly);
}

// Implementación iterativa de Branch and Bound con cola de prioridad
int branch_and_bound_iterativo(const vector<int>& pesos, bool shortcicuits, bool stopearly) {
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0}); // Nodo raíz
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
        Nodo nodo1 = {actual.nivel + 1, actual.suma1 + pesos[actual.nivel], actual.suma2, abs((actual.suma1 + pesos[actual.nivel]) - actual.suma2)};
        pq.push(nodo1);

        // Generar nodo incluyendo el peso actual en el segundo subconjunto
        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel], abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        pq.push(nodo2);

        if (stopearly && min_dif < 5) return min_dif;
    }

    return min_dif;
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly, bool iterativo) {
    if (iterativo) {
        return branch_and_bound_iterativo(pesos, shortcicuits, stopearly);
    } else {
        int min_dif = INT_MAX;
        particiones(pesos, 0, 0, 0, min_dif, shortcicuits, stopearly);
        return min_dif;
    }
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

    // Mostrar los pesos generados
    cout << "Pesos generados: ";
    for (int peso : pesos) {
        cout << peso << " ";
    }
    cout << endl;

    // Seleccionar opciones del algoritmo
    char opcionshortcicuits, opcionstopearly, opcioniterativo;
    cout << "¿Desea habilitar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿Desea habilitar 'stop early'? (s/n): ";
    cin >> opcionstopearly;
    cout << "¿Desea usar el algoritmo iterativo? (s/n): ";
    cin >> opcioniterativo;

    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');
    bool iterativo = (opcioniterativo == 's' || opcioniterativo == 'S');

    // Calcular la partición mínima
    int min_dif = particion_min(pesos, shortcicuits, stopearly, iterativo);

    // Mostrar el resultado
    cout << "La diferencia mínima entre las particiones es: " << min_dif << endl;

    return 0;
}
