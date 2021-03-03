#include <SFML/Network/Packet.hpp>
#include "piece.h"


Piece::Piece(){}
Piece::Piece(Type theType, int theRota, int theX, int theY, Couleur theColor): type(theType), rotation(theRota), position_X(theX), position_Y(theY), couleur(theColor) {}




void Piece::setType(Type theType) {
  type = theType;
}
void Piece::setRota(int theRota) {
  rotation = theRota;
}
void Piece::setCouleur(Couleur theColor) {
  couleur = theColor;
}
void Piece::setPosX(int theX) {
  position_X = theX;
}
void Piece::setPosY(int theY) {
  position_Y = theY;
}
Type Piece::getType() {
  return type;
}
int Piece::getRota() {
  return rotation;
}
int Piece::getPosX() {
  return position_X;
}
int Piece::getPosY() {
  return position_Y;
}
Couleur Piece::getCouleur() {
  return couleur;
}


sf::Packet& operator <<(sf::Packet& packet, const Piece& piece)
{
		sf::Uint8 type = (sf::Uint8) piece.type;
		sf::Uint8 rota = (sf::Uint8) piece.rotation;
		sf::Uint8 posX = (sf::Uint8) piece.position_X;
		sf::Uint8 posY = (sf::Uint8) piece.position_Y;
		sf::Uint8 color = (sf::Uint8) piece.couleur;


		return (packet << type << rota << posX << posY << color);
}

sf::Packet& operator >>(sf::Packet& packet, Piece& piece)
{
		sf::Uint8 type;
		sf::Uint8 rota;
		sf::Uint8 posX;
		sf::Uint8 posY;
		sf::Uint8 color;

		packet >> type >> rota >> posX >> posY >> color;

		piece.type= (Type)type;
		piece.rotation=(int)rota;
		piece.position_X=(int)posX;
		piece.position_Y=(int)posY;
		piece.couleur=(Couleur)color;

		return packet ;
}
