INSTRUSCTIONS

Fleche pour se deplacer. Bas accelere la brique, Espace pour la tourner.

On peut jouer en reseau local 2 joueur : 
	Sur une meme machine: on lance le programme 2 fois: un serveur, et un client. Le client prend en adresse IP l adresse locale (normalement 127.0.0.1) . Cependant on ne oeut pas controler les 2 fenetre en meme temps donc c est inutile
	
	Sur 2 machine sur un meme reseau : on lance le programme 2 fois: un serveur, et un client. Le client prend en adresse IP 192.168.X.X (normalement, faire un ifconfig avant pour voir l IP). IL s'agit d' un mode "classique", si lautre joueur fait une ligne, notre brique est acceleré ou une brique est placé au hasard sur la map
	
	Un push involontaire a été fait d'un main.c, d'un briqueS.h (au pluriel), et des .o . Ils ne sont pas utiles au projets, ils servaient à faire des tests
	
	
	
	
GRUNER MAXIME: termios, structure du niveau, chargement de la map,affichage niveau et brique, gestion du select, deroulement du jeu, deplacement, rotation,menu et mode reseau

MAUFFREY GWENAEL : gestion des Collisions, structure du niveau, chargement de la map, coloration, briques infini, ajout d'une brique à la map