#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include "piece.h"


//dimensions du plateau de jeu
const int hauteur = 22;
const int largeur = 10;

//point d'apparition de la pi�ce (on prend pour r�f�rence le point de rotation de la pi�ce)
const int spawn_X = 1;
const int spawn_Y = largeur/2;

//Etats possibles des cases
enum class Etat { LIBRE=0, OCCUPE=1 , MOUVEMENT=2 };

class Board {
	private :
		Piece piece_courante;
		Piece piece_suivante;

	public :
		int plateau[hauteur][largeur];

		Board() {
			//Initialisation du plateau de jeu : le plateau est num�rot� de haut en bas (y)(ligne 0 en haut), et de gauche � droite (x)
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = Etat::LIBRE;
				}
			}
		};

		void clearPlateau() {
			//on remet toutes les cases sur LIBRE
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = Etat::LIBRE;
				}
			}
		}

		void nouvellePiece(Piece p) {

			//on place la nouvelle pi�ce au point de spawn
			p.setPosX = spawn_X;
			p.setPosY = spawn_Y;

			//on d�finit le type de pi�ce
			int type = rand() % 7;
			p.setType(type);

			//on d�finit la rotation de la pi�ce (on choisit toujours la premi�re par d�faut)
			p.setRota(0);
		}

		bool pieceSpawnable(piece p) {
			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] == 1) {
						return false;
					}
				}
			}
			return true;
		}

		void AfficherPiece(Piece p) {

			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//on associe la bonne couleur aux pi�ces
			if (type == I) {
				p.setCouleur(CYAN);
			}
			else if (type == O) {
				p.setCouleur(JAUNE);
			}
			else if (type == T) {
				p.setCouleur(ORANGE);
			}
			else if (type == L) {
				p.setCouleur(VIOLET);
			}
			else if (type == J) {
				p.setCouleur(BLEU);
			}
			else if (type == Z) {
				p.setCouleur(ROUGE);
			}
			else {
				p.setCouleur(VERT);
			}

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j]==2) {
						plateau[x + i - 2][y + j - 1] = 1;
					}
				}
			}
		}

		void AfficherPieceMouvement(Piece p) {

			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) {
						plateau[x + i - 2][y + j - 1] = 2;
					}
				}
			}
		}

		void EffacerPieceMouvement(piece p) {
			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) {
						plateau[x + i - 2][y + j - 1] = 0;
					}
				}
			}
		}

		bool pieceTournable(Piece p) {
			int type = getType(p);
			int rotation = (getRota(p)+1)%4;
			int x = getPosX();
			int y = getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-2][y+j-1] == 1){
						return false;
					}
				}
			}
			return true;
		}

		void tournerPiece(Piece p) {
			//on verifie d'abord que l'on peut tourner la pi�ce
			if (pieceTournable(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la tourne
				EffacerPieceMouvement(p);
				int newRota = ((p.getRota()) + 1) % 4;
				p.setRota(newRota);
				AfficherPieceMouvement(p);
			}
		}

		bool pieceDeplacableBas(Piece p) {
			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY()+1;


			//on est oblig� de distinguer les cas en fonction des pi�ces et rotation car elles ne prennent pas toutes exactement la m�me place
			if (y >= hauteur-3 && (type == 0 && (rotation == 1 || rotation == 3)) ) {
				return false;
			}

			else if (y >= hauteur-1 && (type == 0 && (rotation = 0 || rotation == 2)) || (type == 2 && rotation == 2) || (type == 3 && rotation == 2) || (type == 4 && rotation == 2) || (type == 3 && rotation == 2)) {
				return false;
			}

			else if (y >= hauteur-2) {
				return false;
			}

			else {
				//On r�cup�re la matrice associ�e � la pi�ce
				int ReprPiece[4][4] = pieces[type][rotation];

				for (int i = 0; i <= 3; i++) {
					for (int j = 0; j <= 3; j++) {
						if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] == 1) {
							return false;
						}
					}
				}
			}
			return true;
		}

		bool pieceDeplacableGauche(Piece p) {
			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX()-1;
			int y = getPosY();

			if (x <= 0 && ((type == 0 && (rotation = 1 || rotation == 3)) || (type == 2 && rotation == 3) || (type == 3 && rotation == 3) || (type == 4 && rotation == 3))){
				return false;
			}

			else if (y <= 2 && type == 0 && (rotation = 0 || rotation == 2)) {
				return false;
			}

			else if (y <= 1) {
				return false;
			}

			else {
				//On r�cup�re la matrice associ�e � la pi�ce
				int ReprPiece[4][4] = pieces[type][rotation];

				for (int i = 0; i <= 3; i++) {
					for (int j = 0; j <= 3; j++) {
						if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] == 1) {
							return false;
						}
					}
				}
			}
			return true;
		}

		bool pieceDeplacableDroite(Piece p) {
			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX()+1;
			int y = getPosY();

			if (y >= largeur - 1 && ((type == 0 && (rotation == 1 || rotation == 3)) || type == 1 || (type == 2 && (rotation == 1)) || (type == 3 && (rotation == 1)) || (type == 4 && (rotation == 1)) || (type == 5 && (rotation == 1 || rotation == 3)) || (type == 6 && (rotation == 1 || rotation == 3)))) {
				return false;
			}

			else if (y >= largeur - 2) {
				return false;
			}

			else {
				//On r�cup�re la matrice associ�e � la pi�ce
				int ReprPiece[4][4] = pieces[type][rotation];

				for (int i = 0; i <= 3; i++) {
					for (int j = 0; j <= 3; j++) {
						if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] == 1) {
							return false;
						}
					}
				}
			}
			return true;
		}

		bool deplacerPieceBas(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableBas(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				EffacerPieceMouvement(p);
				int newY = ((p.getPosY()) + 1);
				p.setPosY(NewY);
				AfficherPieceMouvement(p);

				return false;
			}

			else {
				AfficherPiece(p);

				return true
			}


		}

		void deplacerPieceGauche(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableGauche(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				EffacerPieceMouvement(p);
				int newX = ((p.getPosX()) - 1);
				p.setPosX(NewX);
				AfficherPieceMouvement(p);
			}
		}

		void deplacerPieceDroite(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableDroite(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				EffacerPieceMouvement(p);
				int newX = ((p.getPosX()) + 1);
				p.setPosX(NewX);
				AfficherPieceMouvement(p);
			}
		}


		void TomberPiece(piece p) {
			while (pieceDeplacableBas(p) ){
				deplacerPieceBas(p);
			}
		}

};


#endif