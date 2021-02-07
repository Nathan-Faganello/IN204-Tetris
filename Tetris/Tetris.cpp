// Tetris.cpp : définit le point d'entrée de l'application.
//

#include<cmath>
#include "Tetris.h"
#include"board.h"
#include"piece.h"
#include"game.h"
#include<SFML/System/Time.hpp>

using namespace std;

int main()
{
	 sf::Window window(sf::VideoMode(1080, 720), "Tetris-IN204-Faganello-Laforge");

	 sf::Time dropSpeed = sf::seconds(1.5)*pow(1.1, (double)niveau);

	 bool fin_jeu = false;
	 bool etat_pause = false;

	 
}
