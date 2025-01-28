
/*
Ejercicio 7: heurística hill-climbing
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
#include <algorithm>
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

// Implementación de Hill-Climbing
int hill_climbing(const vector<int>& pesos) {
    int suma1 = 0, suma2 = 0;  // Inicializar las sumas de los dos subconjuntos
    int nivel = 0;            // Nivel actual del árbol
    int diferencia = INT_MAX; // Diferencia mínima encontrada

    while (nivel < pesos.size()) {
        // Generar los dos vecinos posibles
        int nueva_suma1 = suma1 + pesos[nivel];
        int nueva_suma2 = suma2 + pesos[nivel];

        // Calcular las diferencias para ambos vecinos
        int diferencia1 = abs(nueva_suma1 - suma2);
        int diferencia2 = abs(suma1 - nueva_suma2);

        // Seleccionar el vecino que minimice la diferencia
        if (diferencia1 < diferencia2) {
            suma1 = nueva_suma1;
            diferencia = diferencia1;
        } else {
            suma2 = nueva_suma2;
            diferencia = diferencia2;
        }

        // Si se alcanza una diferencia mínima posible, terminar
        if (diferencia == 0) break;

        // Avanzar al siguiente nivel
        nivel++;
    }

    // Retornar la diferencia mínima encontrada
    return diferencia;
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

    // Ordenar pesos en orden decreciente para mayor eficiencia
    sort(pesos.rbegin(), pesos.rend());

    // Mostrar los pesos generados
    cout << "Pesos generados (ordenados): ";
    for (int peso : pesos) {
        cout << peso << " ";
    }
    cout << endl;

    // Ejecutar el algoritmo Hill-Climbing
    int min_dif = hill_climbing(pesos);

    // Mostrar el resultado
    cout << "La diferencia mínima entre las particiones es: " << min_dif << endl;

    return 0;
}
