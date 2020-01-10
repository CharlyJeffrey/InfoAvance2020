# Connect 4 -- C++

Activité de programmation _Connect4_.

## Notions abordées
Les notions abordées lors de cette activités sont:
* Variables
* Fonctions
* Class
* Pointeurs
* Arrays

## VERSION 1
Dans la version 1, les jeunes feront:
* Source.cpp:
    * Macros _ROWS_ et _COLS_
    * Instancier un objet _Game_
* Game.h:
    * Déclaration de _Game(int, int)_, _Reset()_ et _PrintGrid()_ 
    * Ajout des attributs _rows_, _cols_, _grid_ et _symboles_ 
* Game.cpp:
    * Définition du constructeur _Game(int, int)_
    * Définition de la méthode _Reset()_
    * Définition de la méthode _PrintGrid()_

## VERSION 2
Dans la version 2, les jeunes feront:
* Source.cpp:
    * Ajout de la variable _choix_
    * Ajout de la boucle de jeu principale
    * Ajout de la fonction _GetValideChoice()_
* Game.h:
    * Modification de _Game(int, int)_ à _Game(int, int, string*)_
    * Déclaration de _IsColumnFull()_, _PlaceJeton(int)_, _ChangeJoueur()_ et _GetChoiceStatus(int)_
    * Ajout des attributs _colsCounter_, _quiJoue_ et _joueurs_
    * Ajout de l'enum _EChoiceStatus_
* Game.cpp:
    * Définition de _IsColumnFull()_, _PlaceJeton(int)_, _ChangeJoueur()_ et _GetChoiceStatus(int)_
    * Modification de _Reset()_ 

## VERSION 3
Dans la version 3, les jeunes feront:
* Source.cpp:
    * Modification de la condition de la boucle
    * Utilisation de _Game::CheckGrid(int)_
* Game.h:
    * Déclaration de _IsGameOver()_, _CheckGrid()_
    * Ajout des attributs _gameOver_, _gameWon_, _valeurSymboles_
* Game.cpp:
    * Définition de _IsGameOver()_, _CheckGrid()_

## VERSION 4
Dans la version 4, les jeunes feront:
* Source.cpp:
    * Encapsule l'obtention des noms dans la fonction _GetNames()_
    * Encapsule le déroulement d'une partie dans la fonction _Play()_
* Game.h:
* Game.cpp:
    * Inclu la méthode _CheckGrid(int)_ dans _PlaceJeton(int)_