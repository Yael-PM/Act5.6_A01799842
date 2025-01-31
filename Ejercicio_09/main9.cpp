/*
Ejercicio 9:
¿Qué grupos encontraría un programa de particiones si usara la heurística
Hill-Climbing para los pesos 7, 9, 7, 6, 7, 7, 5, 7, 5 y 6?
¿Cuáles son los pesos totales de los grupos y la diferencia entre los pesos totales?
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
 *   - José Eduardo Rosas Ponciano - A01784461
 * Fecha de creación: 27/01/25
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <numeric>

using namespace std;

/*
 * @brief Calcula la diferencia entre el peso más alto y el más bajo de los grupos.
 * @param grupos Un vector de vectores que representa los grupos y sus elementos.
 * @return La diferencia de pesos entre el grupo más pesado y el más ligero.
 */
int calcular_diferencia(const vector<vector<int>>& grupos) {
    vector<int> pesos_totales;
    // Calculamos el peso total de cada grupo
    for (const auto& grupo : grupos) {
        pesos_totales.push_back(accumulate(grupo.begin(), grupo.end(), 0));
    }
    // Retornamos la diferencia entre el peso máximo y el mínimo
    return *max_element(pesos_totales.begin(), pesos_totales.end()) - *min_element(pesos_totales.begin(), pesos_totales.end());
}

/*
 * @brief Implementa el algoritmo Hill Climbing para obtener particiones equilibradas.
 * @param pesos Un vector con los pesos de los elementos a agrupar.
 * @param num_grupos Número de grupos en los que se deben dividir los elementos.
 */
void hill_climbing(vector<int> pesos, int num_grupos) {
    vector<vector<int>> grupos(num_grupos);

    // Ordenamos los pesos de mayor a menor para repartir los más pesados primero
    sort(pesos.begin(), pesos.end(), greater<int>());

    // Asignamos los elementos a los grupos de manera que se balanceen los pesos
    for (int peso : pesos) {
        auto min_it = min_element(grupos.begin(), grupos.end(), [](const vector<int>& a, const vector<int>& b) {
            // Seleccionamos el grupo con el menor peso total
            return accumulate(a.begin(), a.end(), 0) < accumulate(b.begin(), b.end(), 0);
        });
        min_it->push_back(peso);  // Añadimos el elemento al grupo con menor peso
    }

    // Imprimimos los grupos y sus pesos totales
    for (size_t i = 0; i < grupos.size(); ++i) {
        int peso_total = accumulate(grupos[i].begin(), grupos[i].end(), 0);
        cout << "Grupo " << i + 1 << ": ";
        for (int n : grupos[i]) cout << n << " ";  // Imprimimos los elementos del grupo
        cout << "| Peso total: " << peso_total << endl;
    }

    // Imprimimos la diferencia de pesos entre los grupos
    cout << "Diferencia de pesos: " << calcular_diferencia(grupos) << "\n\n";
}

int main() {
    // Datos de ejemplo con pesos de los elementos
    vector<int> pesos = {7, 9, 7, 6, 7, 7, 5, 7, 5, 6};
    int num_grupos = 2; // Cambia esto para probar diferentes agrupaciones

    // Inicializamos la semilla para la generación de números aleatorios
    srand(time(0));

    cout << "Ejecutando Hill Climbing con " << num_grupos << " grupos...\n";
    hill_climbing(pesos, num_grupos);

    return 0;
}
