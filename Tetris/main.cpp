#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <string>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Tetris Faganello Laforge");
		window.setFramerateLimit(30);
		int niveau=0;
		int statut=0;
    int score=0;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
						if (statut==1){
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

        }
				sf::Font font;
				if (!font.loadFromFile("./External/Font/arial.ttf"))
	    //find this file in the "pong" example in the SFML examples folder
				{
    			std::cout << "Error loading font\n" ;
				}

				if (statut==0){ //affichage texte bienvenue
					sf::Text text;
					text.setString("Bienvenue dans notre Tetris");
					text.setFont(font);
					text.setCharacterSize(30);
					text.setFillColor(sf::Color::White);

					sf::FloatRect textRect = text.getLocalBounds();
					text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
					text.setPosition(sf::Vector2f(1080/2.0f,720/2.0f));
					window.draw(text);
					window.display();
					sf::Time t1 = sf::seconds(1.0);
					sf::sleep(t1);


					statut++;

				}

				if(statut==1){  //choix du niveau
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

          sf::Text text;
					text.setString("Choisir avec les fleches directionnelles gauche et droite");
					text.setFont(font);
					text.setCharacterSize(25);
					text.setFillColor(sf::Color::White);

					textRect = text.getLocalBounds();
					text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
					text.setPosition(sf::Vector2f(1080/2.0f,420));
					window.draw(text);

					window.draw(affNiveau);
					window.draw(valNiveau);
					window.display();
			}

      if(statut==2){
        window.clear();

        //affichage cadre de jeu

        sf::Vertex lineVert1[] =
        {
            sf::Vertex(sf::Vector2f(100, 30)),
            sf::Vertex(sf::Vector2f(100, 690))
        };

        window.draw(lineVert1, 2, sf::Lines);

        sf::Vertex lineVert2[] =
        {
            sf::Vertex(sf::Vector2f(400, 30)),
            sf::Vertex(sf::Vector2f(400, 690))
        };

        window.draw(lineVert2, 2, sf::Lines);

        sf::Vertex lineHori1[] =
        {
            sf::Vertex(sf::Vector2f(100, 30)),
            sf::Vertex(sf::Vector2f(400, 30))
        };

        window.draw(lineHori1, 2, sf::Lines);

        sf::Vertex lineHori2[] =
        {
            sf::Vertex(sf::Vector2f(100, 690)),
            sf::Vertex(sf::Vector2f(400, 690))
        };

        window.draw(lineHori2, 2, sf::Lines);

        //affichage score



        sf::Vertex scLineVert1[] =
        {
            sf::Vertex(sf::Vector2f(500, 300)),
            sf::Vertex(sf::Vector2f(500, 400))
        };

        window.draw(scLineVert1, 2, sf::Lines);

        sf::Vertex scLineVert2[] =
        {
            sf::Vertex(sf::Vector2f(800, 300)),
            sf::Vertex(sf::Vector2f(800, 400))
        };

        window.draw(scLineVert2, 2, sf::Lines);

        sf::Vertex scLineHori1[] =
        {
            sf::Vertex(sf::Vector2f(500, 300)),
            sf::Vertex(sf::Vector2f(800, 300))
        };

        window.draw(scLineHori1, 2, sf::Lines);

        sf::Vertex scLineHori2[] =
        {
            sf::Vertex(sf::Vector2f(500, 400)),
            sf::Vertex(sf::Vector2f(800, 400))
        };

        window.draw(scLineHori2, 2, sf::Lines);

        sf::Text txtScore;
        txtScore.setString("Score :");
        txtScore.setFont(font);
        txtScore.setCharacterSize(30);
        txtScore.setFillColor(sf::Color::White);

        sf::FloatRect textRect = txtScore.getLocalBounds();
        txtScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        txtScore.setPosition(sf::Vector2f(650,320));
        window.draw(txtScore);


        std::string txtValScore=std::to_string(score);

        sf::Text valScore;
        valScore.setString(txtValScore);
        valScore.setFont(font);
        valScore.setCharacterSize(30);
        valScore.setFillColor(sf::Color::White);

        textRect = valScore.getLocalBounds();
        valScore.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        valScore.setPosition(sf::Vector2f(650,370));
        window.draw(valScore);



        window.display();


      }


    }

    return 0;
}
