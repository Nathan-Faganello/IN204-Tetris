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

//Etats possibles des cases
enum class Etat {LIBRE, OCCUPE, MOUVEMENT};

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

			//on place la nouvelle pièce au point de spawn
			p.setPosX = spawn_X;
			p.setPosY = spawn_Y;

			//on définit le type de pièce
			int type = rand() % 7;
			p.setType(type);

			//on définit la rotation de la pièce (on choisit toujours la première par défaut)
			p.setRota(0);
		}

		void afficherPiece(Piece p) {

			int type = getType(p);
			int rotation = getRota(p);
			int x = getPosX();
			int y = getPosY();

			//On récupère la matrice associée à la pièce
			int ReprPiece[4][4] = pieces[type][rotation];



		}

		bool pieceTournable(Piece p) {

		}

		void tournerPiece(Piece p) {
			//On fait fait tourner la piece
			int newRota = ((p.getRota())+1)%4;
			p.setRota(newRota)
		}

		bool pieceDeplacable(Piece p) {

		}

		void deplacerPiece(Piece p) {

		}



};


#endif