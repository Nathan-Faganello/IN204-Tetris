#ifndef PIECE_H
#define PIECE_H


const int NB_PIECE = 7;
const int NB_ROTA = 4;
const int TAILLE_MAT = 4;


//définition de l'ensemble des pièces et de leurs rotations, représentées dans le sens de rotation horaire

static const int pieces[NB_PIECE][NB_ROTA][TAILLE_MAT][TAILLE_MAT] = {

	{//définition des pièces I 
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

	{//def des pièces O

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

	{//def des pièces T
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
	{//def des pièces L
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
	{//def des pièces J
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
	{//def des pièces Z
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
	{//def pièces S
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

}


enum class Type = { I, O, T, L, J, Z, S };
enum class Couleur = { CYAN, JAUNE, ORANGE, VIOLET, BLEU, ROUGE, VERT };

class Piece {
private:
	Type type;
	int rotation;
	int position_X;
	int position_Y;
	Couleur couleur;

public:
	Piece();
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
	void setPoxY(int theY) {
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
};

#endif // !PIECE_H

