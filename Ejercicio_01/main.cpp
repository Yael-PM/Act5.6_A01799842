
/*
Ejercicio 1: Backtracking en tic-tac-toe
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
 *   - José Eduardo Rosas Ponciano - A017
 * Fecha de creación: 27/01/25
 */

#include <iostream>
#include <vector>

using namespace std;

// Tablero de 3x3 del juego
vector<char> tablero(9, '.');

// Contadores de resultados
int Xgana = 0, Ogana = 0, empate = 0;

// Función para verificar si hay un ganador
char ganador() {
    int ganadores[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (auto &patron : ganadores) {
        if (tablero[patron[0]] != '.' &&
            tablero[patron[0]] == tablero[patron[1]] &&
            tablero[patron[1]] == tablero[patron[2]]) {
            return tablero[patron[0]];
            }
    }

    return '.'; // No hay ganador aún
}

/**
 * Funcion para calcular los posibles juegos
 * @param jugadorActual char que muestra si el jugador es 'X' o 'O'
 * @return no retorna nada
 */
void simular(char jugadorActual) {
    char winner = ganador();

    // Si hay un ganador o el tablero está lleno, registra el resultado
    if (winner == 'X') { Xgana++; return; }
    if (winner == 'O') { Ogana++; return; }

    bool lleno = true;
    for (char cell : tablero) {
        if (cell == '.') {
            lleno = false;
            break;
        }
    }

    if (lleno) {
        empate++;
        return;
    }

    for (int i = 0; i < 9; i++) {
        if (tablero[i] == '.') {
            tablero[i] = jugadorActual;
            simular(jugadorActual == 'X' ? 'O' : 'X');
            tablero[i] = '.';  // Deshacer el movimiento con backtracking
        }
    }
}

int main() {
    simular('X');

    cout << "Veces que gana X: " << Xgana << endl;
    cout << "Veces que gana O: " << Ogana << endl;
    cout << "Empate: " << empate << endl;

    int juegos = Xgana + Ogana + empate;
    cout << "Total de juegos: " << juegos << endl;
    cout << "El juego favorece a X si empieza primero" << endl;
    return 0;
}
