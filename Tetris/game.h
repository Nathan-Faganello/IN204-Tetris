#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include"board.h"
#include"piece.h"


int calculScore(int score, int niveau, int nbLignes){
  int ajout;
  switch(nbLignes)
  {
    case 1:
      ajout=40;
      break;
    case 2:
      ajout=100;
      break;
    case 3:
      ajout=300;
      break;
    case 4:
      ajout=1200;
      break;
    default:
      std::cerr<<"Wrong number of lines destructed"<<std::endl;
      ajout=0;
      break;
  }
  return score+(niveau+1)*ajout;
}

void mettrePause(bool etat_pause) {
  etat_pause = true;
}

void mettrePlay(bool etat_pause) {
  etat_pause = false;
}


void finJeu(etat bool fin_jeu) {
  fin_jeu = true;
}


void update(sf::Time deltaT, sf::Time TempsChute, Board plateau, sf::Time dropSpeed) {

  TempsChute = TempsChute - deltaT;

  if (TempsChute<=0) {

    TempsChute = dropSpeed;

    if (plateau.deplacerPieceBas(plateau.piece_courante)) {

      plateau.setPieceCourante();
      plateau.setPieceSuivante();

    }
  }


}


void afficherScore(sf::RenderWindow &window, int score){}

void afficherProchainePiece(sf::RenderWindow &window, Board board){}

void afficherPlateau(sf::RenderWindow &window, Board board){}

void afficherPause(sf::RenderWindow &window){}

#endif // !GAME_H
