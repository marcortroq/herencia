#pragma once
#include "Jugador.h";
#include <iostream>

using namespace std;

class EnemigoFinal : public Jugador
{
private:
	
	int superAttack;
	int superAttack2;

public:
	//CONSTRUCTOR CON ELEMENTOS DE LA CLASE PADRE Y PROPIA
	EnemigoFinal(int pVida, int pAtaque, string pNombre, int superAttack, int superAttack2);

	int getSuperAttack();
	int getSuperAttack2();

	void setSuperAttack(int pSuperAttack);
	void setSuperAttack2(int pSuperAttack2);

};

