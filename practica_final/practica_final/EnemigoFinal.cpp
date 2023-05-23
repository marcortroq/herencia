#include "EnemigoFinal.h"


EnemigoFinal::EnemigoFinal(
	int pVida, int pAtaque, string pNombre, int pSuperAttack, int pSuperAttack2) : Jugador
	(pVida, pAtaque, pNombre) 
	{superAttack = pSuperAttack;
	superAttack2 = pSuperAttack2;}

int EnemigoFinal::getSuperAttack() {
	return superAttack;
}
int EnemigoFinal::getSuperAttack2() {
	return superAttack2;
}

void EnemigoFinal::setSuperAttack(int pSuperAttack) {
	superAttack = pSuperAttack;
}

void EnemigoFinal::setSuperAttack2(int pSuperAttack2) {
	superAttack2 = pSuperAttack2;
}
