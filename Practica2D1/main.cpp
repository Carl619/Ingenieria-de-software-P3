// main.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include "gestorAtmosferico.h"


#define INICIOX 9
#define INICIOY 13
#define FIN 80


struct Personaje {
	int x;
	int y;
	char * dibujo;
	Personaje(int px, int py, char * dib)
	{
		x = px;
		y = py;
		dibujo = dib;
	}
};

struct Bala {
	int x;
	int y;
	char * dibujo;
	Bala(int px, int py, char * d)
	{
		x = px;
		y = py;
		dibujo = d;
	}
};


void llover();
void dibujarLuvia();
void secar();
void dibujarEscenario();
void dibujarBala(Bala * bala);
void moverBala(Bala * bala);
void dibujarPersonaje(Personaje pers);
void moverPersonaje(Personaje * pers, char * direccion);
void moverEnemigo(Personaje * enemigo);
Personaje * reaparicionEnemigo(Personaje pers);
Bala * disparar(char * direccion);
void colisiones();
void hacerMundo();
void accionTecla();

Personaje prota = { INICIOX,INICIOY,"*" };
Bala * bala = nullptr;
Personaje * enemigo = nullptr;
Escenario * mundo = new Escenario(14);
std::vector<Gota> gotas;

void gotoxy(int x, int y)
{
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void dibujarEscenario()
{
	gotoxy(0, mundo->y);
	printf(mundo->escenario);
	return;
}

void llover() {
	int indice = - 2;
	int indiceEscenario =  rand() % 79 + 1;

	indice = hacerGota(indiceEscenario, mundo);
	if (indice > 0)
		gotas.push_back({ indice,TIEMPOSECADO,"g" });
}

void dibujarLuvia() {
	for (int i = 0; i < gotas.size(); i++) {
		gotoxy(gotas[i].x, mundo->y);
		printf(gotas[i].dibujo);
	}
}

void secar() {
	for (int i = 0; i < gotas.size(); i++) {
		secado(&gotas[i]);
		if (gotas[i].segundos < 0)
			gotas.erase(gotas.begin() + i);
	}
}

void hacerMundo() {
	dibujarEscenario();
	dibujarLuvia();
	dibujarPersonaje(prota);


	if (bala != nullptr) {
		moverBala(bala);
		dibujarBala(bala);
	}

	if (enemigo != nullptr) {
		moverEnemigo(enemigo);
		dibujarPersonaje(*enemigo);
	}


	if (enemigo == nullptr) {
		enemigo = reaparicionEnemigo(prota);
		if (enemigo != nullptr)
		dibujarPersonaje(*enemigo);
	}

}

void colisiones() {
	if (enemigo != nullptr && bala != nullptr)
		if (enemigo->x == bala->x || enemigo->x - 1 == bala->x || enemigo->x + 1 == bala->x) {
			delete bala;
			bala = nullptr;
			delete enemigo;
			enemigo = nullptr;
		}

	if (bala != nullptr)
		if (bala->x <= 0 || bala->x > 80) {
			delete bala;
			bala = nullptr;
		}
}

Bala * disparar(char * direccion)
{
	Bala * b;
	if (strcmp(direccion, "der") == 0)
		b = new Bala(prota.x + 1, prota.y, ">");
	else if (strcmp(direccion, "izq") == 0)
		b = new Bala(prota.x - 1, prota.y, "<");
	else return nullptr;
	return b;

}

void dibujarPersonaje(Personaje pers)
{
	gotoxy(pers.x, pers.y);
	printf(pers.dibujo);
	return;
}

void dibujarBala(Bala * bal) {
	gotoxy(bal->x, bal->y);
	printf(bal->dibujo);
	return;
}

void moverBala(Bala * bal)
{
	if (strcmp(bal->dibujo, ">") == 0)
		bal->x++;
	else if (strcmp(bal->dibujo, "<") == 0)
		bal->x--;
	else return;

	return;
}

void moverPersonaje(Personaje * pers, char * direccion)
{
	if (pers->x > 0 && pers->x < 80) {
		if (strcmp(direccion, "der") == 0)
			pers->x++;
		else if (strcmp(direccion, "izq") == 0)
			pers->x--;
	}
	else {
		if (pers->x == 0)
			pers->x++;
		else
			pers->x--;
	}
	return;
}

void moverEnemigo(Personaje * ene)
{

	int movimientoAleatorio = rand() % 2 + 1;
	if (ene->x > 0 && ene->x < FIN) {
		if (movimientoAleatorio == 1)
			ene->x++;
		else if (movimientoAleatorio == 2)
			ene->x--;
	}
	else {
		if (ene->x == 0)
			ene->x++;
		else
			ene->x--;
	}
	return;
}

Personaje * reaparicionEnemigo(Personaje pers)
{
	int movimientoAleatorio = rand() % 79 + 1;
	if (movimientoAleatorio != pers.x && movimientoAleatorio != pers.x + 1 && movimientoAleatorio != pers.x + 2 && movimientoAleatorio != pers.x - 1 && movimientoAleatorio != pers.x - 2) {
		return new Personaje(movimientoAleatorio, INICIOY, "/");
	}
	return nullptr;
}

void clear()
{
	system("cls");
}

void update() {
	clear();
	hacerMundo();
	colisiones();
	secar();
	llover();
}

void accionTecla() {
	int c;
	if (_kbhit()) {
		c = _getch();
		if (c == 'a')
			moverPersonaje(&prota, "izq");
		else if (c == 'd')
			moverPersonaje(&prota, "der");
		if (bala == nullptr) {
			if (c == 'q')
				bala = disparar("izq");
			else if (c == 'e')
				bala = disparar("der");
		}
		return;
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	while (1) {
		update();
		accionTecla();
		Sleep(100);
	}
	return 0;
}


