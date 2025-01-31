
/*
Ejercicio 2: Piezas iniciales
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - Yael Octavio Pérez Méndez - A01799842
 *   - José Eduardo Rosas Ponciano - A01784461
 * Fecha de creación: 27/01/25
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<char> tablero(9, '.');
int Xgana = 0, Ogana = 0, empate = 0;

char ganador() {
    int ganadores[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        if (tablero[ganadores[i][0]] != '.' &&
            tablero[ganadores[i][0]] == tablero[ganadores[i][1]] &&
            tablero[ganadores[i][1]] == tablero[ganadores[i][2]]) {
            return tablero[ganadores[i][0]];
        }
    }
    return '.';
}

bool tableroLleno() {
    for (char cell : tablero) {
        if (cell == '.') return false;
    }
    return true;
}

/**
 * Funcion con el algoritmo minimax
 * @param jugador char que muestra si el jugador es 'X' o 'O'
 * @param profundidad profundidad recursiva
 * @param maxProfundidad profundidad recursiva máxima
 * @return no retorna nada
 */
int minimax(char jugador, int profundidad, int maxProfundidad) {
    char resultado = ganador();
    if (resultado == 'X') return 10 - profundidad;
    if (resultado == 'O') return profundidad - 10;
    if (tableroLleno()) return 0;

    if (profundidad >= maxProfundidad) return 0;

    int mejorValor = (jugador == 'X') ? numeric_limits<int>::min() : numeric_limits<int>::max();
    for (int i = 0; i < 9; i++) {
        if (tablero[i] == '.') {
            tablero[i] = jugador;
            int valor = minimax(jugador == 'X' ? 'O' : 'X', profundidad + 1, maxProfundidad);
            tablero[i] = '.';
            mejorValor = (jugador == 'X') ? max(mejorValor, valor) : min(mejorValor, valor);
        }
    }
    return mejorValor;
}

/**
 * Funcion para calcular el mejor movimiento de la computadora
 * @param jugador char que muestra si el jugador es 'X' o 'O'
 * @param nivel es el nivel de profundidad que utilizará la función minimax
 * @return entero que es la posición del mejor movimiento
 */
int mejorMovimiento(char jugador, int nivel) {
    vector<int> movimientos;
    for (int i = 0; i < 9; i++) {
        if (tablero[i] == '.') movimientos.push_back(i);
    }

    int profundidad = (nivel == 1) ? 3 : (nivel == 2) ? 6 : 9;

    int mejorValor = (jugador == 'X') ? numeric_limits<int>::min() : numeric_limits<int>::max();
    int mejorMov = -1;

    for (int mov : movimientos) {
        tablero[mov] = jugador;
        int valor = minimax(jugador == 'X' ? 'O' : 'X', 0, profundidad);
        tablero[mov] = '.';

        if ((jugador == 'X' && valor > mejorValor) || (jugador == 'O' && valor < mejorValor)) {
            mejorValor = valor;
            mejorMov = mov;
        }
    }
    return mejorMov;
}

// Función para imprimir el tablero
void imprimirTablero() {
    cout << "\nTablero actual:\n";
    for (int i = 0; i < 9; i++) {
        cout << tablero[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0));
    char jugador, computadora;
    int nivel;

    cout << "Elige tu ficha (X/O): ";
    cin >> jugador;
    computadora = (jugador == 'X') ? 'O' : 'X';

    cout << "Elige la dificultad (1: Principiante, 2: Medio, 3: Experto): ";
    cin >> nivel;

    char turno = 'X';
    while (ganador() == '.' && !tableroLleno()) {
        imprimirTablero();
        if (turno == jugador) {
            int pos;
            cout << "Elige una posicion (0-8): ";
            cin >> pos;
            if (pos < 0 || pos > 8 || tablero[pos] != '.') {
                cout << "Movimiento inválido, intenta de nuevo.\n";
                continue;
            }
            tablero[pos] = jugador;
        } else {
            int mejorMov = mejorMovimiento(computadora, nivel);
            tablero[mejorMov] = computadora;
            cout << "La computadora jugó en " << mejorMov << "\n";
        }
        turno = (turno == 'X') ? 'O' : 'X';
    }
    imprimirTablero();
    char resultado = ganador();
    if (resultado == jugador) cout << "¡Ganaste!" << endl;
    else if (resultado == computadora) cout << "Perdiste, la computadora ganó." << endl;
    else cout << "Empate." << endl;
    return 0;
}
