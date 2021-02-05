#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include "piece.h"


//dimensions du plateau de jeu
const int hauteur = 22; 
const int largeur = 10;

//point d'apparition de la pièce (on prend pour référence le point de rotation de la pièce)
const int spawn_X = 1;
const int spawn_Y = largeur/2;


class Board {
	private :
		Piece piece_courante;
		Piece piece_suivante;

	public :
		int plateau[hauteur][largeur];

		Board() {
			//Initialisation du plateau de jeu : le plateau est numéroté de haut en bas (y)(ligne 0 en haut), et de gauche à droite (x)
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = Couleur::LIBRE;
				}
			}
		};

		void clearPlateau() {
			//on remet toutes les cases sur LIBRE
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = Couleur::LIBRE;
				}
			}
		}

		void nouvellePiece(Piece p) {

			//on place la nouvelle pièce au point de spawn
			p.setPosX = spawn_X;
			p.setPosY = spawn_Y;

			//on définit le type de pièce
			Type type = (Type)(rand() % 7);
			p.setType(type);

			//on définit la rotation de la pièce (on choisit toujours la première par défaut)
			p.setRota(0);
		}

		bool pieceSpawnable(piece p) {
			Type type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != Couleur::LIBRE) {
						return false;
					}
				}
			}
			return true;
		}

		void AfficherPiece(Piece p) {

			Type type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//on associe la bonne couleur aux pièces
			if (type == Type::I) {
				p.setCouleur(CYAN);
			}
			else if (type == Type::O) {
				p.setCouleur(JAUNE);
			}
			else if (type == Type::T) {
				p.setCouleur(ORANGE);
			}
			else if (type == Type::L) {
				p.setCouleur(VIOLET);
			}
			else if (type == Type::J) {
				p.setCouleur(BLEU);
			}
			else if (type == Type::Z) {
				p.setCouleur(ROUGE);
			}
			else {
				p.setCouleur(VERT);
			}

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j]==2) {
						plateau[x + i - 2][y + j - 1] = p.couleur;
					}
				}
			}
		}


		void EffacerPiece(piece p) {
			Type type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];



			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) {
						plateau[x + i - 2][y + j - 1] = Couleur::LIBRE;
					}
				}
			}
		}

		bool pieceTournable(Piece p) {
			int type = getType(p);
			int rotation = (getRota(p)+1)%4;
			int x = getPosX();
			int y = getPosY();

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (x+i-2 >= largeur || x+i-2<2 || y+j-1 >= hauteur || y+j-1 < 0) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					//si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pièces déjà posées
					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-2][y+j-1] != Couleur::LIBRE){
						return false;
					}
				}
			}
			return true;
		}

		void tournerPiece(Piece p) {
			//on verifie d'abord que l'on peut tourner la pièce
			if (pieceTournable(p)) {
				//Si oui, on efface la pièce dans sa position précédente et on la tourne
				int newRota = ((p.getRota()) + 1) % 4;
				p.setRota(newRota);;
			}
		}

		bool pieceDeplacableBas(Piece p) {
			Type type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY()+1;

			EffacerPiece(p);

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (y+j-1 >= hauteur) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}	

					//si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pièces déjà posées
					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-2][y+j-1] != Couleur::LIBRE){
						return false;
					}
				}
			}
			return true;
		}

		bool pieceDeplacableGauche(Piece p) {
			Type type = getType(p);
			int rotation = getRota(p);
			int x = getPosX()-1;
			int y = getPosY();

			EffacerPiece(p);


			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (x+i-2 < 0) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != Couleur::LIBRE) {
						return false;
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

			EffacerPiece(p);

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					if (x+i-2 >= largeur) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != Couleur::LIBRE) {
						return false;
					}
				}
			}
			return true;
		}

		bool deplacerPieceBas(Piece p) {
			//on verifie d'abord que l'on peut déplacer la pièce
			if (pieceDeplacableBas(p)) {
				//Si oui, on efface la pièce dans sa position précédente et on la déplace
				int newY = ((p.getPosY()) + 1);
				p.setPosY(NewY);
				AfficherPiece(p);

				return false;
			}

			else {
				AfficherPiece(p);

				return true
			}


		}

		void deplacerPieceGauche(Piece p) {
			//on verifie d'abord que l'on peut déplacer la pièce
			if (pieceDeplacableGauche(p)) {
				//Si oui, on efface la pièce dans sa position précédente et on la déplace
				int newX = ((p.getPosX()) - 1);
				p.setPosX(NewX);
			}

			AfficherPiece(p);
		}

		void deplacerPieceDroite(Piece p) {
			//on verifie d'abord que l'on peut déplacer la pièce
			if (pieceDeplacableDroite(p)) {
				//Si oui, on efface la pièce dans sa position précédente et on la déplace
				int newX = ((p.getPosX()) + 1);
				p.setPosX(NewX);
			}

			AfficherPiece(p);
		}


		void TomberPiece(piece p) {
			while (pieceDeplacableBas(p) ){
				deplacerPieceBas(p);
			}
		}

		int ligne_full() {
			int NbLignesSuppr = 0;
			int cases_pleines;

			for (int i=0; i<hauteur; i++) {
				cases_pleines = 0;

				//on parcourt la ligne en comptant le nombre de cases pleines pour savoir si la ligne est pleine
				for (int j=0; j<largeur; j++) {
					if (plateau[i][j] != Couleur::LIBRE) {
						cases_pleines++;
					}
				}

				//Si elle l'est, on déplace tout ce qui est au dessus vers le bas et on vide la ligne du haut du tableau
				if (cases_pleines == largeur) {
					NbLignesSuppr++;
					for (int k=i; k>0; k--) {
						memmove(&plateau[k], &plateau[k-1], largeur*sizeof(int));
					}

					for (int k=0; k<largeur; k++) {
						plateau[0][k]==Couleur::LIBRE;
					}
				}
			}

			return NbLignesSuppr;
		}


};


#endif