#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include"board.h"
#include"piece.h"
#include <string>
#include <SFML/Network/IpAddress.hpp>


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

    if (plateau.deplacerPieceBas()) {

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
        case Couleur::LIBRE:
          colorPiece=sf::Color::Black;
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

void afficherFin(sf::RenderWindow &window, sf::Font font, int score){

  sf::Text line1;
  line1.setString("Partie terminee!");
  line1.setFont(font);
  line1.setCharacterSize(50);
  line1.setFillColor(sf::Color::White);



  sf::FloatRect textRect = line1.getLocalBounds();
  line1.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line1.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-200));
  window.draw(line1);

  sf::Text line2;
  line2.setString("Votre score :");
  line2.setFont(font);
  line2.setCharacterSize(30);
  line2.setFillColor(sf::Color::White);

  textRect = line2.getLocalBounds();
  line2.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line2.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-60));
  window.draw(line2);

  std::string txtValScore=std::to_string(score);

  sf::Text valScore;
  valScore.setString(txtValScore);
  valScore.setFont(font);
  valScore.setCharacterSize(30);
  valScore.setFillColor(sf::Color::White);

  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-20));
  window.draw(valScore);

  sf::Text line5;
  line5.setString("Appuyez sur Entree pour continuer");
  line5.setFont(font);
  line5.setCharacterSize(20);
  line5.setFillColor(sf::Color::White);

  textRect = line5.getLocalBounds();
  line5.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line5.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+100));
  window.draw(line5);
}

void afficherMulti(sf::RenderWindow &window,sf::Font font, int multijoueur){


  sf::Text messageChoix;
  messageChoix.setFont(font);
  messageChoix.setCharacterSize(30);
  messageChoix.setFillColor(sf::Color::White);
  messageChoix.setString("Choix du mode");

  sf::FloatRect textRect = messageChoix.getLocalBounds();
  messageChoix.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageChoix.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-50));
  window.draw(messageChoix);


  sf::Text messageStatutChoix1;
  messageStatutChoix1.setFont(font);
  messageStatutChoix1.setCharacterSize(30);
  messageStatutChoix1.setFillColor(sf::Color::White);
  messageStatutChoix1.setString("Solo");



  textRect = messageStatutChoix1.getLocalBounds();
  messageStatutChoix1.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutChoix1.setPosition(sf::Vector2f(1080/2.0f-90,720/2.0f+50));


  sf::Text messageStatutChoix2;
  messageStatutChoix2.setFont(font);
  messageStatutChoix2.setCharacterSize(30);
  messageStatutChoix2.setFillColor(sf::Color::White);
  messageStatutChoix2.setString("2 joueurs");



  textRect = messageStatutChoix2.getLocalBounds();
  messageStatutChoix2.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutChoix2.setPosition(sf::Vector2f(1080/2.0f+70,720/2.0f+50));


  if(multijoueur==0){
    messageStatutChoix1.setOutlineThickness(1);
    messageStatutChoix1.setOutlineColor(sf::Color::White);
  }
  else{
    messageStatutChoix2.setOutlineThickness(1);
    messageStatutChoix2.setOutlineColor(sf::Color::White);
  }


  window.draw(messageStatutChoix1);
  window.draw(messageStatutChoix2);
}

void afficherHeberge(sf::RenderWindow &window,sf::Font font, int heberge){


  sf::Text messageChoix;
  messageChoix.setFont(font);
  messageChoix.setCharacterSize(30);
  messageChoix.setFillColor(sf::Color::White);
  messageChoix.setString("Heberger ou rejoindre ?");

  sf::FloatRect textRect = messageChoix.getLocalBounds();
  messageChoix.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageChoix.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-50));
  window.draw(messageChoix);


  sf::Text messageStatutChoix1;
  messageStatutChoix1.setFont(font);
  messageStatutChoix1.setCharacterSize(30);
  messageStatutChoix1.setFillColor(sf::Color::White);
  messageStatutChoix1.setString("Heberger");



  textRect = messageStatutChoix1.getLocalBounds();
  messageStatutChoix1.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutChoix1.setPosition(sf::Vector2f(1080/2.0f-90,720/2.0f+50));


  sf::Text messageStatutChoix2;
  messageStatutChoix2.setFont(font);
  messageStatutChoix2.setCharacterSize(30);
  messageStatutChoix2.setFillColor(sf::Color::White);
  messageStatutChoix2.setString("Rejoindre");



  textRect = messageStatutChoix2.getLocalBounds();
  messageStatutChoix2.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageStatutChoix2.setPosition(sf::Vector2f(1080/2.0f+70,720/2.0f+50));


  if(heberge==0){
    messageStatutChoix1.setOutlineThickness(1);
    messageStatutChoix1.setOutlineColor(sf::Color::White);
  }
  else{
    messageStatutChoix2.setOutlineThickness(1);
    messageStatutChoix2.setOutlineColor(sf::Color::White);
  }


  window.draw(messageStatutChoix1);
  window.draw(messageStatutChoix2);
}

