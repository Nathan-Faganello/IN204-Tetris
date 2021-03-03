#include <cstdlib>
#include <string.h>
#include "piece.h"
#include <time.h>
#include <stdlib.h>
#include "board.h"



Piece Board::getPieceSuivante(){
  return piece_suivante;
}
Piece Board::getPieceCourante(){
  return piece_courante;
}
Board::Board() {
  //Initialisation du plateau de jeu : le plateau est num�rot� de haut en bas (y)(ligne 0 en haut), et de gauche � droite (x)
  for (int i = 0; i < hauteur; i++) {
    for (int j = 0; j < largeur; j++) {
      plateau[i][j] = (int)Couleur::LIBRE;
    }
  }
}

void Board::clearPlateau() {
  //on remet toutes les cases sur LIBRE
  for (int i = 0; i < hauteur; i++) {
    for (int j = 0; j < largeur; j++) {
      plateau[i][j] = (int)Couleur::LIBRE;
    }
  }
}

//tranforme le plateau en un tableau de 'sf::Uint8', représentant la même chose mais étant plus "sûr" à l'envoi

void Board::plateauEnvoi(sf::Uint8 (&envoi)[hauteur][largeur]){
  for(int i=0; i< hauteur; i++){
    for(int j=0; j< largeur; j++){
      envoi[i][j] = (sf::Uint8) plateau[i][j];
    }
  }
}

//passe la pièce suivante comme pièce courante

void Board::setPieceCourante(){
  piece_courante=piece_suivante;
}

//défini une nouvelle pièce suivante, aléatoirement

void Board::setPieceSuivante(){
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

//permet de passer une pièce en nouvelle pièce suivante (utile en ode 2 joueurs pour que l'invité ai la même pièce que l'hôte)

void Board::setPieceSuivante(Piece piece){
  piece_suivante.setPosX(spawn_X);
  piece_suivante.setPosY(spawn_Y);

  piece_suivante.setType(piece.getType());
  piece_suivante.setCouleur(piece.getCouleur());

  piece_suivante.setRota(0);
}

//vérfie que la nouvelle pièce puisse être placé sur le plateau

bool Board::pieceSpawnable(Piece p) {
  int type = (int)p.getType();
  int rotation = p.getRota();
  int x = p.getPosX();
  int y = p.getPosY();

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]), 16*sizeof(int));

  for (int i = 1; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 1][y + j - 2] != (int)Couleur::LIBRE) {

        return false;
      }
    }
  }

  return true;
}

//dispose la pièce la courante sur le plateau

void Board::AfficherPiece() {

  int type = (int)piece_courante.getType();
  int rotation = piece_courante.getRota();
  int x = piece_courante.getPosX();
  int y = piece_courante.getPosY();

  //on associe la bonne couleur aux pi�ces
  if (type == (int)Type::I) {
    piece_courante.setCouleur(Couleur::CYAN);
  }
  else if (type == (int)Type::O) {
    piece_courante.setCouleur(Couleur::JAUNE);
  }
  else if (type == (int)Type::T) {
    piece_courante.setCouleur(Couleur::ORANGE);
  }
  else if (type == (int)Type::L) {
    piece_courante.setCouleur(Couleur::VIOLET);
  }
  else if (type == (int)Type::J) {
    piece_courante.setCouleur(Couleur::BLEU);
  }
  else if (type == (int)Type::Z) {
    piece_courante.setCouleur(Couleur::ROUGE);
  }
  else {
    piece_courante.setCouleur(Couleur::VERT);
  }

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]), 16*sizeof(int));

  //on récupère la couleur de la pièce
  int couleurPiece = (int)piece_courante.getCouleur();

  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      if (ReprPiece[i][j] == 1 || ReprPiece[i][j]==2) {
        plateau[x + i - 1][y + j - 2] = couleurPiece;
      }
    }
  }
}

//enlève la pièce courante du plateau

void Board::EffacerPiece() {
  int type = (int)piece_courante.getType();
  int rotation = piece_courante.getRota();
  int x = piece_courante.getPosX();
  int y = piece_courante.getPosY();

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]), 16*sizeof(int));



  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      if (ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) {
        plateau[x + i - 1][y + j - 2] = (int)Couleur::LIBRE;
      }
    }
  }
}

//vérifie que la pièce puisse effectuer une rotation

bool Board::pieceTournable() {
  int type = (int)piece_courante.getType();
  int rotation = (piece_courante.getRota()+1)%4;
  int x = piece_courante.getPosX();
  int y = piece_courante.getPosY();

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]),16*sizeof(int));

  EffacerPiece();
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {

      //on teste d'abord que la piece ne sortira pas du plateau
      if (x+i-1 >= hauteur || x+i-1<0 || y+j-2 >= largeur || y+j-2 < 0) {
        if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
          return false;
        }
      }

      //si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pi�ces d�j� pos�es
      else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-1][y+j-2] != (int)Couleur::LIBRE){
        return false;
      }
    }
  }
  return true;
}

