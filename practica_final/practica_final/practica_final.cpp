#include <windows.h>
#include <iostream>
#include <string>
#include "Jugador.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "EnemigoFinal.h"

using namespace std;

//MEDIDAS DEL MAPA

#define FILAS_MAPA 10
#define COLUMNAS_MAPA 5

//constante de ataques

int espada = 250;
int golpe = 400;
int magia = 500;

//DEFINIR VARIABLES

int posY;

//DEFINIR TABLERO

char tablero[FILAS_MAPA][COLUMNAS_MAPA];


//DEFINIR VARIABLES
int posHeroe;
boolean acabarJuego = false;


//Ataques heroes

int limitado = 2;
int ataque;
int contadorGuarida = 0;
    

int posicionesX() {
    //DADO PARA LA POSICION INICIAL DEL HEROE
    return rand() % 4 + 1;
}

int posicionesY() {
    //DADO PARA LA POSICION INICIAL DEL HEROE
    return rand() % 9 + 1;
}

void verificarPosiciones(Jugador& enemigo1, Jugador& enemigo2, Jugador& enemigo3, Jugador& enemigo4) {
    // Verificar y corregir posiciones repetidas
    while (enemigo1.getPosY() == enemigo2.getPosY() && enemigo1.getPosX() == enemigo2.getPosX()) {
        enemigo2.setPosY(posicionesY());
        enemigo2.setPosX(posicionesX());
    }

    while ((enemigo1.getPosY() == enemigo3.getPosY() && enemigo1.getPosX() == enemigo3.getPosX()) ||
        (enemigo2.getPosY() == enemigo3.getPosY() && enemigo2.getPosX() == enemigo3.getPosX())) {
        enemigo3.setPosY(posicionesY());
        enemigo3.setPosX(posicionesX());
    }

    while ((enemigo1.getPosY() == enemigo4.getPosY() && enemigo1.getPosX() == enemigo4.getPosX()) ||
        (enemigo2.getPosY() == enemigo4.getPosY() && enemigo2.getPosX() == enemigo4.getPosX()) ||
        (enemigo3.getPosY() == enemigo4.getPosY() && enemigo3.getPosX() == enemigo4.getPosX())) {
        enemigo4.setPosY(posicionesY());
        enemigo4.setPosX(posicionesX());
    }
}



void attackChose(Jugador& enemigo) {
    cout << "Que ataque quieres realizar:\n" "Espada[1]\n" "Golpe[2]\n" "Magia[3] Quedan " << limitado << " ataques restantes\n";
    cin >> ataque;

    if (ataque == 1) {
        enemigo.setVida(enemigo.getVida() - espada);
    }
    else if (ataque == 2) {
        enemigo.setVida(enemigo.getVida() - golpe);
    }
    else if (ataque == 3) {
        if (limitado != 0) {
            enemigo.setVida(enemigo.getVida() - magia);
            limitado -= 1;
        }
        else {
            cout << "no has podido atacar con magia no te quedan usos\n";
        }
    }
    else
    {
        "Has fallado, no existe ese ataque";
    }

    if (enemigo.getVida() <= 0) {
        enemigo.setVida(0);
    }
    cout << "Al " << enemigo.getNombre() << " le quedan " << enemigo.getVida() << " puntos de vida" << endl;

}

void enemiesAttack(Jugador& enemigo, Jugador& heroe) {
    
    heroe.setVida(heroe.getVida() - enemigo.getAtaque());
    if (heroe.getVida() <= 0) {
        heroe.setVida(0);
    }
    cout << "\nLos enemigos te han hecho " << enemigo.getAtaque() << " te quedan " << heroe.getVida() << " puntos de vida\n\n";
    }

