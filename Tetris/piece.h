#ifndef PIECE_H
#define PIECE_H

#include <SFML/Network/Packet.hpp>

const int NB_PIECE = 7;
const int NB_ROTA = 4;
const int TAILLE_MAT = 4;


//d�finition de l'ensemble des pi�ces et de leurs rotations, repr�sent�es dans le sens de rotation horaire

static const int pieces[NB_PIECE][NB_ROTA][TAILLE_MAT][TAILLE_MAT] {

	{//d�finition des pi�ces I
		{
			{0, 0, 0, 0},
			{ 1, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},

		{
			{0, 0, 1, 0},
			{0, 0, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},

		{
			{0, 0, 0, 0},
			{1, 1, 2, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},

		{
			{0, 0, 1, 0},
			{0, 0, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},

	},

	{//def des pi�ces O

		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	},

	{//def des pi�ces T
		{
			{0, 0, 0, 0},
			{0, 1, 2, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 1, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 1, 2, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 0, 2, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{//def des pi�ces L
		{
			{0, 0, 0, 0},
			{0, 1, 2, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 1, 0},
			{0, 0, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 1},
			{0, 1, 2, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 0, 2, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0}
		}
	},
	{//def des pi�ces J
		{
			{0, 0, 0, 0},
			{0, 1, 2, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 2, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 1, 0, 0},
			{0, 1, 2, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 1},
			{0, 0, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		}
	},
	{//def des pi�ces Z
		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 1, 2, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 2, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 1, 2, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
		}
	},
	{//def pi�ces S
		{
			{0, 0, 0, 0},
			{0, 0, 2, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 2, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 2, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}
	}

};


enum class Type { I, O, T, L, J, Z, S };
enum class Couleur { CYAN, JAUNE, ORANGE, VIOLET, BLEU, ROUGE, VERT, LIBRE };

class Piece {
private:
	Type type;
	int rotation;
	int position_X;
	int position_Y;
	Couleur couleur;

public:


	Piece();
	Piece(Type theType, int theRota, int theX, int theY, Couleur theColor);




	void setType(Type theType);
	void setRota(int theRota);
	void setCouleur(Couleur theColor);
	void setPosX(int theX);
	void setPosY(int theY);
	Type getType();
	int getRota();
	int getPosX();
	int getPosY();
	Couleur getCouleur();

	friend sf::Packet& operator <<(sf::Packet& packet, const Piece& piece); //surcharge d'opérateur pour manipuler plus facilement ensemble les packets et les pièces.
	friend sf::Packet& operator >>(sf::Packet& packet, Piece& piece);

};





#endif // !PIECE_H
