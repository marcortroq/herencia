#include "Jugador.h"
#include <iostream>
using namespace std;

//CONSTRUCTOR
Jugador::Jugador(int pVida, int pAtaque, string pNombre, int pPosX, int pPosY) {
	vida = pVida;
	ataque = pAtaque;
	nombre = pNombre;
	posX = pPosX; 
	posY =  pPosY;
}
Jugador::Jugador(int pVida, int pAtaque, string pNombre) {
	vida = pVida;
	ataque = pAtaque;
	nombre = pNombre;
}



//GETTERS
	string Jugador::getNombre(){
		return nombre;
	}
	int Jugador::getPosX(){
		return posX;
	}
	int Jugador::getPosY() {
		return posY;
	}
	int Jugador::getVida() {
		return vida;
	}
	int Jugador::getAtaque() {
		return ataque;
	}

//SETTER
	void Jugador::setPosX(int pPosX) {
		posX = pPosX;
	}
	void Jugador::setPosY(int pPosY) {
		posY = pPosY;
	}
	void Jugador::setVida(int pVida) {
		vida = pVida;
	}

//METODOS PROPIOS