void afficherIP(sf::RenderWindow &window,sf::Font font, sf::IpAddress addressIP, unsigned short localPort){


  sf::Text messageIP;
  messageIP.setFont(font);
  messageIP.setCharacterSize(30);
  messageIP.setFillColor(sf::Color::White);
  messageIP.setString("Votre adresse IP est : ");

  sf::FloatRect textRect = messageIP.getLocalBounds();
  messageIP.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageIP.setPosition(sf::Vector2f(1080/2.0f-180,720/2.0f-50));
  window.draw(messageIP);

  std::string IP = addressIP.toString();


  sf::Text messageValIP;
  messageValIP.setFont(font);
  messageValIP.setCharacterSize(30);
  messageValIP.setFillColor(sf::Color::White);
  messageValIP.setString(IP);

  textRect = messageValIP.getLocalBounds();
  messageValIP.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageValIP.setPosition(sf::Vector2f(1080/2.0f+180,720/2.0f-50));
  window.draw(messageValIP);

  sf::Text messagePort;
  messagePort.setFont(font);
  messagePort.setCharacterSize(30);
  messagePort.setFillColor(sf::Color::White);
  messagePort.setString("Votre port est : ");

  textRect = messagePort.getLocalBounds();
  messagePort.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messagePort.setPosition(sf::Vector2f(1080/2.0f-80,720/2.0f+50));
  window.draw(messagePort);

  std::string Port=std::to_string(localPort);

  sf::Text messageValPort;
  messageValPort.setFont(font);
  messageValPort.setCharacterSize(30);
  messageValPort.setFillColor(sf::Color::White);
  messageValPort.setString(Port);

  textRect = messageValPort.getLocalBounds();
  messageValPort.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageValPort.setPosition(sf::Vector2f(1080/2.0f+120,720/2.0f+50));
  window.draw(messageValPort);

  sf::Text line5;
  line5.setString("En attente du  deuxieme joueur");
  line5.setFont(font);
  line5.setCharacterSize(20);
  line5.setFillColor(sf::Color::White);

  textRect = line5.getLocalBounds();
  line5.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line5.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+180));
  window.draw(line5);

}

void afficherEntreeIP(sf::RenderWindow &window,sf::Font font, std::string entreeIP){


  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("Entrez l'adresse IP de l'hote : ");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-50));
  window.draw(message);



  sf::Text messageIP;
  messageIP.setFont(font);
  messageIP.setCharacterSize(30);
  messageIP.setFillColor(sf::Color::White);
  messageIP.setString(entreeIP);

  textRect = messageIP.getLocalBounds();
  messageIP.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messageIP.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+50));
  window.draw(messageIP);

  sf::Text line5;
  line5.setString("Appuyez sur Entree pour continuer");
  line5.setFont(font);
  line5.setCharacterSize(20);
  line5.setFillColor(sf::Color::White);

  textRect = line5.getLocalBounds();
  line5.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line5.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+180));
  window.draw(line5);

}


void afficherEntreePort(sf::RenderWindow &window,sf::Font font, std::string portExterneTxt){


  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("Entrez le port de l'hote : ");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f-50));
  window.draw(message);


  sf::Text messagePort;
  messagePort.setFont(font);
  messagePort.setCharacterSize(30);
  messagePort.setFillColor(sf::Color::White);
  messagePort.setString(portExterneTxt);

  textRect = messagePort.getLocalBounds();
  messagePort.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  messagePort.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+50));
  window.draw(messagePort);

  sf::Text line5;
  line5.setString("Appuyez sur Entree pour continuer");
  line5.setFont(font);
  line5.setCharacterSize(20);
  line5.setFillColor(sf::Color::White);

  textRect = line5.getLocalBounds();
  line5.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  line5.setPosition(sf::Vector2f(1080/2.0f,720/2.0f+180));
  window.draw(line5);

}


void afficherErreurConnection(sf::RenderWindow &window,sf::Font font){


  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("Impossible d'etablir la connection entre les joueurs.");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
  window.draw(message);

}


void afficherErreurReseau(sf::RenderWindow &window,sf::Font font){


  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("Erreur lors de l'ouverture d'un port, mode multijoueur non fonctionnel.");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
  window.draw(message);

}



void afficherScoreAllie(sf::RenderWindow &window, sf::Font font, int allyScore){

  sf::Vertex cadreScore[] =
  {
      sf::Vertex(sf::Vector2f(500, 400)),
      sf::Vertex(sf::Vector2f(500, 480)),
      sf::Vertex(sf::Vector2f(700, 480)),
      sf::Vertex(sf::Vector2f(700, 400)),
      sf::Vertex(sf::Vector2f(500, 400))
  };

  window.draw(cadreScore, 5, sf::LinesStrip);



  sf::Text txtScore;
  txtScore.setString("Score :");
  txtScore.setFont(font);
  txtScore.setCharacterSize(20);
  txtScore.setFillColor(sf::Color::White);

  sf::FloatRect textRect = txtScore.getLocalBounds();
  txtScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  txtScore.setPosition(sf::Vector2f(600,415));
  window.draw(txtScore);


  std::string txtValScore=std::to_string(allyScore);

  sf::Text valScore;
  valScore.setString(txtValScore);
  valScore.setFont(font);
  valScore.setCharacterSize(20);
  valScore.setFillColor(sf::Color::White);

  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(600,455));
  window.draw(valScore);



}