//effectue la rotation de la pièce

void Board::tournerPiece() {
  //on verifie d'abord que l'on peut tourner la pi�ce
  if (pieceTournable()) {
    //Si oui, on efface la pi�ce dans sa position pr�c�dente et on la tourne
    int newRota = ((piece_courante.getRota()) + 1) % 4;
    piece_courante.setRota(newRota);;
  }
  AfficherPiece();
}

//vérifie que la pièce puisse se déplacer vers le bas

bool Board::pieceDeplacableBas() {
  int type = (int)piece_courante.getType();
  int rotation = piece_courante.getRota();
  int x = piece_courante.getPosX()+1;
  int y = piece_courante.getPosY();

  EffacerPiece();

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]),16*sizeof(int));

  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {

      //on teste d'abord que la piece ne sortira pas du plateau
      if (x+i-1 >= hauteur) {
        if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
          AfficherPiece();
          return false;
        }
      }

      //si elle ne sort pas du plateau, on teste qu'elle n'entre pas en collision avec d'autres pi�ces d�j� pos�es
      else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x+i-1][y+j-2] != (int)Couleur::LIBRE){
        AfficherPiece();
        return false;
      }
    }
  }
  AfficherPiece();
  return true;
}

//vérifie que la pièce puisse se déplacer vers la gauche

bool Board::pieceDeplacableGauche() {
  int type = (int)piece_courante.getType();
  int rotation = piece_courante.getRota();
  int x = piece_courante.getPosX();
  int y = piece_courante.getPosY()-1;

  EffacerPiece();


  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]),16*sizeof(int));

  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {

      //on teste d'abord que la piece ne sortira pas du plateau
      if (y+j-2 < 0) {
        if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
          return false;
        }
      }

      else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 1][y + j - 2] != (int)Couleur::LIBRE) {
        return false;
      }
    }
  }

  return true;
}

//vérifie que la pièce puisse se déplacer vers la gauche

bool Board::pieceDeplacableDroite() {
  int type = (int)piece_courante.getType();
  int rotation = piece_courante.getRota();
  int x = piece_courante.getPosX();
  int y = piece_courante.getPosY()+1;

  EffacerPiece();

  //On r�cup�re la matrice associ�e � la pi�ce
  int ReprPiece[4][4];
  memmove(ReprPiece, &(pieces[type][rotation]),16*sizeof(int));

  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {

      if (y+j-2 >= largeur) {
        if (ReprPiece[i][j]==1 || ReprPiece[i][j]==2){
          return false;
        }
      }

      else if ((ReprPiece[i][j] == 1 || ReprPiece[i][j] == 2) && plateau[x + i - 1][y + j - 2] != (int)Couleur::LIBRE) {

        return false;
      }
    }
  }

  return true;
}

//déplace la pièce vers le bas d'une case

bool Board::deplacerPieceBas() {
  //on verifie d'abord que l'on peut d�placer la pi�ce
  if (pieceDeplacableBas()) {
    //Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
    EffacerPiece();
    int newX = ((piece_courante.getPosX()) + 1);
    piece_courante.setPosX(newX);
    AfficherPiece();

    return false;
  }

  else {

    return true;
  }


}

//déplace la pièce vers la gauche d'une case

void Board::deplacerPieceGauche() {
  //on verifie d'abord que l'on peut d�placer la pi�ce
  if (pieceDeplacableGauche()) {
    //Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
    int newY = ((piece_courante.getPosY()) - 1);
    piece_courante.setPosY(newY);
  }

  AfficherPiece();
}

//déplace la pièce vers la droite d'une case

void Board::deplacerPieceDroite() {
  //on verifie d'abord que l'on peut d�placer la pi�ce
  if (pieceDeplacableDroite()) {
    //Si oui, on efface la pi�ce dans sa position pr�c�dente et on la d�place
    int newY = ((piece_courante.getPosY()) + 1);
    piece_courante.setPosY(newY);
  }

  AfficherPiece();
}


void Board::TomberPiece() {
  while (pieceDeplacableBas() ){
    deplacerPieceBas();
  }
}

int Board::ligne_full() {
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
//transforme un plateau (un tableau) en format 'sf::Uint8' qui a été reçu en un tableau de 'int'

void convertPlateau (sf::Uint8 plateauRecu[hauteur][largeur], int (&plateauInt)[hauteur][largeur]){
  for (int i=0; i<hauteur; i++){
    for(int j=0; i<largeur; j++){
      plateauInt[i][j]=(int)plateauRecu[i][j];
    }
  }
}
