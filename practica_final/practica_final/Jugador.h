#pragma once
#include <iostream>

using namespace std; 


class Jugador
{
private: 
	int vida;
	int ataque;
	string nombre;
	int posX;
	int posY;
public:
	//CONSTRUCTOR
	Jugador(int pVida, int pAtaque, string pNombre, int pPosX, int pPosY);
	//CONSTRUCTOR PROPIO
	Jugador(int pVida, int pAtaque, string pNombre);

	//GETTER
	int getVida();
	int getAtaque();
	string getNombre();
	int getPosX();
	int getPosY();

	//SETTER

	void setVida(int pVida);
	void setPosX(int pPosX);
	void setPosY(int pPosY);


	//METODOS PROPIOS


};

