# IN204-Tetris


Compilation : make tetris-sfml clean dans le dossier Tetris\
<<<<<<< HEAD
Exécution: export LD_LIBRARY_PATH=External/SFML/lib && ./tetris-sfml
=======
Exécution: export LD_LIBRARY_PATH=External/SFML/lib && ./tetris-sfml 
>>>>>>> ad32e233c6ea86457cf2fb24decde435d9bd2983



# EXPLICATION DES STATUTS

Chaque statut correspond à un "état du jeu", comme le choix du mode, le début de la partie, la pause, etc\


statut = -1, 0, 1 : menu


## MODE SOLO


statut = 2 : début de la partie, avec l'affichage de la prochaine pièce (pendant 1 seconde)\
statut = 3 : boucle de jeu \
statut = 4 : fin de la partie \
statut = 100 : menu de pause \
statut  = 101 : affichage du jeu pendant 2 secondes avant reprise du jeu


## MODE 2 JOUEURS


statut = 200 : choix d'héberger ou de rejoindre une partie \
statut = 201 : affichage de l'IP et du port de l'hôte si on est l'hôte, et attente de la connexion à l'autre joueur \
statut = 202 : saisie clavier de l'IP de l'hôte (si on est l'invité) \
statut = 203 : saisie clavier du port de l'hôte (si on est l'invité) \
statut = 204 : affichage d'une erreur de connexion \


#### STATUTS 300+ : HÔTE


statut = 300 : choix du niveau \
statut = 301 : attente validation réception par l'invité + transmission de la première pièce \
statut = 302 : affichage jeu en mode 2 joueurs avant le début de la partie \
statut = 303 : boucle de jeu quand les deux joueurs jouent \
statut = 304 : boucle de jeu quand l'autre joueur a terminé \
statut = 305 : affichage de ce que fait l'autre joueur quand l'hôte a fini et que l'autre joueur n'a pas fini \


#### STATUTS 400+ : INVITE


statut = 400 : attente du choix du niveau par l'hôte \
statut = 401 : affichage du niveau choisi par l'hôte \
statut = 402 : réception de la première pièce \
statut = 403 : affichage jeu en mode 2 joueurs avant le début de la partie \
statut = 404 : boucle de jeu quand les deux joueurs jouent \
statut = 405 : boucle de jeu quand l'autre joueur a terminé \
statut = 406 : affichage de ce que fait l'autre joueur quand l'hôte a fini et que l'autre joueur n'a pas fini \


statut = 500 : affichage du résultat de la partie une fois terminée \

# REGLE MODE 2 JOUEURS


Pour le mode deux joueurs, le vainqueur est celui ayant le plus gros score une fois la partie terminée pour  les deux joueurs, c'est-à-dire quand les deux joueurs ont atteint le haut du plateau et que la prochaine pièce ne peut plus apparaitre.