void combateStart(Jugador& heroe, Jugador& enemigo) {
    if (heroe.getPosX() == enemigo.getPosX() && heroe.getPosY() == enemigo.getPosY() && enemigo.getVida() > 0) {
        cout << "\nAcabas de encontrarte con el " << enemigo.getNombre() << endl;
        cout << "Se inicia el combate" << endl;

        while (enemigo.getVida() > 0 && heroe.getVida() > 0) {
            attackChose(enemigo);
            if (enemigo.getVida() > 0) {
                enemiesAttack(enemigo, heroe);
            }
        }

        if (enemigo.getVida() <= 0) {
            cout << "Has derrotado al " << enemigo.getNombre() << "!" << endl;
            contadorGuarida++;
        }
        else {
            cout << "Has sido derrotado por el " << enemigo.getNombre() << "..." << endl;
        }

        Sleep(2000);
    }
}


void movimientoHeroe(int x, int y, Jugador& heroe) {
    char tecla = -1;
    tecla = _getch();
    tecla = toupper(tecla);
    switch (tecla) {
    case 'W':
        if (x - 1 >= 0) {
            heroe.setPosX(x - 1);
        } else {
            heroe.setPosX(x); // Si se pasa del límite superior, permanece en la misma posicion
        }
        break;
    case 'A':
        if (y - 1 >= 0) {
            heroe.setPosY(y - 1);
        } else {
            heroe.setPosY(COLUMNAS_MAPA - 1); // Si se pasa del límite izquierdo, vuelve a la posición derecha
        }
        break;
    case 'S':
        if (x + 1 < FILAS_MAPA) {
            heroe.setPosX(x + 1);
        } else {
            heroe.setPosX(x); // Si se pasa del límite inferior, permanece en la misma posicion
        }
        break;
    case 'D':
        if (y + 1 < COLUMNAS_MAPA) {
            heroe.setPosY(y + 1);
        } else {
            heroe.setPosY(0); // Si se pasa del límite derecho, vuelve a la posición izquierda
        }
        break;
    }
}


void defensaEnemigoFinal() {
    cout << "El enemigo final se defiende y reduce el daño recibido en el próximo turno.\n";
    espada = espada - 50;
    golpe = golpe - 50;
    magia = magia - 50;
}

void batallaFinal(Jugador& heroe, EnemigoFinal& enemigoFinal) {

    cout << "¡Ha llegado el momento de la batalla final!\n";
    Sleep(2000);

    while (heroe.getVida() > 0 && enemigoFinal.getVida() > 0) {
        cout << "\n==============================\n";
        cout << "Jugador:\tVida: " << heroe.getVida() << "\n";
        cout << "Enemigo Final:\tVida: " << enemigoFinal.getVida() << "\n";
        cout << "==============================\n";

        int opcion;
        cout << "Acciones disponibles:\n";
        cout << "1. ESPADA\n";
        cout << "2. GOLPE\n";
        cout << "3. MAGIA [" << limitado << " ataques restantes]\n";
        cout << "Elige tu acción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            enemigoFinal.setVida(enemigoFinal.getVida() - espada);
            cout << "Has usado espada.\n";
            break;
        case 2:
            enemigoFinal.setVida(enemigoFinal.getVida() - golpe);
            break;
        case 3:
            if (limitado != 0) {
                enemigoFinal.setVida(enemigoFinal.getVida() - magia);
                limitado -= 1;
            }
            else {
                cout << "No has podido atacar con magia. No te quedan usos.\n";
            }
            break;
        default:
            cout << "Has fallado. No existe ese ataque.\n";
            break;
        }

        // Comprobar vida del enemigo
        if (enemigoFinal.getVida() <= 0) {
            break; // Salir del bucle si el enemigo ha sido derrotado
        }

        // Turno del enemigo final
        int decisionEnemigo = rand() % 4 + 1;
        switch (decisionEnemigo) {
        case 1:
            heroe.setVida(heroe.getVida() - enemigoFinal.getAtaque());
            cout << "El enemigo final te ataca y te inflige " << enemigoFinal.getAtaque() << " puntos de daño.\n";
            Sleep(1000);
            break;
        case 2:
            defensaEnemigoFinal();
            Sleep(1000);
            break;
        case 3:
            heroe.setVida(heroe.getVida() - enemigoFinal.getSuperAttack());
            cout << "El enemigo final te ataca con su primer ataque especial y te inflige " << enemigoFinal.getSuperAttack() << " puntos de daño.\n";
            Sleep(1000);
            break;
        case 4:
            heroe.setVida(heroe.getVida() - enemigoFinal.getSuperAttack2());
            cout << "El enemigo final te ataca con su segundo ataque especial y te inflige " << enemigoFinal.getSuperAttack2() << " puntos de daño.\n";
            Sleep(1000);
            break;
        }

        // Comprobar vida del héroe
        if (heroe.getVida() <= 0) {
            break; // Salir del bucle si el héroe ha sido derrotado
        }

        Sleep(1000);
        system("cls");
    }

    if (heroe.getVida() <= 0) {
        cout << "Has sido derrotado. El enemigo final ha ganado la batalla.\n";
        Sleep(2000);
    }
    else {
        cout << "¡Felicidades! Has derrotado al enemigo final y has recuperado la paz en el reino.\n";
        Sleep(2000);
    }
    Sleep(2000);
}


