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
    int statutPause=0;


    Board board;

    board.setPieceSuivante();
    board.setPieceCourante();

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

        sf::Time t1 = sf::seconds(3.0);
        sf::sleep(t1);
        statut++;

      }

      else if(statut==3){
        window.clear();

        afficherPlateau(window,board);
        afficherScore(window, score, font);
        afficherProchainePiece(window, board, font);
        window.display();

      }
      else if(statut==100){
        window.clear();
        afficherPause(window, font, statutPause);
        window.display();

      }


    }

    return 0;
}
