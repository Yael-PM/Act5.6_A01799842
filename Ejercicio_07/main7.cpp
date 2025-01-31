
/*
Ejercicio 7: Particiones con Branch and Bound y heurística aleatoria
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
#include <random>
using namespace std;

/*
 * @brief nodo en el árbol de soluciones para el algoritmo Branch and Bound.
 */
struct Nodo{
    int nivel;
    int suma1;
    int suma2;
    int diferencia;

    bool operator<(const Nodo& otro) const{ //sobrecarga para usar Nodo en una cola de prioridad
        return diferencia > otro.diferencia; // menor diferencia tiene mayor prioridad
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
 * @brief Implementa el algoritmo Branch and Bound con heurística aleatoria para encontrar la partición mínima.
 * @param pesos Vector de enteros con los pesos a particionar.
 * @param shortcicuits Habilita la optimización de atajos si se encuentra una solución óptima temprana.
 * @param stopearly Finaliza si la diferencia mínima encontrada es menor a un umbral definido.
 * @param random_heuristic Activa el uso de heurística aleatoria para decidir si se expanden nodos.
 * @param heuristic_prob Probabilidad de expansión de nodos cuando la heurística aleatoria está activada.
 * @return diferencia mínima entre las sumas de los dos subconjuntos.
 */
int branch_and_bound_heuristica(const vector<int>& pesos, bool shortcicuits, bool stopearly, bool random_heuristic, double heuristic_prob){
    priority_queue<Nodo> pq;
    pq.push({0, 0, 0, 0});
    int min_dif = INT_MAX;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
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
        //agrega nodo con heurística
        if (!random_heuristic || dis(gen) < heuristic_prob){
            pq.push(nodo1);
        }

        //genera nodo incluyendo en el peso actual en el segundo subconjunto
        Nodo nodo2 = {actual.nivel + 1, actual.suma1, actual.suma2 + pesos[actual.nivel], abs(actual.suma1 - (actual.suma2 + pesos[actual.nivel]))};
        //agrega nodo con heurística
        if (!random_heuristic || dis(gen) < heuristic_prob){
            pq.push(nodo2);
        }
        if (stopearly && min_dif < 5) return min_dif;
    }
    return min_dif;
}

// Función principal para calcular la diferencia mínima entre particiones
int particion_min(const vector<int>& pesos, bool shortcicuits, bool stopearly, bool random_heuristic, double heuristic_prob){
    return branch_and_bound_heuristica(pesos, shortcicuits, stopearly, random_heuristic, heuristic_prob);
}

/*
 * @brief Función principal que solicita parámetros de entrada, genera los pesos y ejecuta el algoritmo.
 * @return ejecución exitosa.
 */

int main(){
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
    if (max_peso - min_peso + 1 < cantidad){
        cout << "Error: El rango de pesos no permite generar suficientes valores únicos." << endl;
        return 1;
    }

    // Generar lista de pesos únicos
    vector<int> pesos = pesos_unicos(cantidad, min_peso, max_peso);

    // Mostrar los pesos generados
    cout << "Pesos generados: ";
    for (int peso : pesos){
        cout << peso << " ";
    }
    cout << endl;

    // Seleccionar opciones del algoritmo
    char opcionshortcicuits, opcionstopearly, opcionheuristica;
    cout << "¿usar 'short circuit'? (s/n): ";
    cin >> opcionshortcicuits;
    cout << "¿usar 'stop early'? (s/n): ";
    cin >> opcionstopearly;
    cout << "¿usar heurística aleatoria? (s/n): ";
    cin >> opcionheuristica;

    bool shortcicuits = (opcionshortcicuits == 's' || opcionshortcicuits == 'S');
    bool stopearly = (opcionstopearly == 's' || opcionstopearly == 'S');
    bool random_heuristic = (opcionheuristica == 's' || opcionheuristica == 'S');

    //heurística aleatoria
    double heuristic_prob = 0.5; //50%
    if (random_heuristic){
        cout << "probabilidad de nodos (0.0 a 1.0): ";
        cin >> heuristic_prob;
    }
    int min_dif = particion_min(pesos, shortcicuits, stopearly, random_heuristic, heuristic_prob); //partición mínima
    cout << "solucion: " << min_dif << endl; //solución
    return 0;
}
