#pragma once

#define TIEMPOSECADO 30


struct Escenario {
	int y;
	char * escenario;

	Escenario(int py) {
		y = py;
		escenario = "--------------------------------------------------------------------------------";

	}
};

struct Gota{
	int x;
	int segundos;
	char * dibujo;
};

int hacerGota(int indiceEscenario, Escenario * escenario);

int secado(Gota * gota);