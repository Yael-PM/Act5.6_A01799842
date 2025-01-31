
/*
Ejercicio 4: Particiones
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
using namespace std;

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
    if (indice == pesos.size()){
        // Calcular diferencia actual entre las dos particiones
        int diferencia = abs(suma1 - suma2);
        if (diferencia < min_dif){
            min_dif = diferencia;

            // Si short circuit está habilitado y encontramos una solución óptima (diferencia = 0)
            if (shortcicuits && min_dif == 0) return;
        }
        return;
    }
    particiones(pesos, indice + 1, suma1 + pesos[indice], suma2, min_dif, shortcicuits, stopearly); //peso actual en el primer subconjunto

    // Si stop early está habilitado y ya encontramos una buena aproximación
    if (stopearly && min_dif < 5) return;

    particiones(pesos, indice + 1, suma1, suma2 + pesos[indice], min_dif, shortcicuits, stopearly); //peso actual en el segundo subconjunto
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly){
    int min_dif = INT_MAX;
    particiones(pesos, 0, 0, 0, min_dif, shortcicuits, stopearly);
    return min_dif;
}

/*
 * @brief Función principal que solicita parámetros al usuario y ejecuta el algoritmo de partición.
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

    // Validar que se puedan generar suficientes pesos únicos
    if (max_peso - min_peso + 1 < cantidad){
        cout << "el rango no puede generar suficientes valores." << endl;
        return 1;
    }

    //lista de pesos únicos
    vector<int> pesos = pesos_unicos
(cantidad, min_peso, max_peso);

    //mostrar los pesos generados
    cout << "Pesos generados: ";
    for (int peso : pesos){
        cout << peso << " ";
    }
    cout << endl;

    //short circuit o stop early
    char opcionshortcicuits, opcionstopearly;
    cout << "¿usar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿usar 'stop early'? (s/n): ";
    cin >> opcionstopearly;
    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');
    int min_dif = particion_min(pesos, shortcicuits, stopearly); //calcula la partición mínima
    cout << "solucion: " << min_dif << endl; //solución
    return 0;
}