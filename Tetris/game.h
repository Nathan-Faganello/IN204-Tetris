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
#include <SFML/Network/Packet.hpp>


//calcule le nouveau score après la destruction de nbLignes, selon le niveau.

void calculScore(int &score, int niveau, int nbLignes);


//fonction d'affichage de l'introduction du jeu, lors de l'ouverture

void afficherIntro(sf::RenderWindow &window, sf::Font font);

//affiche un message d'attente pour l'invité pendant que l'hôte choisi le niveau.

void afficherAttenteChoixNiveau(sf::RenderWindow &window, sf::Font font);

//message qui est utilisé quand on est en attente d'une réponse de l'adversaire.

void afficherAttenteAdversaire(sf::RenderWindow &window, sf::Font font);

//affiche pour l'invité le niveau choisi par l'hôte/

void afficherNiveauChoisi(sf::RenderWindow &window, sf::Font font, int niveau);


//affiche le niveau qui est en train d'être choisi (interface de choix).

void afficherNiveau(sf::RenderWindow &window, sf::Font font, int niveau);

//fonction d'affichage de l'encadré du score pendant la partie. (mode 1 joueur)

void afficherScore(sf::RenderWindow &window, int score, sf::Font font);

//affiche l'encadré avec la prochaine pièce qui entrera en jeu (mode 1 joueur)

void afficherProchainePiece(sf::RenderWindow &window, Board board, sf::Font font);

//affiche le plateau de jeu avec les pièces déjà posées et la pièce en cours.

void afficherPlateau(sf::RenderWindow &window, Board board);

//interface de pause (disponible qu'en mode 1 joueur)

void afficherPause(sf::RenderWindow &window,sf::Font font, int statutPause);

//affichage de la fin de partie (mode 1 joueur)

void afficherFin(sf::RenderWindow &window, sf::Font font, int score);

//interface du choix du mode entre 1 ou 2 joueurs

void afficherMulti(sf::RenderWindow &window,sf::Font font, int multijoueur);

//interface de choix entre être l'hôte ou rejoindre une partie.

void afficherHeberge(sf::RenderWindow &window,sf::Font font, int heberge);

//interface pour l'hôte, affiche son IP et le port local utilisé, à transmettre à l'invité pour qu'il puisse rejoindre.

void afficherIP(sf::RenderWindow &window,sf::Font font, sf::IpAddress addressIP, unsigned short localPort);

//interface pour écrire lIP de l'hôte pour rejoindre la partie.

void afficherEntreeIP(sf::RenderWindow &window,sf::Font font, std::string entreeIP);

//interface pour écrire le port utilisé par l'hôte pour pouvoir rejoindre la partie.

void afficherEntreePort(sf::RenderWindow &window,sf::Font font, std::string portExterneTxt);

//Message d'erreur si jamais la connexion échoue

void afficherErreurConnection(sf::RenderWindow &window,sf::Font font);


//Message d'erreur envoyé si le contenue reçu n'est pas le bon.

void afficherErreurCommunication(sf::RenderWindow &window,sf::Font font);

//message s'affichant au début du jeu si jamais il est impossible d'ouvrir un port, pour signaler que le mode 2 joueurs ne sera pas fonctionnel

void afficherErreurReseau(sf::RenderWindow &window,sf::Font font);

//Affiche le score du joueur pendant la partie (en mode 2 joueurs)

void afficherScoreAllie(sf::RenderWindow &window, sf::Font font, int allyScore);

//affiche le score adverse pendant la partie (mode 2 joueurs)

void afficherScoreEnnemi(sf::RenderWindow &window, sf::Font font, int ennemyScore);

//Affiche la prochaine pièce à tomber, commune aux deux joueurs (mode 2 joueurs)

void afficherProchainePieceCommune(sf::RenderWindow &window, Board board, sf::Font font);

//affiche le plateau adverse, sera raffraichi à la fin de chaque tour  (mode 2 joueurs)

void afficherPlateauEnnemi(sf::RenderWindow &window, int plateauEnnemi[hauteur][largeur]);

void recepScore(sf::Packet &packet, int &score);

void envoiScore(sf::Packet &packet, const int score);

//Affiche l'entièreté du plateau en un seul appel (mode 2 joueurs)

void afficherJeuDeuxJoueurs(sf::RenderWindow &window, sf::Font font, Board allyBoard, int plateauEnnemi[hauteur][largeur], int allyScore, int ennemyScore);



#endif // !GAME_H
