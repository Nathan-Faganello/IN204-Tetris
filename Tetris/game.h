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


void finJeu(bool etat_fin_jeu) {
  etat_fin_jeu = true;
}


void update(sf::Time deltaT, sf::Time &TempsChute, Board &plateau, sf::Time dropSpeed) {

  TempsChute = TempsChute - deltaT;

  if (TempsChute<=sf::Time::Zero) {

    TempsChute = dropSpeed;

    if (plateau.deplacerPieceBas(plateau.getPieceCourante())) {

      plateau.setPieceCourante();
      plateau.setPieceSuivante();

    }
  }


}





void afficherIntro(sf::RenderWindow &window, sf::Font font){

  sf::Text line1;
  line1.setString("Bienvenue dans notre Tetris");
  line1.setFont(font);
  line1.setCharacterSize(50);
  line1.setFillColor(sf::Color::White);



  sf::FloatRect textRect = line1.getLocalBounds();
  line1.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line1.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-200));
  window.draw(line1);

  sf::Text line2;
  line2.setString("Pour parcourir les differents menus, utilisez les fleches directionnelles.");
  line2.setFont(font);
  line2.setCharacterSize(30);
  line2.setFillColor(sf::Color::White);

  textRect = line2.getLocalBounds();
  line2.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line2.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-60));
  window.draw(line2);


  sf::Text line3;
  line3.setString("Appuyez sur Entree pour valider votre choix.");
  line3.setFont(font);
  line3.setCharacterSize(30);
  line3.setFillColor(sf::Color::White);

  textRect = line3.getLocalBounds();
  line3.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line3.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-20));
  window.draw(line3);

  sf::Text line4;
  line4.setString("Appuyez sur Echap pour revenir en arriere ou mettre le jeu en pause.");
  line4.setFont(font);
  line4.setCharacterSize(30);
  line4.setFillColor(sf::Color::White);

  textRect = line4.getLocalBounds();
  line4.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line4.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+20));
  window.draw(line4);

  sf::Text line5;
  line5.setString("Appuyez sur Entree pour continuer");
  line5.setFont(font);
  line5.setCharacterSize(30);
  line5.setFillColor(sf::Color::White);

  textRect = line5.getLocalBounds();
  line5.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line5.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+80));
  window.draw(line5);

}

void afficherScore(sf::RenderWindow &window, int score, sf::Font font){


  sf::Vertex cadreScore[] =
  {
      sf::Vertex(sf::Vector2f(500, 400)),
      sf::Vertex(sf::Vector2f(500, 500)),
      sf::Vertex(sf::Vector2f(800, 500)),
      sf::Vertex(sf::Vector2f(800, 400)),
      sf::Vertex(sf::Vector2f(500, 400))
  };

  window.draw(cadreScore, 5, sf::LinesStrip);



  sf::Text txtScore;
  txtScore.setString("Score :");
  txtScore.setFont(font);
  txtScore.setCharacterSize(30);
  txtScore.setFillColor(sf::Color::White);

  sf::FloatRect textRect = txtScore.getLocalBounds();
  txtScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  txtScore.setPosition(sf::Vector2f(650,420));
  window.draw(txtScore);


  std::string txtValScore=std::to_string(score);

  sf::Text valScore;
  valScore.setString(txtValScore);
  valScore.setFont(font);
  valScore.setCharacterSize(30);
  valScore.setFillColor(sf::Color::White);

  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(650,470));
  window.draw(valScore);

}

