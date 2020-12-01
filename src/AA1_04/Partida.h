#pragma once
#include "Tablero.h"
#include "Pieza.h"
#include "Movimiento.h"

class Partida {
	Tablero tablero; //NOT BENNE, ha de ser agregació -> puntero tablero
	Pieza* piezas; // size = capacity = K_MAX_PIEZAS //BENNE
	Movimiento* movimientos; // size = 0, capacity = K_MAX_MOVES //BENNE

};