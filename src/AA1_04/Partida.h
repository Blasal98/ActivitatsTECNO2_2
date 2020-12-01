#pragma once
#include "Tablero.h"
#include "Pieza.h"
#include "Movimiento.h"

class Partida {
	Tablero tablero;
	Pieza* piezas; // size = capacity = K_MAX_PIEZAS
	Movimiento* movimientos; // size = 0, capacity = K_MAX_MOVES

};