#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <string.h>
#include "piece.h"
#include <time.h>
#include <stdlib.h>


//dimensions du plateau de jeu
const int hauteur = 22;
const int largeur = 10;

//point d'apparition de la pi�ce (on prend pour r�f�rence le point de rotation de la pi�ce)
const int spawn_X = 1;
const int spawn_Y = largeur/2;


class Board {
	private :
		Piece piece_courante;
		Piece piece_suivante;

	public :
		int plateau[hauteur][largeur];

		Piece getPieceSuivante(){
			return piece_suivante;
		}
		Piece getPieceCourante(){
			return piece_courante;
		}
		Board() {
			//Initialisation du plateau de jeu : le plateau est num�rot� de haut en bas (y)(ligne 0 en haut), et de gauche � droite (x)
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = (int)Couleur::LIBRE;
				}
			}
		};

		void clearPlateau() {
			//on remet toutes les cases sur LIBRE
			for (int i = 0; i < hauteur; i++) {
				for (int j = 0; j < largeur; j++) {
					plateau[i][j] = (int)Couleur::LIBRE;
				}
			}
		}

		void setPieceCourante(){
			piece_courante=piece_suivante;
		}

		void setPieceSuivante(){
			//on place la nouvelle pi�ce au point de spawn
			piece_suivante.setPosX(spawn_X);
			piece_suivante.setPosY(spawn_Y);

			//on d�finit le type de pi�ce
			Type type = (Type)(rand() % 7);
			piece_suivante.setType(type);
			piece_suivante.setCouleur((Couleur)((int)type));
			//on d�finit la rotation de la pi�ce (on choisit toujours la premi�re par d�faut)
			piece_suivante.setRota(0);
		}


		bool pieceSpawnable(Piece p) {
			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX();
			int y = p.getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]), 16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != (int)Couleur::LIBRE) {
						return false;
					}
				}
			}
			return true;
		}

		void AfficherPiece(Piece p) {

			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX();
			int y = p.getPosY();

			//on associe la bonne couleur aux pi�ces
			if (type == (int)Type::I) {
				p.setCouleur(Couleur::CYAN);
			}
			else if (type == (int)Type::O) {
				p.setCouleur(Couleur::JAUNE);
			}
			else if (type == (int)Type::T) {
				p.setCouleur(Couleur::ORANGE);
			}
			else if (type == (int)Type::L) {
				p.setCouleur(Couleur::VIOLET);
			}
			else if (type == (int)Type::J) {
				p.setCouleur(Couleur::BLEU);
			}
			else if (type == (int)Type::Z) {
				p.setCouleur(Couleur::ROUGE);
			}
			else {
				p.setCouleur(Couleur::VERT);
			}

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]), 16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j]==2) {
						plateau[x + i - 2][y + j - 1] = (int)p.getCouleur();
					}
				}
			}
		}


		void EffacerPiece(Piece p) {
			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX();
			int y = p.getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]), 16);



			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					if (ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) {
						plateau[x + i - 2][y + j - 1] = (int)Couleur::LIBRE;
					}
				}
			}
		}

		bool pieceTournable(Piece p) {
			int type = (int)p.getType();
			int rotation = (p.getRota()+1)%4;
			int x = p.getPosX();
			int y = p.getPosY();

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]),16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (x+i-2 >= largeur || x+i-2<2 || y+j-1 >= hauteur || y+j-1 < 0) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					//si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pi�ces d�j� pos�es
					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-2][y+j-1] != (int)Couleur::LIBRE){
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
				int newRota = ((p.getRota()) + 1) % 4;
				p.setRota(newRota);;
			}
		}

		bool pieceDeplacableBas(Piece p) {
			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX();
			int y = p.getPosY()+1;

			EffacerPiece(p);

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]),16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (y+j-1 >= hauteur) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					//si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pi�ces d�j� pos�es
					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-2][y+j-1] != (int)Couleur::LIBRE){
						return false;
					}
				}
			}
			return true;
		}

		bool pieceDeplacableGauche(Piece p) {
			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX()-1;
			int y = p.getPosY();

			EffacerPiece(p);


			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]),16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					//on teste d'abord que la piece ne sortira pas du plateau
					if (x+i-2 < 0) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != (int)Couleur::LIBRE) {
						return false;
					}
				}
			}

			return true;
		}

		bool pieceDeplacableDroite(Piece p) {
			int type = (int)p.getType();
			int rotation = p.getRota();
			int x = p.getPosX()+1;
			int y = p.getPosY();

			EffacerPiece(p);

			//On r�cup�re la matrice associ�e � la pi�ce
			int ReprPiece[4][4];
			memmove(ReprPiece, &(pieces[type][rotation]),16);

			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {

					if (x+i-2 >= largeur) {
						if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
							return false;
						}
					}

					else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 2][y + j - 1] != (int)Couleur::LIBRE) {
						return false;
					}
				}
			}
			return true;
		}

		bool deplacerPieceBas(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableBas(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				int newY = ((p.getPosY()) + 1);
				p.setPosY(newY);
				AfficherPiece(p);

				return false;
			}

			else {
				AfficherPiece(p);

				return true;
			}


		}

		void deplacerPieceGauche(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableGauche(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				int newX = ((p.getPosX()) - 1);
				p.setPosX(newX);
			}

			AfficherPiece(p);
		}

		void deplacerPieceDroite(Piece p) {
			//on verifie d'abord que l'on peut d�placer la pi�ce
			if (pieceDeplacableDroite(p)) {
				//Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
				int newX = ((p.getPosX()) + 1);
				p.setPosX(newX);
			}

			AfficherPiece(p);
		}


		void TomberPiece(Piece p) {
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
					if (plateau[i][j] != (int)Couleur::LIBRE) {
						cases_pleines++;
					}
				}

				//Si elle l'est, on d�place tout ce qui est au dessus vers le bas et on vide la ligne du haut du tableau
				if (cases_pleines == largeur) {
					NbLignesSuppr++;
					for (int k=i; k>0; k--) {
						memmove(&plateau[k], &plateau[k-1], largeur*sizeof(int));
					}

					for (int k=0; k<largeur; k++) {
						plateau[0][k]=(int)Couleur::LIBRE;
					}
				}
			}

			return NbLignesSuppr;
		}


};


#endif
