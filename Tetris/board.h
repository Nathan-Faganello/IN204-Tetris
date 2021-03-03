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
const int spawn_X = 0;
const int spawn_Y = largeur/2;


class Board {
	private :
		Piece piece_courante;
		Piece piece_suivante;

	public :
		int plateau[hauteur][largeur];

		Piece getPieceSuivante();
		Piece getPieceCourante();
		Board();

		void clearPlateau();

		//tranforme le plateau en un tableau de 'sf::Uint8', représentant la même chose mais étant plus "sûr" à l'envoi

		void plateauEnvoi(sf::Uint8 (&envoi)[hauteur][largeur]);

		//passe la pièce suivante comme pièce courante

		void setPieceCourante();

		//défini une nouvelle pièce suivante, aléatoirement

		void setPieceSuivante();

		//permet de passer une pièce en nouvelle pièce suivante (utile en ode 2 joueurs pour que l'invité ai la même pièce que l'hôte)

		void setPieceSuivante(Piece piece);

		//vérfie que la nouvelle pièce puisse être placé sur le plateau

		bool pieceSpawnable(Piece p);

		//dispose la pièce la courante sur le plateau

		void AfficherPiece();

		//enlève la pièce courante du plateau

		void EffacerPiece();

		//vérifie que la pièce puisse effectuer une rotation

		bool pieceTournable();

		//effectue la rotation de la pièce

		void tournerPiece();

		//vérifie que la pièce puisse se déplacer vers le bas

		bool pieceDeplacableBas();

		//vérifie que la pièce puisse se déplacer vers la gauche

		bool pieceDeplacableGauche();

		//vérifie que la pièce puisse se déplacer vers la gauche

		bool pieceDeplacableDroite() ;

		//déplace la pièce vers le bas d'une case

		bool deplacerPieceBas();

		//déplace la pièce vers la gauche d'une case

		void deplacerPieceGauche();

		//déplace la pièce vers la droite d'une case

		void deplacerPieceDroite();


		void TomberPiece();

		int ligne_full();


};

void convertPlateau (sf::Uint8 plateauRecu[hauteur][largeur], int (&plateauInt)[hauteur][largeur]);



#endif