void guaridaFinal(Jugador heroe, int guarida, EnemigoFinal enemigoFinal) {
    if (heroe.getPosX() == (FILAS_MAPA - 1) && heroe.getPosY() == guarida) {
        if (contadorGuarida == 4) {
            cout << "Entras en la guarida..." << endl;
            Sleep(500);
            cout << "ha aparecido el enemigo final " << enemigoFinal.getNombre() << endl;
            Sleep(2000);
            batallaFinal(heroe, enemigoFinal);
            acabarJuego = true;
        }
        else {
            cout << "No puedes entrar en la guarida ahi enemigos cerca (" << contadorGuarida << "/4)";
            Sleep(2000);
        }
    }   
}




void mapa(Jugador& heroe, Jugador& enemigo, Jugador& enemigo1, Jugador& enemigo2, Jugador& enemigo3, EnemigoFinal enemigoFinal) {
    int guarida = posicionesX();

    while (!acabarJuego)
    {
        bool enemigoEnPosicionGuarida = false;

        for (int i = 0; i < FILAS_MAPA; i++) {
            for (int j = 0; j < COLUMNAS_MAPA; j++) {
                cout << "  ";

                // Comprobar si hay un enemigo en la posición de la guarida
                if (i == (FILAS_MAPA - 1) && j == guarida) {
                    if (enemigo.getPosX() == i && enemigo.getPosY() == j) {
                        enemigoEnPosicionGuarida = true;
                    }
                    if (enemigo1.getPosX() == i && enemigo1.getPosY() == j) {
                        enemigoEnPosicionGuarida = true;
                    }
                    if (enemigo2.getPosX() == i && enemigo2.getPosY() == j) {
                        enemigoEnPosicionGuarida = true;
                    }
                    if (enemigo3.getPosX() == i && enemigo3.getPosY() == j) {
                        enemigoEnPosicionGuarida = true;
                    }
                    if (enemigoEnPosicionGuarida) {
                        guarida = (guarida + 1) % COLUMNAS_MAPA; // Cambiar la posición de la guarida evitando la posición ocupada por un enemigo
                        enemigoEnPosicionGuarida = false; // Resetea la variable
                    }
                }


                // Mostrar los elementos del mapa
                if (heroe.getPosX() == i && heroe.getPosY() == j) {
                    cout << tablero[i][j] << '@';
                }
                else if (enemigo.getPosX() == i && enemigo.getPosY() == j) {
                    if (enemigo.getVida() > 0) {
                        cout << tablero[i][j] << '$';
                    }
                    else {
                        cout << tablero[i][j] << '*';
                    }
                }
                else if (enemigo1.getPosX() == i && enemigo1.getPosY() == j) {
                    if (enemigo1.getVida() > 0) {
                        cout << tablero[i][j] << '$';
                    }
                    else {
                        cout << tablero[i][j] << '*';
                    }
                }
                else if (enemigo2.getPosX() == i && enemigo2.getPosY() == j) {
                    if (enemigo2.getVida() > 0) {
                        cout << tablero[i][j] << '$';
                    }
                    else {
                        cout << tablero[i][j] << '*';
                    }
                }
                else if (enemigo3.getPosX() == i && enemigo3.getPosY() == j) {
                    if (enemigo3.getVida() > 0) {
                        cout << tablero[i][j] << '$';
                    }
                    else {
                        cout << tablero[i][j] << '*';
                    }
                }

                else if (i == (FILAS_MAPA - 1) && j == guarida) {
                    cout << tablero[i][j] << 'G';
                }
                else {
                    cout << tablero[i][j] << '*';
                }
                cout << "  ";
            }
            cout << endl;
        }

        movimientoHeroe(heroe.getPosX(), heroe.getPosY(), heroe);
        combateStart(heroe, enemigo);
        combateStart(heroe, enemigo1);
        combateStart(heroe, enemigo2);
        combateStart(heroe, enemigo3);
        guaridaFinal(heroe, guarida, enemigoFinal);

        system("cls"); // Borra el mapa
    }
}





