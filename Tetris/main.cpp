#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <string>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
		window.setFramerateLimit(30);
		int niveau=0;
		int statut=0;

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
							}
						}

        }
				sf::Font font;
				if (!font.loadFromFile("./External/Font/arial.ttf"))
	    //find this file in the "pong" example in the SFML examples folder
				{
    			std::cout << "Error loading font\n" ;
				}

				if (statut==0){
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
					sf::Time t1 = sf::seconds(2.0);
					sf::sleep(t1);


					statut++;

				}

				if(statut==1){
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


    }

    return 0;
}
