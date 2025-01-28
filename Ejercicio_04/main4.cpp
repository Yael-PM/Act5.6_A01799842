
/*
Ejercicio 4: Particiones
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
using namespace std;

// Generar una lista de pesos aleatorios sin duplicados
vector<int> pesos_unicos(int cantidad, int min_peso, int max_peso) {
    set<int> unicos_pesos;
    while (unicos_pesos.size() < cantidad) {
        int peso = rand() % (max_peso - min_peso + 1) + min_peso;
        unicos_pesos.insert(peso);
    }
    return vector<int>(unicos_pesos.begin(), unicos_pesos.end());
}

// Función recursiva para calcular las particiones y su diferencia mínima
void particiones(const vector<int>& pesos, int indice, int suma1, int suma2, int& min_dif, bool shortcicuits, bool stopearly) {
    if (indice == pesos.size()) {
        // Calcular diferencia actual entre las dos particiones
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif) {
            min_dif = diferencia;

            // Si short circuit está habilitado y encontramos una solución óptima (diferencia = 0)
            if (shortcicuits && min_dif == 0) return;
        }
        return;
    }

    // Incluir el peso actual en el primer subconjunto
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif, shortcicuits, stopearly);

    // Si stop early está habilitado y ya encontramos una buena aproximación
    if (stopearly && min_dif < 5) return;  // Ejemplo: detenerse si la diferencia es menor a 5

    // Incluir el peso actual en el segundo subconjunto
    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif, shortcicuits, stopearly);
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly) {
    int min_dif = INT_MAX;
    particiones(pesos, 0, 0, 0, min_dif, shortcicuits, stopearly);
    return min_dif;
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
    vector<int> pesos = pesos_unicos
(cantidad, min_peso, max_peso);

    // Mostrar los pesos generados
    cout << "Pesos generados: ";
    for (int peso : pesos) {
        cout << peso << " ";
    }
    cout << endl;

    // Seleccionar si se usará short circuit o stop early
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