void afficherScoreEnnemi(sf::RenderWindow &window, sf::Font font, int ennemyScore){

  sf::Vertex cadreScore[] =
  {
      sf::Vertex(sf::Vector2f(800, 550)),
      sf::Vertex(sf::Vector2f(800, 650)),
      sf::Vertex(sf::Vector2f(1000, 650)),
      sf::Vertex(sf::Vector2f(1000, 550)),
      sf::Vertex(sf::Vector2f(800, 550))
  };

  window.draw(cadreScore, 5, sf::LinesStrip);



  sf::Text txtScore;
  txtScore.setString("Score adverse:");
  txtScore.setFont(font);
  txtScore.setCharacterSize(20);
  txtScore.setFillColor(sf::Color::White);

  sf::FloatRect textRect = txtScore.getLocalBounds();
  txtScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  txtScore.setPosition(sf::Vector2f(900,570));
  window.draw(txtScore);


  std::string txtValScore=std::to_string(ennemyScore);

  sf::Text valScore;
  valScore.setString(txtValScore);
  valScore.setFont(font);
  valScore.setCharacterSize(20);
  valScore.setFillColor(sf::Color::White);

  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(900,620));
  window.draw(valScore);


}


void afficherProchainePieceCommune(sf::RenderWindow &window, Board board, sf::Font font){


  sf::Vertex cadreNouvPiece[] =
  {
      sf::Vertex(sf::Vector2f(500, 100)),
      sf::Vertex(sf::Vector2f(500, 300)),
      sf::Vertex(sf::Vector2f(700, 300)),
      sf::Vertex(sf::Vector2f(700, 100)),
      sf::Vertex(sf::Vector2f(500, 100))
  };

  window.draw(cadreNouvPiece, 5, sf::LinesStrip);


  sf::Text nouvellePiece;
  nouvellePiece.setString("Piece suivante :");
  nouvellePiece.setFont(font);
  nouvellePiece.setCharacterSize(20);
  nouvellePiece.setFillColor(sf::Color::White);

  sf::FloatRect nouvPieceRect = nouvellePiece.getLocalBounds();
  nouvellePiece.setOrigin(nouvPieceRect.left + nouvPieceRect.width/2.0f, nouvPieceRect.top  + nouvPieceRect.height/2.0f);
  nouvellePiece.setPosition(sf::Vector2f(600,120));
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
            rectangle1.setPosition(sf::Vector2f(541+j*30, 151+i*30));
            numRectangle++;
            break;
          case 2:
            rectangle2.setPosition(sf::Vector2f(541+j*30, 151+i*30));
            numRectangle++;
            break;
          case 3:
            rectangle3.setPosition(sf::Vector2f(541+j*30, 151+i*30));
            numRectangle++;
            break;
          case 4:
            rectangle4.setPosition(sf::Vector2f(541+j*30, 151+i*30));
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

void afficherPlateauEnnemi(sf::RenderWindow &window, Board ennemyBoard){


  sf::Vertex cadreJeu[] =
  {
      sf::Vertex(sf::Vector2f(800, 50)),
      sf::Vertex(sf::Vector2f(800, 490)),
      sf::Vertex(sf::Vector2f(1000, 490)),
      sf::Vertex(sf::Vector2f(1000, 50)),
      sf::Vertex(sf::Vector2f(800, 50))
  };

  window.draw(cadreJeu, 5, sf::LinesStrip);


  sf::RectangleShape rectangle(sf::Vector2f(18, 18));
  sf::Color colorPiece;

  for(int i=0; i<hauteur; i++){
    for(int j=0; j<largeur; j++){
      switch ((Couleur)(ennemyBoard.plateau[i][j])){
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
        case Couleur::LIBRE:
          colorPiece=sf::Color::Black;
          break;
      }

    rectangle.setFillColor(colorPiece);

    rectangle.setPosition(sf::Vector2f(801+j*20, 51+i*20));

    window.draw(rectangle);

    }
  }
}



void afficherJeuDeuxJoueurs(sf::RenderWindow &window, sf::Font font, Board allyBoard, Board ennemyBoard, int allyScore, int ennemyScore){
  afficherPlateau(window, allyBoard);
  afficherScoreAllie(window, font, allyScore);
  afficherScoreEnnemi(window, font, ennemyScore);
  afficherProchainePieceCommune(window, allyBoard, font);
  afficherPlateauEnnemi(window, ennemyBoard);

}



#endif // !GAME_H
