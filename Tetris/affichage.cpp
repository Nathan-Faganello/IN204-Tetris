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
    sf::Vertex(sf::Vector2f(500, 400)),
    sf::Vertex(sf::Vector2f(500, 500))
};

window.draw(scLineVert1, 2, sf::Lines);

sf::Vertex scLineVert2[] =
{
    sf::Vertex(sf::Vector2f(800, 400)),
    sf::Vertex(sf::Vector2f(800, 500))
};

window.draw(scLineVert2, 2, sf::Lines);

sf::Vertex scLineHori1[] =
{
    sf::Vertex(sf::Vector2f(500, 400)),
    sf::Vertex(sf::Vector2f(800, 400))
};

window.draw(scLineHori1, 2, sf::Lines);

sf::Vertex scLineHori2[] =
{
    sf::Vertex(sf::Vector2f(500, 500)),
    sf::Vertex(sf::Vector2f(800, 500))
};

window.draw(scLineHori2, 2, sf::Lines);

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


//Cadre affichage nouvelle pièce

sf::Vertex npLineVert1[] =
{
    sf::Vertex(sf::Vector2f(500, 100)),
    sf::Vertex(sf::Vector2f(500, 300))
};

window.draw(npLineVert1, 2, sf::Lines);

sf::Vertex npLineVert2[] =
{
    sf::Vertex(sf::Vector2f(800, 100)),
    sf::Vertex(sf::Vector2f(800, 300))
};

window.draw(npLineVert2, 2, sf::Lines);

sf::Vertex npLineHori1[] =
{
    sf::Vertex(sf::Vector2f(500, 100)),
    sf::Vertex(sf::Vector2f(800, 100))
};

window.draw(npLineHori1, 2, sf::Lines);

sf::Vertex npLineHori2[] =
{
    sf::Vertex(sf::Vector2f(500, 300)),
    sf::Vertex(sf::Vector2f(800, 300))
};

window.draw(npLineHori2, 2, sf::Lines);

sf::Text nouvellePiece;
nouvellePiece.setString("Nouvelle piece :");
nouvellePiece.setFont(font);
nouvellePiece.setCharacterSize(30);
nouvellePiece.setFillColor(sf::Color::White);

sf::FloatRect nouvPieceRect = nouvellePiece.getLocalBounds();
nouvellePiece.setOrigin(nouvPieceRect.left + nouvPieceRect.width/2.0f, nouvPieceRect.top  + nouvPieceRect.height/2.0f);
nouvellePiece.setPosition(sf::Vector2f(650,120));
window.draw(nouvellePiece);

//Affichage de la prochaine pièce


sf::RectangleShape rectangle1(sf::Vector2f(28, 28));
sf::RectangleShape rectangle2(sf::Vector2f(28, 28));
sf::RectangleShape rectangle3(sf::Vector2f(28, 28));
sf::RectangleShape rectangle4(sf::Vector2f(28, 28));

sf::Color colorPiece;

Piece pieceSuivante(Type::O, 0,0,0,Couleur::ORANGE);


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






window.display();
