#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include"board.h"
#include"piece.h"
#include <string>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include "game.h"


//calcule le nouveau score après la destruction de nbLignes, selon le niveau.

void calculScore(int &score, int niveau, int nbLignes){
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
  score=score+(niveau+1)*ajout;
}



//fonction d'affichage de l'introduction du jeu, lors de l'ouverture

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

//affiche un message d'attente pour l'invité pendant que l'hôte choisi le niveau.

void afficherAttenteChoixNiveau(sf::RenderWindow &window, sf::Font font){
  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("En attente du choix du niveau par l'hote.");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
  window.draw(message);

}

//message qui est utilisé quand on est en attente d'une réponse de l'adversaire.

void afficherAttenteAdversaire(sf::RenderWindow &window, sf::Font font){
  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("En attente de l'adversaire.");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
  window.draw(message);

}

//affiche pour l'invité le niveau choisi par l'hôte/

void afficherNiveauChoisi(sf::RenderWindow &window, sf::Font font, int niveau){
  sf::Text affNiveau;
  affNiveau.setString("Niveau choisi par l'hote");
  affNiveau.setFont(font);
  affNiveau.setCharacterSize(30);
  affNiveau.setFillColor(sf::Color::White);
  sf::FloatRect textRect = affNiveau.getLocalBounds();
  affNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  affNiveau.setPosition(sf::Vector2f(1080/2.0f,200));

  window.draw(affNiveau);

  std::string textNiveau=std::to_string(niveau);

  sf::Text valNiveau;
  valNiveau.setString(textNiveau);
  valNiveau.setFont(font);
  valNiveau.setCharacterSize(30);
  valNiveau.setFillColor(sf::Color::White);
  textRect = valNiveau.getLocalBounds();
  valNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valNiveau.setPosition(sf::Vector2f(1080/2.0f,350));


  window.draw(valNiveau);
}

//affiche le niveau qui est en train d'être choisi (interface de choix).

void afficherNiveau(sf::RenderWindow &window, sf::Font font, int niveau){
  sf::Text affNiveau;
  affNiveau.setString("Niveau");
  affNiveau.setFont(font);
  affNiveau.setCharacterSize(30);
  affNiveau.setFillColor(sf::Color::White);
  sf::FloatRect textRect = affNiveau.getLocalBounds();
  affNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  affNiveau.setPosition(sf::Vector2f(1080/2.0f,200));

  window.draw(affNiveau);

  std::string textNiveau=std::to_string(niveau);

  sf::Text valNiveau;
  valNiveau.setString(textNiveau);
  valNiveau.setFont(font);
  valNiveau.setCharacterSize(30);
  valNiveau.setFillColor(sf::Color::White);
  textRect = valNiveau.getLocalBounds();
  valNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valNiveau.setPosition(sf::Vector2f(1080/2.0f,350));


  window.draw(valNiveau);
}

//fonction d'affichage de l'encadré du score pendant la partie. (mode 1 joueur)

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

//affiche l'encadré avec la prochaine pièce qui entrera en jeu (mode 1 joueur)

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

//affiche le plateau de jeu avec les pièces déjà posées et la pièce en cours.

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

//interface de pause (disponible qu'en mode 1 joueur)

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

//affichage de la fin de partie (mode 1 joueur)

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

//interface du choix du mode entre 1 ou 2 joueurs

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

//interface de choix entre être l'hôte ou rejoindre une partie.

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

//interface pour l'hôte, affiche son IP et le port local utilisé, à transmettre à l'invité pour qu'il puisse rejoindre.

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

//interface pour écrire lIP de l'hôte pour rejoindre la partie.

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

//interface pour écrire le port utilisé par l'hôte pour pouvoir rejoindre la partie.

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

//Message d'erreur si jamais la connexion échoue

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


//Message d'erreur envoyé si le contenue reçu n'est pas le bon.

void afficherErreurCommunication(sf::RenderWindow &window,sf::Font font){


  sf::Text message;
  message.setFont(font);
  message.setCharacterSize(30);
  message.setFillColor(sf::Color::White);
  message.setString("Communication erronnée entre les deux joueurs, retour au menu");

  sf::FloatRect textRect = message.getLocalBounds();
  message.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  message.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
  window.draw(message);

}

//message s'affichant au début du jeu si jamais il est impossible d'ouvrir un port, pour signaler que le mode 2 joueurs ne sera pas fonctionnel

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

//Affiche le score du joueur pendant la partie (en mode 2 joueurs)

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

//affiche le score adverse pendant la partie (mode 2 joueurs)

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

//Affiche la prochaine pièce à tomber, commune aux deux joueurs (mode 2 joueurs)

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