void presentacionJuego() {
    cout << "¡Bienvenido, valiente aventurero!" << endl;
    Sleep(1000);
    cout << "En este reino, la oscuridad se ha apoderado de nuestras tierras y nuestro pueblo sufre bajo el dominio de enemigos malevolos." << endl;
    Sleep(1000);
    cout << "Te necesitamos para liberarnos de este terrible destino y salvar nuestro amado reino." << endl;
    Sleep(1000);
    cout << "Tu mision es enfrentarte a cuatro poderosos enemigos dispersos por el territorio, derrotarlos uno por uno y recuperar la paz perdida." << endl;
    Sleep(1000);
    cout << "Una vez hayas derrotado a los cuatro enemigos, llegaras a la guarida, donde te enfrentaras al temible enemigo final." << endl;
    Sleep(1000);
    cout << "El enemigo final es un poderoso y despiadado adversario que ha sumido a nuestro reino en la oscuridad absoluta." << endl;
    Sleep(1000);
    cout << "¡Solo tu puedes detenerlo y devolvernos la luz!" << endl;
    Sleep(1000);
    cout << "Confiamos en que seras el heroe que necesitamos. ¡Adelante, valiente guerrero, y que la suerte este de tu lado!" << endl;

    cout << "\nPresiona Enter para comenzar la partida...";
    while (_getch() != 13); // Espera hasta que se presione la tecla Enter

    system("cls"); // Borra la pantalla
}



int main(){
    srand(time(NULL));

    Jugador enemigo1(1000, 100, "Zombie", posicionesY(), posicionesX());
    Jugador enemigo2(1000, 120, "Esqueleto", posicionesY(), posicionesX());
    Jugador enemigo3(1000, 150, "Ogro", posicionesY(), posicionesX());
    Jugador enemigo4(1000, 180, "Gobling", posicionesY(), posicionesX());

    //verifico que ninguno de los enemigos repiten posicion
    verificarPosiciones(enemigo1, enemigo2, enemigo3, enemigo4);

    //CREAMOS EL ENEMIGO FINAL

    EnemigoFinal enemigoFinal(2000, 150, "Dragon Oscuro", 500, 800);

    //CREAMOS AL HEROE
    posHeroe = posicionesX();
    Jugador heroe(3000, 100, "Heroe", 0, posHeroe);
    
    presentacionJuego();
    mapa(heroe, enemigo1, enemigo2, enemigo3, enemigo4, enemigoFinal);
}
    

