
/*
Ejercicio 10: heurística hill-climbing
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
#include <algorithm>
using namespace std;

/*
 * @brief Genera una lista de pesos únicos dentro de un rango dado.
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
 * @brief Implementa el algoritmo de Hill-Climbing para minimizar la diferencia entre dos subconjuntos de pesos.
 * @param pesos Vector de enteros que representa los pesos a particionar.
 * @return La diferencia mínima encontrada entre las sumas de los dos subconjuntos.
 */

int hill_climbing(const vector<int>& pesos){
    int suma1 = 0, suma2 = 0;
    int nivel = 0;
    int diferencia = INT_MAX;

    while (nivel < pesos.size()) {
        // Generar los dos vecinos posibles
        int nueva_suma1 = suma1 + pesos[nivel];
        int nueva_suma2 = suma2 + pesos[nivel];

        // Calcular las diferencias para ambos vecinos
        int diferencia1 = abs(nueva_suma1 - suma2);
        int diferencia2 = abs(suma1 - nueva_suma2);

        // Seleccionar el vecino que minimice la diferencia
        if (diferencia1 < diferencia2){
            suma1 = nueva_suma1;
            diferencia = diferencia1;
        } else{
            suma2 = nueva_suma2;
            diferencia = diferencia2;
        }
        if (diferencia == 0) break;
        nivel++; //siguiente nivel
    }
    return diferencia; //dif minima
}

/*
 * @brief Función principal que solicita parámetros de entrada, genera los pesos y ejecuta el algoritmo Hill-Climbing.
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
    cout << "Pesos generados (hill-cimbing): ";
    for (int peso : pesos){
        cout << peso << " ";
    }
    cout << endl;
    int min_dif = hill_climbing(pesos); //ejecutar el algoritmo Hill-Climbing
    cout << "Solucion: " << min_dif << endl; //solución
    return 0;
}