void afficherProchainePiece(sf::RenderWindow &window, Board board, sf::Font font){


  sf::Vertex cadreNouvPiece[] =
  {
      sf::Vertex(sf::Vector2f(500, 100)),
      sf::Vertex(sf::Vector2f(500, 300)),
      sf::Vertex(sf::Vector2f(800, 300)),
      sf::Vertex(sf::Vector2f(800, 100)),
      sf::Vertex(sf::Vector2f(500, 100))
  };

  window.draw(cadreNouvPiece, 5, sf::LinesStrip);


  sf::Text nouvellePiece;
  nouvellePiece.setString("Piece suivante :");
  nouvellePiece.setFont(font);
  nouvellePiece.setCharacterSize(30);
  nouvellePiece.setFillColor(sf::Color::White);

  sf::FloatRect nouvPieceRect = nouvellePiece.getLocalBounds();
  nouvellePiece.setOrigin(nouvPieceRect.left + nouvPieceRect.width/2.0f, nouvPieceRect.top  + nouvPieceRect.height/2.0f);
  nouvellePiece.setPosition(sf::Vector2f(650,120));
  window.draw(nouvellePiece);



  sf::RectangleShape rectangle1(sf::Vector2f(28, 28));
  sf::RectangleShape rectangle2(sf::Vector2f(28, 28));
  sf::RectangleShape rectangle3(sf::Vector2f(28, 28));
  sf::RectangleShape rectangle4(sf::Vector2f(28, 28));

  sf::Color colorPiece;

  Piece pieceSuivante=board.getPieceSuivante();


  switch(pieceSuivante.getCouleur()){
    case Couleur::CYAN:
      colorPiece=sf::Color::Cyan;
      break;
    case Couleur::JAUNE:
      colorPiece=sf::Color::Yellow;
      break;
    case Couleur::ORANGE:
      colorPiece.r=255;
      colorPiece.g=127;
      colorPiece.b=80;
      break;
    case Couleur::VIOLET:
      colorPiece=sf::Color::Magenta;
      break;
    case Couleur::BLEU:
      colorPiece=sf::Color::Blue;
      break;
    case Couleur::ROUGE:
      colorPiece=sf::Color::Red;
      break;
    case Couleur::VERT:
      colorPiece=sf::Color::Green;
      break;
  }

  int numRectangle=1;

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      if (pieces[(int)pieceSuivante.getType()][0][i][j]!=0){
        switch(numRectangle){
          case 1:
            rectangle1.setPosition(sf::Vector2f(591+j*30, 151+i*30));
            numRectangle++;
            break;
          case 2:
            rectangle2.setPosition(sf::Vector2f(591+j*30, 151+i*30));
            numRectangle++;
            break;
          case 3:
            rectangle3.setPosition(sf::Vector2f(591+j*30, 151+i*30));
            numRectangle++;
            break;
          case 4:
            rectangle4.setPosition(sf::Vector2f(591+j*30, 151+i*30));
            numRectangle++;
            break;
        }
      }
    }
  }


  rectangle1.setFillColor(colorPiece);

  rectangle2.setFillColor(colorPiece);

  rectangle3.setFillColor(colorPiece);

  rectangle4.setFillColor(colorPiece);

  window.draw(rectangle1);
  window.draw(rectangle2);
  window.draw(rectangle3);
  window.draw(rectangle4);

}

void afficherPlateau(sf::RenderWindow &window, Board board){

  sf::Vertex cadreJeu[] =
  {
      sf::Vertex(sf::Vector2f(100, 30)),
      sf::Vertex(sf::Vector2f(100, 690)),
      sf::Vertex(sf::Vector2f(400, 690)),
      sf::Vertex(sf::Vector2f(400, 30)),
      sf::Vertex(sf::Vector2f(100, 30))
  };

  window.draw(cadreJeu, 5, sf::LinesStrip);


  sf::RectangleShape rectangle(sf::Vector2f(28, 28));
  sf::Color colorPiece;

  for(int i=0; i<hauteur; i++){
    for(int j=0; j<largeur; j++){
      switch ((Couleur)(board.plateau[i][j])){
        case Couleur::CYAN:
          colorPiece=sf::Color::Cyan;
          break;
        case Couleur::JAUNE:
          colorPiece=sf::Color::Yellow;
          break;
        case Couleur::ORANGE:
          colorPiece.r=255;
          colorPiece.g=127;
          colorPiece.b=80;
          break;
        case Couleur::VIOLET:
          colorPiece=sf::Color::Magenta;
          break;
        case Couleur::BLEU:
          colorPiece=sf::Color::Blue;
          break;
        case Couleur::ROUGE:
          colorPiece=sf::Color::Red;
          break;
        case Couleur::VERT:
          colorPiece=sf::Color::Green;
          break;
      }

    rectangle.setFillColor(colorPiece);

    rectangle.setPosition(sf::Vector2f(101+j*30, 31+i*30));

    window.draw(rectangle);

    }
  }
}

void afficherPause(sf::RenderWindow &window,sf::Font font, int statutPause){


  sf::Text messagePause;
  messagePause.setFont(font);
  messagePause.setCharacterSize(30);
  messagePause.setFillColor(sf::Color::White);
  messagePause.setString("Jeu en pause");

  sf::FloatRect textRect = messagePause.getLocalBounds();
  messagePause.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messagePause.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-50));
  window.draw(messagePause);


  sf::Text messageStatutPause1;
  messageStatutPause1.setFont(font);
  messageStatutPause1.setCharacterSize(30);
  messageStatutPause1.setFillColor(sf::Color::White);
  messageStatutPause1.setString("Reprendre");



  textRect = messageStatutPause1.getLocalBounds();
  messageStatutPause1.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutPause1.setPosition(sf::Vector2f(1080/2.0f-130,720/2.0f+50));


  sf::Text messageStatutPause2;
  messageStatutPause2.setFont(font);
  messageStatutPause2.setCharacterSize(30);
  messageStatutPause2.setFillColor(sf::Color::White);
  messageStatutPause2.setString("Quitter la partie");



  textRect = messageStatutPause2.getLocalBounds();
  messageStatutPause2.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutPause2.setPosition(sf::Vector2f(1080/2.0f+70,720/2.0f+50));


  if(statutPause==0){
    messageStatutPause1.setOutlineThickness(1);
    messageStatutPause1.setOutlineColor(sf::Color::White);
  }
  else{
    messageStatutPause2.setOutlineThickness(1);
    messageStatutPause2.setOutlineColor(sf::Color::White);
  }


  window.draw(messageStatutPause1);
  window.draw(messageStatutPause2);
}

#endif // !GAME_H
