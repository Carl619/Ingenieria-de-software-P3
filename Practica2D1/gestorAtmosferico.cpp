#include "stdafx.h"
#include "gestorAtmosferico.h"

int hacerGota(int indiceEscenario, Escenario * escenario) {
	int gotaAleatoria = rand() % 20 + 1;
	if (gotaAleatoria < 2 && escenario->escenario[indiceEscenario] == '-') {
		return indiceEscenario;
	}

	return -1;
}


int secado(Gota * gota){
	gota->segundos--;
	if (gota->segundos == 0)
		return 1;
	return 0;
}