//affiche le plateau adverse, sera raffraichi à la fin de chaque tour  (mode 2 joueurs)

void afficherPlateauEnnemi(sf::RenderWindow &window, int plateauEnnemi[hauteur][largeur]){


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
      switch ((Couleur)(plateauEnnemi[i][j])){
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

void recepScore(sf::Packet &packet, int &score){
  sf::Uint8 scoreSF;
  packet>>scoreSF;
  score=(int)scoreSF;
}

void envoiScore(sf::Packet &packet, const int score){
  sf::Uint8 scoreSF=(sf::Uint8)score;
  packet<<scoreSF;
}



//Affiche l'entièreté du plateau en un seul appel (mode 2 joueurs)

void afficherJeuDeuxJoueurs(sf::RenderWindow &window, sf::Font font, Board allyBoard, int plateauEnnemi[hauteur][largeur], int allyScore, int ennemyScore){
  afficherPlateau(window, allyBoard);
  afficherScoreAllie(window, font, allyScore);
  afficherScoreEnnemi(window, font, ennemyScore);
  afficherProchainePieceCommune(window, allyBoard, font);
  afficherPlateauEnnemi(window, plateauEnnemi);

}


void afficherMatchNul(sf::RenderWindow &window, sf::Font font, int score){
  sf::Text msgMatchNul;
  msgMatchNul.setString("Match nul!");
  msgMatchNul.setFont(font);
  msgMatchNul.setCharacterSize(40);
  msgMatchNul.setFillColor(sf::Color::White);
  sf::FloatRect textRect = msgMatchNul.getLocalBounds();
  msgMatchNul.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  msgMatchNul.setPosition(sf::Vector2f(1080/2.0f,150));

  window.draw(msgMatchNul);

  sf::Text msgScore;
  msgScore.setString("Score :");
  msgScore.setFont(font);
  msgScore.setCharacterSize(30);
  msgScore.setFillColor(sf::Color::White);
  textRect = msgScore.getLocalBounds();
  msgScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  msgScore.setPosition(sf::Vector2f(1080/2.0f,205));

  window.draw(msgScore);

  std::string textScore=std::to_string(score);

  sf::Text valScore;
  valScore.setString(textScore);
  valScore.setFont(font);
  valScore.setCharacterSize(30);
  valScore.setFillColor(sf::Color::White);
  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(1080/2.0f,350));


  window.draw(valScore);

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


void afficherResultat(sf::RenderWindow &window, sf::Font font, int score, int scoreAdverse, bool win){
  sf::Text msgResultat;
  if (win){
      msgResultat.setString("Victoire");
  }
  else{
      msgResultat.setString("Defaite");
  }

  msgResultat.setFont(font);
  msgResultat.setCharacterSize(40);
  msgResultat.setFillColor(sf::Color::White);
  sf::FloatRect textRect = msgResultat.getLocalBounds();
  msgResultat.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  msgResultat.setPosition(sf::Vector2f(1080/2.0f,250));

  window.draw(msgResultat);

  sf::Text msgScore;
  msgScore.setString("Votre score :");
  msgScore.setFont(font);
  msgScore.setCharacterSize(30);
  msgScore.setFillColor(sf::Color::White);
  textRect = msgScore.getLocalBounds();
  msgScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  msgScore.setPosition(sf::Vector2f(1080/2.0f-50,305));

  window.draw(msgScore);

  std::string textScore=std::to_string(score);

  sf::Text valScore;
  valScore.setString(textScore);
  valScore.setFont(font);
  valScore.setCharacterSize(30);
  valScore.setFillColor(sf::Color::White);
  textRect = valScore.getLocalBounds();
  valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScore.setPosition(sf::Vector2f(1080/2.0f+40,305));


  window.draw(valScore);

  sf::Text msgScoreAdv;
  msgScoreAdv.setString("Score adverse :");
  msgScoreAdv.setFont(font);
  msgScoreAdv.setCharacterSize(30);
  msgScoreAdv.setFillColor(sf::Color::White);
  textRect = msgScoreAdv.getLocalBounds();
  msgScoreAdv.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  msgScoreAdv.setPosition(sf::Vector2f(1080/2.0f-50,350));

  window.draw(msgScoreAdv);

  std::string textScoreAdv=std::to_string(scoreAdverse);

  sf::Text valScoreAdv;
  valScoreAdv.setString(textScoreAdv);
  valScoreAdv.setFont(font);
  valScoreAdv.setCharacterSize(30);
  valScoreAdv.setFillColor(sf::Color::White);
  textRect = valScoreAdv.getLocalBounds();
  valScoreAdv.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  valScoreAdv.setPosition(sf::Vector2f(1080/2.0f+40,350));


  window.draw(valScoreAdv);

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
