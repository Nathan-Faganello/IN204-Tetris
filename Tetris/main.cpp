#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "piece.h"
#include "board.h"
#include "game.h"





int main()
{
    srand (time(NULL));
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Tetris Faganello Laforge");
		window.setFramerateLimit(30);
    sf::Font font;
    if (!font.loadFromFile("./External/Font/arial.ttf"))
  //find this file in the "pong" example in the SFML examples folder
    {
      std::cout << "Error loading font\n" ;
    }


		int niveau=0;
		int statut=0;
    int score=0;
    int NbLignes=0;
    int statutPause=0;

    sf::Time dropSpeed;
    sf::Time tempsChute;
    sf::Time deltaT;


    Board board;

    board.setPieceSuivante();


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
                  statut++;
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
          }


				if (statut==0){ //affichage texte bienvenue
          window.clear();
          afficherIntro(window, font);

					window.display();
				}

				else if(statut==1){  //choix du niveau
					window.clear();
					sf::Text affNiveau;
					affNiveau.setString("Niveau");
					affNiveau.setFont(font);
					affNiveau.setCharacterSize(30);
					affNiveau.setFillColor(sf::Color::White);
					sf::FloatRect textRect = affNiveau.getLocalBounds();
					affNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
					affNiveau.setPosition(sf::Vector2f(1080/2.0f,200));



					std::string textNiveau=std::to_string(niveau);

					sf::Text valNiveau;
					valNiveau.setString(textNiveau);
					valNiveau.setFont(font);
					valNiveau.setCharacterSize(30);
					valNiveau.setFillColor(sf::Color::White);
					textRect = valNiveau.getLocalBounds();
					valNiveau.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
					valNiveau.setPosition(sf::Vector2f(1080/2.0f,350));


					window.draw(affNiveau);
					window.draw(valNiveau);
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
        sf::Time t1 = sf::seconds(3);
        sf::sleep(t1);
        statut++;

      }

      else if(statut==3){



        tempsChute=dropSpeed;
        /*for(int i=0; i<hauteur; i++){
          for(int j=0; j<largeur; j++){
            std::cout<<" "<<board.plateau[i][j];
          }
          std::cout<<std::endl;
        }
        std::cout<<std::endl; */
        //sf::Time t1 = sf::seconds(0);
        //sf::sleep(t1); *
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
            if(timerUp.getElapsedTime()>=sf::seconds(0.3)){
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
            score = calculScore(score, niveau, NbLignes);
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


    }

    return 0;
}
