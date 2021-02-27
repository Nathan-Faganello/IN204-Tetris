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
	Piece(){}
	Piece(Type theType, int theRota, int theX, int theY, Couleur theColor): type(theType), rotation(theRota), position_X(theX), position_Y(theY), couleur(theColor) {}




	void setType(Type theType) {
		type = theType;
	}
	void setRota(int theRota) {
		rotation = theRota;
	}
	void setCouleur(Couleur theColor) {
		couleur = theColor;
	}
	void setPosX(int theX) {
		position_X = theX;
	}
	void setPosY(int theY) {
		position_Y = theY;
	}
	Type getType() {
		return type;
	}
	int getRota() {
		return rotation;
	}
	int getPosX() {
		return position_X;
	}
	int getPosY() {
		return position_Y;
	}
	Couleur getCouleur() {
		return couleur;
	}

	friend sf::Packet& operator <<(sf::Packet& packet, const Piece& piece);
	friend sf::Packet& operator >>(sf::Packet& packet, Piece& piece);

};


sf::Packet& operator <<(sf::Packet& packet, const Piece& piece)
{
		sf::Uint8 type = (sf::Uint8) piece.type;
		sf::Uint8 rota = (sf::Uint8) piece.rotation;
		sf::Uint8 posX = (sf::Uint8) piece.position_X;
		sf::Uint8 posY = (sf::Uint8) piece.position_Y;
		sf::Uint8 color = (sf::Uint8) piece.couleur;


		return (packet << type << rota << posX << posY << color);
}

sf::Packet& operator >>(sf::Packet& packet, Piece& piece)
{
		sf::Uint8 type;
		sf::Uint8 rota;
		sf::Uint8 posX;
		sf::Uint8 posY;
		sf::Uint8 color;

		packet >> type >> rota >> posX >> posY >> color;

		piece.type= (Type)type;
		piece.rotation=(int)rota;
		piece.position_X=(int)posX;
		piece.position_Y=(int)posY;
		piece.couleur=(Couleur)color;

		return packet ;
}

#endif // !PIECE_H
