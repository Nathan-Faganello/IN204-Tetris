#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "piece.h"
#include "board.h"
#include "game.h"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>



int main()
{
    srand (time(NULL));
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Tetris Faganello Laforge");
		window.setFramerateLimit(30);
    sf::Font font;
    if (!font.loadFromFile("./External/Font/arial.ttf"))

    {
      std::cout << "Error loading font\n" ;
    }


		int niveau=0;
		int statut=0;
    int score=0;
    int scoreAdverse=0;
    int NbLignes=0;
    int statutPause=0;
    int multijoueur=0;
    int heberge=0;
    std::string IPHoteTxt;
    sf::IpAddress IPHote;
    sf::IpAddress IPInvite;
    std::string portExterneTxt;



    sf::Time dropSpeed;
    sf::Time tempsChute;
    sf::Time deltaT;

    sf::UdpSocket socket;

    // lie la socket à un port
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
      window.clear();
      afficherErreurReseau(window, font);
      window.display();
      sf::Time t1 = sf::seconds(5);
      sf::sleep(t1);
    }
    unsigned short localPort=socket.getLocalPort();
    unsigned short portExterne;


    Board board;

    board.setPieceSuivante();

    sf::Uint8 plateauPacket[hauteur][largeur];
    int plateauAdverse[hauteur][largeur];
    for (int i = 0; i < hauteur; i++) {
      for (int j = 0; j < largeur; j++) {
        plateauAdverse[i][j] = (int)Couleur::LIBRE;
      }
    }


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (statut==0){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                  statut--;
                }
              }
            }
            else if (statut==-1){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left){
                  multijoueur=(multijoueur+1)%2;
                }
                else if(event.key.code == sf::Keyboard::Enter){
                  if (multijoueur==0){
                    statut=1;
                    niveau=0;
                  }
                  else{
                    statut=200;
                  }
                }
              }
            }
						else if (statut==1){
							if (event.type == sf::Event::KeyPressed){
								if (event.key.code == sf::Keyboard::Right){
									niveau=(niveau+1)%16;
								}
								else if (event.key.code == sf::Keyboard::Left){
									if (niveau==0){niveau=16;}
									niveau=niveau-1;
								}
                else if (event.key.code == sf::Keyboard::Enter){
                  dropSpeed=sf::seconds(1.5)-(sf::seconds(niveau*1.499/15));
                  tempsChute=dropSpeed;
                  statut++;
                }
                else if(event.key.code == sf::Keyboard::Escape){
                  statut=-1;
                }
							}
						}
            else if(statut==3){
              if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                  statut=100;
                  statutPause=0;
                }

              }
            }
            else if(statut==100){
              if (event.type == sf::Event::KeyPressed){
								if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left){
                  statutPause=(statutPause+1)%2;
                }
                else if(event.key.code == sf::Keyboard::Enter){
                  if (statutPause==0){
                    statut=101;
                  }
                  else{
                    board.clearPlateau();
                    statut=1;
                    score=0;
                  }
                }
              }
            }
            else if(statut==4){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                  statut=1;
                  board.clearPlateau();
                  score=0;
                }
              }
            }
            else if(statut==200){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left){
                  heberge=(heberge+1)%2;
                }
                else if(event.key.code == sf::Keyboard::Enter){
                  if (heberge==0){
                    statut=201;
                  }
                  else{
                    window.pollEvent(event);
                    statut=202;
                  }
                }
                else if(event.key.code==sf::Keyboard::Escape){
                  statut=-1;
                }
              }
            }
            else if(statut==201){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                  statut=200;
                }
              }
            }
            else if(statut==202){
              if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128&&event.text.unicode!=13&&event.text.unicode!=8&&event.text.unicode!=27){
                  IPHoteTxt.push_back(static_cast<char>(event.text.unicode));
                }
                else if(event.text.unicode==8){
                  IPHoteTxt.pop_back();
                }
                else if(event.text.unicode==13){

                  statut=203;
                }
                else if(event.text.unicode==27){
                  IPHoteTxt.clear();
                  statut=200;
                }
              }
            }
            else if(statut==203){
              if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128&&event.text.unicode!=13&&event.text.unicode!=8&&event.text.unicode!=27){
                  portExterneTxt.push_back(static_cast<char>(event.text.unicode));
                }
                else if(event.text.unicode==8){
                  portExterneTxt.pop_back();
                }
                else if(event.text.unicode==13){
                  char buffer[]="OK";
                  IPHote=sf::IpAddress(IPHoteTxt);
                  portExterne=(unsigned short) std::stoi(portExterneTxt);
                  if (socket.send(buffer, sizeof(buffer), IPHote, portExterne)!=sf::Socket::Done){
                    statut=204;
                  }
                  else{
                    niveau=0;
                    statut=400;
                  }
                }
                else if(event.text.unicode==27){
                  portExterneTxt.clear();
                  statut=202;
                }
              }
            }
            else if(statut==204){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                  statut=200;
                }
              }
            }
            else if (statut==300){
              if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Right){
                  niveau=(niveau+1)%16;
                }
                else if (event.key.code == sf::Keyboard::Left){
                  if (niveau==0){niveau=16;}
                  niveau=niveau-1;
                }
                else if (event.key.code == sf::Keyboard::Enter){
                  dropSpeed=sf::seconds(1.5)-(sf::seconds(niveau*1.499/15));
                  tempsChute=dropSpeed;
                  sf::Packet packNiv;
                  sf::Uint8 nivConvert = (sf::Uint8) niveau;
                  packNiv<<nivConvert;
                  socket.send(packNiv, IPInvite, portExterne);
                  packNiv.clear();
                  statut++;
                }
                else if(event.key.code == sf::Keyboard::Escape){
                  statut=200;
                }
              }
            }
          }







				if (statut==0){ //affichage texte bienvenue
          window.clear();
          afficherIntro(window, font);

					window.display();
				}


        else if(statut==-1){
          window.clear();
          afficherMulti(window, font, multijoueur);
          window.display();
        }

				else if(statut==1){  //choix du niveau
					window.clear();
          afficherNiveau(window, font, niveau);
					window.display();
			}

      else if(statut==2){ //affichage du jeu pendant 3 secondes lors de l'entrée dans celui ci (avant le début effectif)
        window.clear();



        afficherPlateau(window,board);
        afficherScore(window, score, font);
        afficherProchainePiece(window, board, font);
        window.display();

        board.setPieceCourante();
        board.setPieceSuivante();
        board.AfficherPiece();
        sf::Time t1 = sf::seconds(1);
        sf::sleep(t1);
        statut++;

      }

      else if(statut==3){



        tempsChute=dropSpeed;

        sf::Clock clock;
        sf::Clock timerUp;
        sf::Clock timerDown;
        bool finChute;
        sf::Time coolDown=sf::seconds(0.35f);
        bool firstTime=true;
        do {
          window.clear();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            board.deplacerPieceDroite();

          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            board.deplacerPieceGauche();

          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(firstTime){
              board.tournerPiece();
              firstTime=false;
            }
            else{
              if(timerUp.getElapsedTime()>=coolDown){
                board.tournerPiece();
                timerUp.restart();
              }
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(timerUp.getElapsedTime()>=sf::seconds(0.2)){
              finChute=board.deplacerPieceBas();
              timerDown.restart();
              window.clear();
              afficherPlateau(window,board);
              afficherScore(window, score, font);
              afficherProchainePiece(window, board, font);

              window.display();
              if (finChute){
                break;
              }

            }
          }


          sf::Time deltaT = clock.getElapsedTime();
          tempsChute-=deltaT;
          clock.restart();

          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);

          window.display();


        } while(tempsChute>sf::Time::Zero);

        bool changement=board.deplacerPieceBas();


        if(changement){
          NbLignes=board.ligne_full();
          if(NbLignes!=0){
            calculScore(score, niveau, NbLignes);
            window.clear();
            afficherPlateau(window,board);
            afficherScore(window, score, font);
            afficherProchainePiece(window, board, font);
            window.display();
          }
          board.setPieceCourante();
          board.setPieceSuivante();
          if(!board.pieceSpawnable(board.getPieceCourante())){
            statut=4;
          }
          else{
            board.AfficherPiece();
            sf::Time t1 = sf::seconds(0.4);
            sf::sleep(t1);
          }
        }
        else {
          window.clear();
          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);
          window.display();
        }

      }
      else if(statut==4){
        window.clear();
        afficherFin(window, font, score);
        window.display();
      }
      else if(statut==100){
        window.clear();
        afficherPause(window, font, statutPause);
        window.display();

      }

      else if(statut==101){//petit temps de pause avant reprise du jeu après la pause où on affiche l'état du jeu avant reprise
        window.clear();



        afficherPlateau(window,board);
        afficherScore(window, score, font);
        afficherProchainePiece(window, board, font);
        window.display();



        sf::Time t1 = sf::seconds(2);
        sf::sleep(t1);
        statut=3;
      }

      else if(statut==200){

        window.clear();
        afficherHeberge(window, font, heberge);
        window.display();
      }

      else if(statut==201){

        char buffer[50];

        std::size_t received;



        window.clear();
        sf::IpAddress addressIP = sf::IpAddress::getPublicAddress();
        afficherIP(window, font, addressIP, localPort);
        window.display();
        socket.receive(buffer, sizeof(buffer), received, IPInvite, portExterne);
        std::string txtTest(buffer, received);
        char OK[]="OK";
        if(strcmp(txtTest.c_str(), OK)!=0){
          statut=204;
        }
        else{
          statut=300;
          niveau=0;
        }

      }

      else if(statut==202){
        window.clear();
        afficherEntreeIP(window, font, IPHoteTxt);
        window.display();
      }

      else if(statut==203){
        window.clear();
        afficherEntreePort(window, font, portExterneTxt);
        window.display();
      }

      else if(statut==204){
        window.clear();
        afficherErreurConnection(window, font);
        window.display();
      }

      else if(statut==300){

        window.clear();
        afficherNiveau(window, font, niveau);
        window.display();

      }

      else if (statut == 301){

        window.clear();
        afficherAttenteAdversaire(window, font);
        window.display();
        sf::Packet packet;
        std::string ready;
        socket.receive(packet, IPInvite, portExterne);
        packet>>ready;
        if (ready.compare("ready")==0){
          sf::Packet nextPiece;
          nextPiece<<board.getPieceSuivante();
          socket.send(nextPiece, IPInvite, portExterne);
          nextPiece.clear();
          statut++;
        }
      }

      else if(statut == 302){
        window.clear();
        afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
        window.display();

        board.setPieceCourante();
        board.setPieceSuivante();
        board.AfficherPiece();
        sf::Time t1 = sf::seconds(1);
        sf::sleep(t1);
        sf::Packet nextPiece;
        nextPiece<<board.getPieceSuivante();
        socket.send(nextPiece, IPInvite, portExterne);
        statut++;

      }

      else if (statut == 303){

        tempsChute=dropSpeed;

        sf::Clock clock;
        sf::Clock timerUp;
        sf::Clock timerDown;
        bool finChute;
        sf::Time coolDown=sf::seconds(0.35f);
        bool firstTime=true;
        do {
          window.clear();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            board.deplacerPieceDroite();

          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            board.deplacerPieceGauche();

          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(firstTime){
              board.tournerPiece();
              firstTime=false;
            }
            else{
              if(timerUp.getElapsedTime()>=coolDown){
                board.tournerPiece();
                timerUp.restart();
              }
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(timerUp.getElapsedTime()>=sf::seconds(0.2)){
              finChute=board.deplacerPieceBas();
              timerDown.restart();
              window.clear();
              afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
              window.display();


              if (finChute){
                break;
              }

            }
          }


          sf::Time deltaT = clock.getElapsedTime();
          tempsChute-=deltaT;
          clock.restart();

          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);

          window.display();


        } while(tempsChute>sf::Time::Zero);

        bool changement=board.deplacerPieceBas();


        if(changement){
          NbLignes=board.ligne_full();
          if(NbLignes!=0){
            calculScore(score, niveau, NbLignes);
            window.clear();
            afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
            window.display();
          }
          board.setPieceCourante();
          board.setPieceSuivante();


          sf::Packet packetPieceSuiv;
          packetPieceSuiv<<board.getPieceSuivante();
          socket.send(packetPieceSuiv, IPInvite, portExterne);
          packetPieceSuiv.clear();

          int scoreTemp;
          sf::Packet packetScore;
          socket.receive(packetScore, IPInvite, portExterne);
          recepScore(packetScore, scoreTemp);
          packetScore.clear();
          if (scoreTemp==-1){
            statut++;
          }
          else{
            scoreAdverse=scoreTemp;
          }

          if(!board.pieceSpawnable(board.getPieceCourante())){
            envoiScore(packetScore, -1);
            socket.send(packetScore, IPInvite, portExterne);
            packetScore.clear();
            statut = 305;
          }
          else{
            envoiScore(packetScore, score);
            socket.send(packetScore, IPInvite, portExterne);
            packetScore.clear();
          }

          std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
          std::size_t received;
          socket.receive(plateauPacket, tailleEnvoi, received, IPInvite, portExterne);
          if (received==tailleEnvoi){
            convertPlateau(plateauPacket, plateauAdverse);
          }
          board.plateauEnvoi(plateauPacket);
          socket.send(plateauPacket, tailleEnvoi, IPInvite, portExterne);





          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
          board.AfficherPiece();
          sf::Time t1 = sf::seconds(0.4);
          sf::sleep(t1);
        }
        else {
          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
        }


      }

      else if (statut == 304){

        tempsChute=dropSpeed;

        sf::Clock clock;
        sf::Clock timerUp;
        sf::Clock timerDown;
        bool finChute;
        sf::Time coolDown=sf::seconds(0.35f);
        bool firstTime=true;
        do {
          window.clear();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            board.deplacerPieceDroite();

          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            board.deplacerPieceGauche();

          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(firstTime){
              board.tournerPiece();
              firstTime=false;
            }
            else{
              if(timerUp.getElapsedTime()>=coolDown){
                board.tournerPiece();
                timerUp.restart();
              }
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(timerUp.getElapsedTime()>=sf::seconds(0.2)){
              finChute=board.deplacerPieceBas();
              timerDown.restart();
              window.clear();
              afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
              window.display();


              if (finChute){
                break;
              }

            }
          }


          sf::Time deltaT = clock.getElapsedTime();
          tempsChute-=deltaT;
          clock.restart();

          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);

          window.display();


        } while(tempsChute>sf::Time::Zero);

        bool changement=board.deplacerPieceBas();


        if(changement){
          NbLignes=board.ligne_full();
          if(NbLignes!=0){
            calculScore(score, niveau, NbLignes);
            window.clear();
            afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
            window.display();
          }
          board.setPieceCourante();
          board.setPieceSuivante();



          sf::Packet packetScore;

          if(!board.pieceSpawnable(board.getPieceCourante())){
            envoiScore(packetScore, -1);
            socket.send(packetScore, IPInvite, portExterne);
            packetScore.clear();
            statut = 500;
          }
          else{
            envoiScore(packetScore, score);
            socket.send(packetScore, IPInvite, portExterne);
            packetScore.clear();
          }

          std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
          board.plateauEnvoi(plateauPacket);
          socket.send(plateauPacket, tailleEnvoi, IPInvite, portExterne);





          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
          board.AfficherPiece();
          sf::Time t1 = sf::seconds(0.4);
          sf::sleep(t1);
        }
        else {
          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
        }


      }

      else if (statut == 305){

        int scoreTemp;
        sf::Packet packetScore;
        socket.receive(packetScore, IPInvite, portExterne);
        recepScore(packetScore, scoreTemp);
        packetScore.clear();
        if (scoreTemp==-1){
          statut=500;
        }
        else{
          scoreAdverse=scoreTemp;
        }


        std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
        std::size_t received;
        socket.receive(plateauPacket, tailleEnvoi, received, IPInvite, portExterne);
        if (received==tailleEnvoi){
          convertPlateau(plateauPacket, plateauAdverse);
        }




        window.clear();
        afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
        window.display();

      }




      else if(statut==400){
        window.clear();
        afficherAttenteChoixNiveau(window, font);
        window.display();
        sf::Packet nivRecu;
        socket.receive(nivRecu, IPHote, portExterne);
        sf::Uint8 valNiv;
        nivRecu>>valNiv;
        niveau=(int)valNiv;
        dropSpeed=sf::seconds(1.5)-(sf::seconds(niveau*1.499/15));
        tempsChute=dropSpeed;
        statut++;

      }

      else if (statut == 401){
        window.clear();
        afficherNiveauChoisi(window, font, niveau);
        window.display();
        sf::Time t1 = sf::seconds(2);
        sf::sleep(t1);
        sf::Packet packet;
        std::string ready = "ready";
        packet<<ready;
        socket.send(packet, IPHote, portExterne);
        statut++;
      }

      else if (statut == 402){
        Piece pieceRecue;
        sf::Packet packetPieceRecue;
        socket.receive(packetPieceRecue, IPHote, portExterne);
        packetPieceRecue>>pieceRecue;
        board.setPieceSuivante(pieceRecue);
        packetPieceRecue.clear();
        statut++;
      }

      else if(statut == 403){
        window.clear();
        afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
        window.display();

        board.setPieceCourante();
        Piece pieceRecue;
        sf::Packet packetPieceRecue;
        socket.receive(packetPieceRecue, IPHote, portExterne);
        packetPieceRecue>>pieceRecue;
        board.setPieceSuivante(pieceRecue);
        board.AfficherPiece();
        packetPieceRecue.clear();
        statut++;
      }

      else if(statut == 404) {

        tempsChute=dropSpeed;

        sf::Clock clock;
        sf::Clock timerUp;
        sf::Clock timerDown;
        bool finChute;
        sf::Time coolDown=sf::seconds(0.35f);
        bool firstTime=true;
        do {
          window.clear();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            board.deplacerPieceDroite();

          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            board.deplacerPieceGauche();

          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(firstTime){
              board.tournerPiece();
              firstTime=false;
            }
            else{
              if(timerUp.getElapsedTime()>=coolDown){
                board.tournerPiece();
                timerUp.restart();
              }
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(timerUp.getElapsedTime()>=sf::seconds(0.2)){
              finChute=board.deplacerPieceBas();
              timerDown.restart();
              window.clear();
              afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
              window.display();


              if (finChute){
                break;
              }

            }
          }


          sf::Time deltaT = clock.getElapsedTime();
          tempsChute-=deltaT;
          clock.restart();

          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);

          window.display();


        } while(tempsChute>sf::Time::Zero);

        bool changement=board.deplacerPieceBas();


        if(changement){
          NbLignes=board.ligne_full();
          if(NbLignes!=0){
            calculScore(score, niveau, NbLignes);
            window.clear();
            afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
            window.display();
          }
          board.setPieceCourante();


          Piece pieceRecue;
          sf::Packet packetPieceRecue;
          socket.receive(packetPieceRecue, IPHote, portExterne);
          packetPieceRecue>>pieceRecue;
          board.setPieceSuivante(pieceRecue);
          packetPieceRecue.clear();

          sf::Packet packetScore;

          if(!board.pieceSpawnable(board.getPieceCourante())){
            envoiScore(packetScore, -1);
            socket.send(packetScore, IPHote, portExterne);
            packetScore.clear();
            statut = 406;
          }
          else{
            envoiScore(packetScore, score);
            socket.send(packetScore, IPHote, portExterne);
            packetScore.clear();
          }

          int scoreTemp;
          socket.receive(packetScore, IPHote, portExterne);
          recepScore(packetScore, scoreTemp);
          packetScore.clear();

          if (scoreTemp==-1){
            statut++;
          }
          else{
            scoreAdverse=scoreTemp;
          }


          board.plateauEnvoi(plateauPacket);
          std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
          socket.send(plateauPacket, tailleEnvoi, IPHote, portExterne);
          std::size_t received;
          socket.receive(plateauPacket, tailleEnvoi, received, IPHote, portExterne);
          if (received==tailleEnvoi){
            convertPlateau(plateauPacket, plateauAdverse);
          }


          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
          board.AfficherPiece();
          sf::Time t1 = sf::seconds(0.4);
          sf::sleep(t1);
        }
        else {
          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
        }

      }

      else if (statut==405){
        tempsChute=dropSpeed;

        sf::Clock clock;
        sf::Clock timerUp;
        sf::Clock timerDown;
        bool finChute;
        sf::Time coolDown=sf::seconds(0.35f);
        bool firstTime=true;
        do {
          window.clear();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            board.deplacerPieceDroite();

          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            board.deplacerPieceGauche();

          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(firstTime){
              board.tournerPiece();
              firstTime=false;
            }
            else{
              if(timerUp.getElapsedTime()>=coolDown){
                board.tournerPiece();
                timerUp.restart();
              }
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(timerUp.getElapsedTime()>=sf::seconds(0.2)){
              finChute=board.deplacerPieceBas();
              timerDown.restart();
              window.clear();
              afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
              window.display();


              if (finChute){
                break;
              }

            }
          }


          sf::Time deltaT = clock.getElapsedTime();
          tempsChute-=deltaT;
          clock.restart();

          afficherPlateau(window,board);
          afficherScore(window, score, font);
          afficherProchainePiece(window, board, font);

          window.display();


        } while(tempsChute>sf::Time::Zero);

        bool changement=board.deplacerPieceBas();


        if(changement){
          NbLignes=board.ligne_full();
          if(NbLignes!=0){
            calculScore(score, niveau, NbLignes);
            window.clear();
            afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
            window.display();
          }
          board.setPieceCourante();
          board.setPieceSuivante();

          sf::Packet packetScore;

          if(!board.pieceSpawnable(board.getPieceCourante())){
            envoiScore(packetScore, -1);
            socket.send(packetScore, IPHote, portExterne);
            packetScore.clear();
            statut = 500;
          }
          else{
            envoiScore(packetScore, score);
            socket.send(packetScore, IPHote, portExterne);
            packetScore.clear();
          }


          board.plateauEnvoi(plateauPacket);
          std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
          socket.send(plateauPacket, tailleEnvoi, IPHote, portExterne);



          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
          board.AfficherPiece();
          sf::Time t1 = sf::seconds(0.4);
          sf::sleep(t1);
        }
        else {
          window.clear();
          afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
          window.display();
        }
      }

      else if (statut == 406){

        int scoreTemp;
        sf::Packet packetScore;
        socket.receive(packetScore, IPHote, portExterne);
        recepScore(packetScore, scoreTemp);
        packetScore.clear();
        if (scoreTemp==-1){
          statut=500;
        }
        else{
          scoreAdverse=scoreTemp;
        }


        std::size_t tailleEnvoi=(std::size_t)hauteur*largeur*sizeof(sf::Uint8);
        std::size_t received;
        socket.receive(plateauPacket, tailleEnvoi, received, IPHote, portExterne);
        if (received==tailleEnvoi){
          convertPlateau(plateauPacket, plateauAdverse);
        }




        window.clear();
        afficherJeuDeuxJoueurs(window, font, board, plateauAdverse, score, scoreAdverse);
        window.display();

      }

      else if (statut == 500){
        if (score==scoreAdverse){
          window.clear();
          afficherMatchNul(window, font, score);
        }
        else {
          bool win = score>scoreAdverse;
          window.clear();
          afficherResultat(window, font, score, scoreAdverse, win);
          window.display();
        }
      }



    }

    return 0;
}
