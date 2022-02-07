# FinalProject-HexGame

*<h2>Introduction</h2>*

Let’s start by a short introduction to what the game is and what the gameplay is like .
Hex is a two player abstract strategy board game in which players attempt to connect opposite sides
of a hexagonal board. Hex was invented by mathematician and poet Piet Hein in 1942 and
independently by John Nash in 1948.

 **Gameplay :**

-  Two players alternatively taking turns placing hexes onto the board
- Each side of a hex has it’s own attack value 
- When a a hex is placed , compare its side to all of its neighbours , if its attack value is greater
, “conquer” the neighbor .
- When the hex board is full announce the winner (the player with more hexes on the board)

 First things first ,we are going to start by implementing the HexGame class which :
 
   - Inherits from QGraphicsview
   - Is Responsible for managing the global aspects of the game 
   
 And has the Attributes :
 
   - Scene 
   - HexBoard
   - Whosturn
 And methods :
   - Start () 

We will create a header file HexGame.h where we will initialize any variables and declare any
methods , that will be then used and implemented in the source file of the class HexGame.cpp.
To create the first attribute “scene” we will use a QGrapgicsscene pointer which means that we will
have to include the QGraphicsscene class in the include section , the attribute scene is basically the
layout where our game will be played.

The second attribute “hexboard” will be commented for now , because we haven’t yet created the
hexagoneboard class yet , which we will explain later on .

The third attribute “whosturn” will be used to determine which player’s turn it is to play the game ,
we can represent this attribute in a lot of ways such as 0 and 1 , but we chose to represent it as a
string , so for example string player1 means its player1’s turn .

Ps :All of the others game’s classes will follow the concept of encapsulation and information hiding
except for the HexGame class since so many other classes need to access its attributes so we may as
well just make them public.

```javascript

#ifndef HEXGAME_H
#define HEXGAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
// #include "hexagoneboard.h"
class hexgame: public QGraphicsView{
public:
 // constructors
hexgame (QWidget* parent=NULL);
 // public methods
 void start();
 // public attributes
 QGraphicsScene* scene;
 // hexagoneboard* hexBoard; TODO
 QString whosTurn;
};
#endif // HEXGAME_H

```
