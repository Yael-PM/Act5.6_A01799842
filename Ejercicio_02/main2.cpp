
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

    for (int i = 0; i < 8; i++) {
        if (tablero[ganadores[i][0]] != '.' &&
            tablero[ganadores[i][0]] == tablero[ganadores[i][1]] &&
            tablero[ganadores[i][1]] == tablero[ganadores[i][2]]) {
            return tablero[ganadores[i][0]];
        }
    }

    return '.'; // No hay ganador aún
}

/**
 * Funcion para simular los posibles juegos
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

/**
 * Funcion que imprime el tablero
 * @param numerado es un booleano que muestra el tablero numerado o no
 * @return no retorna nada
 */
void imprimirTablero(bool numerado = false) {
    cout << "\nTablero actual:\n";
    for (int i = 0; i < 9; i++) {
        if (numerado) {
            cout << i << " ";  // Muestra los números de las casillas
        } else {
            cout << tablero[i] << " ";  // Muestra el estado actual del tablero
        }

        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

int main() {
    int posicion;
    char ficha;
    char jugadorInicial = 'X';

    cout << "Posiciones del tablero:\n";
    imprimirTablero(true);  // Muestra la versión numerada del tablero

    cout << "Ingresa una posicion (0-8) seguida del jugador (X/O), usa -1 para terminar:\n";

    while (true) {
        imprimirTablero();
        cout << "Posicion (0-8): ";
        cin >> posicion;
        if (posicion == -1) break;

        if (posicion < 0 || posicion > 8 || tablero[posicion] != '.') {
            cout << "Posición invalida o ya ocupada, intenta otra.\n";
            continue;
        }

        cout << "Jugador (X/O): ";
        cin >> ficha;

        if (ficha == 'X' || ficha == 'O') {
            tablero[posicion] = ficha;
        } else {
            cout << "Ficha invalida, usa 'X' o 'O'.\n";
        }
    }

    // Determinar quién sigue jugando según la cantidad de movimientos
    int cuentaX = 0, cuentaO = 0;
    for (char cell : tablero) {
        if (cell == 'X') cuentaX++;
        if (cell == 'O') cuentaO++;
    }
    jugadorInicial = (cuentaX > cuentaO) ? 'O' : 'X';

    simular(jugadorInicial);

    cout << "Resultados desde esta configuracion inicial:\n";
    cout << "Veces que gana X: " << Xgana << endl;
    cout << "Veces que gana O: " << Ogana << endl;
    cout << "Empates: " << empate << endl;
    cout << "Total de juegos posibles: " << (Xgana + Ogana + empate) << endl;

    return 0;
}