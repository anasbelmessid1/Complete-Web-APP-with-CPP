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
Time to go to the source file and set up some stuff ! In the hexgame.cpp class we will start by setiing
up the screen /window where our game’s scene will be on , to do that we will go in the constructor
and set up the Horizantal an Vertical scroll bars , and the fixing up the windows’s size.

After that we will set up our game’s scene , to do that we will create a new object from the class
QGraphicsscene , and use it as a pointer to set the scene’s size which will be the exact same as the
screen’s size.

    The code implementation in “hexgame.cpp” is as shown bellow :

```javascript
#include "hexgame.h"
hexgame::hexgame(QWidget *parent){
 // set up the screen
 setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 setFixedSize(1024,768);
 // set up the scene
 scene = new QGraphicsScene();
 scene->setSceneRect(0,0,1024,768);
 setScene(scene);
}
void hexgame::start(){
}

```
So far , we should just have a blank window if we run the code , but before doing that we must go to
main.cpp and create a hexgame pointer that we will use to show the game.

    The code implementation in “main.cpp” :

```javascript
#include <QApplication>
#include "hexgame.h"
hexgame* game;
int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 game = new hexgame();
 game->show();
 game->start();
 return a.exec();
}
```
Second class “hexagone” :
  - Represents a hex
  - Inherits from QGraphicsPolygonItem 
  
Attributes : 
  - Side0Attack 
  - Side1Attack
  - Side2Attack
  ...
  - Side5Attack
 
Methods :
  - getOwner()
  - getAttackOf(int i)
  - setAttackOf(int i)
 
This class is going to inherit from QGraphicsPolygonItem which is going to help us draw our hexes
which are basically polygons.

This class contains a bunch of integer attributes”SideAttack” that describe the value of each of its
side attacks which go from 0 to 5 , basically because a hexagon has 6 angels from which the attack
can come. It also has some getters and setters which have information about the attack of a specific
side .

    The code implementation in hexagone.h

```javascript
#ifndef HEXAGONE_H
#define HEXAGONE_H
#include <QGraphicsPolygonItem>
class hexagone: public QGraphicsPolygonItem{
public:
 // constructors
 hexagone(QGraphicsItem* parent=NULL);
 // getters
 int getAttackOf(int side);
 // setters
 void setAttackOf(int side, int attack);
private:
 QString owner;
 int side0Attack;
 int side1Attack;
 int side2Attack;
 int side3Attack;
 int side4Attack;
 int side5Attack;
};
#endif // HEXAGONE_H
```
Moving on the source file hexagone.cpp where we will draw our hexes , and to do that let’s foget
programming for a bit and remember how we used to draw a hex in geometry class using an 
orthonormal axis and some points :

![1](https://user-images.githubusercontent.com/98289987/152769062-d4960326-3435-4f2b-a32d-9d20fc25bda1.PNG)

As we can see , we have a list of 6 points that define the shapeof our polygon .

To create this list of points we are going to create a QVector called hexPoints that will store a bunch
of QPointFs as shown below : 

```javascript
#include "hexagone.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
hexagone::hexagone(QGraphicsItem *parent){
 // points needed to draw hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
 QVector<QPointF> hexPoints;
 hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
 << QPointF(1,2) << QPointF(0,1);

```
The problem here is that our polygone is small , so what we are going to do is to scale it so that it
gets bigger , and we are going to do that by creating a for loop that will run through the list of points
and multiplying each point by 40 , and here is the code to do that :

```javascript
// scale the points
 int SCALE_BY = 40;
 for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
 hexPoints[i] = hexPoints[i] * SCALE_BY;
 }
 ```
 Now let’s go ahead and create an actual polygon object . we must pay attention to the difference
betwen QPolygon and QGraphicsPolygon , because qGraphicsPolygon will actually represent a
drawing of a polygon , but you have to create a polygon first and that will be done using QPolygon.

    The implementation of the code is as shown here :
```javascript
// create a polygon with the scaled points
 QPolygonF hexagon(hexPoints);
 // draw the poly
 setPolygon(hexagon);
}
```
So nothing is left for us but to test what we did , so we will go to the hexgame.cpp class and
implement the start method by creating a new hexagone object and add it to our scene that we
created using addItem() like shown below :
```javascript
void hexgame::start(){
 // test code TODO remove
 hexagone* hex = new hexagone();
 hex->setPos(100,100);
 scene->addItem(hex);
}
```

     Finally we will call the start method in the main.cpp file so that we can run our code :
```javascript
#include <QApplication>
#include "hexgame.h"
hexgame* game;
int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 game = new Game();
 game->show();
 game->start();
 return a.exec();
}
```
So after running the code we we can visualize our hexagone :

![2](https://user-images.githubusercontent.com/98289987/152771104-3e0d9d5f-ddc5-4f6a-8950-beabc8d674e2.PNG)

**THE HEXAGONEBOARD CLASS :**

This class is where our created hexes are going to be , so its basically a container for the hexes .
hence its called hexagoneboard.

Hexagoneboard : 
  - Represents a hex board that is responsible for manipulating hexes 
  - We can think of this as a container for hexes 
Attributes :
  - List of hexes
Methods :
  - getHexes()
  - placeHexes()
  
This class doesn’t inherit from anything , its Basically a container for the hexes .
the list of hexes will be create dusing a Qlist vector named hexes., so for that we need to include the
QList class in the include section .

For the methods , the first one is the getHexes()which will help us get the list of hexes that we
defined , and the second one is the placeHexes() method which defines the placement of the hexes
on hexagoneboard .

     The implementation of hexagoneboard.h :
```javascript 

#ifndef HEXAGONEBOARD_H
#define HEXAGONEBOARD_H
#include <QList>
#include "Hex.h"
class hexagoneboard{
public:
 // constructors
 hexagoneBoard();
 // getters/setters
 QList<hexagone*> getHexes();
 // public methods
 void placeHexes(int x, int y, int cols, int rows);
private:
 QList<hexagone*> hexes;
};
#endif // HEXAGONEBOARD_H

```
The next thing we will do is to go to the hexgame.cpp and erase the implementation of the start
method , which essentially had in it the code to create a simple hex . The thing is once we launch the
game the first thing should pop up is the hexagone board in which al the hexes will be in , so that’s
exactly what we will do , we will create a hexagoneboard !

```javascript 
void Game::start(){
 // test code TODO remove
 hexBoard = new HexBoard();
 hexBoard->placeHexes(100,100,3,3);
}
```
Regarding the implementation of the hexagoneboard’s methods , we have the simple getter
getHexes() which will basically return the hexes created . 
```javascript
QList<Hex *> HexBoard::getHexes(){
 return hexes;
}

```
The second method is the placeHexes() method , which will lead us to create another function called
createhexescolumn() , that takes in three parameters : x,y , numberofrows . this function basically
places a column on a specified x and y coordinate , and the way we accomplish that is we keep track
of how many rows we need to place in general so we know which row we’re currently placing , its
important to know that each row is placed 80 pixels lower so that we have our desired hexes stacked
together . 

    Let’s see what this looks like in code : createHexColumn() function :

```javascript

void hexagoneBoard::createHexColumn(int x, int y, int numOfRows){
 // creates a column of Hexes at the specified location with the specified
 // number of rows
 for (size_t i = 0, n = numOfRows; i < n; i++){
 hexagone* hex = new Hex();
 hex->setPos(x,y+82*i);
 hexes.append(hex);
 game->scene->addItem(hex);
 }
}
```

To run the code we will have to uncomment a line in the hexgame.h file that we commented earlier ,
this line holds the pointer of hexagoneboard class . 

    So the start method will look like this : 

```javascript
void start();
 // public attributes
 QGraphicsScene* scene;
 hexagoneoard* hexBoard;
 QString whosTurn;
};
```
Finally after running the code we will have a column of hexes looking like this :

![3](https://user-images.githubusercontent.com/98289987/152772730-e4dfe05d-cebf-468f-86fd-94c39da03830.PNG)

As we can see , we only have one column of hexes , but to actually play the game we will
need a ful board of hexes , so we basically have to repeat what we did to have several
columns that form a hexagone board. 

![4](https://user-images.githubusercontent.com/98289987/152772905-20e15ca2-5697-4b6c-8044-3b9afd3045ed.PNG)

In other words we will need to generalize the placehexes() member function , meaning we
will have it take parameters that will alter its behavior . These parameters are :

```javascript
//hexagoneboard.h:
void placeHexes(int x, int y, int cols, int rows);
```
The x and y coordinates represent the top left hand grd that we are going to create .
The cols parameter specifies the number of columns of hexes we want to create .
The rows parameter specifies the number of rows of hexes we want to create.
So the implementation of the placehexes() function in the hexagoneboard.cpp will be like
this : 

```javascript
void hexagone oard::placeHexes(int x, int y, int cols, int rows){
 int X_SHIFT = 82;
 int Y_SHIFT = 41;
 for (size_t i = 0, n = cols; i < n; i++){
 if (i % 2 == 0){ // even column
 Y_SHIFT = 0;
 }
 else{ // odd column
 Y_SHIFT = 41;
 }
 createHexColumn(x+X_SHIFT*i,y+Y_SHIFT,rows);
 }
}
```

Moving on to a new class , which is called the controlcenter class , as its name says , it will have
functionalities of a control center panel or window . It’s the first window that pops up once we
launch or game and it will give us three options /Buttons : Play – Quit – Help .

**Controlcenter :**
     - Inherits from QGraphicsRectItem
     - Constructor requires a QString describing the text of the button
     - Has a clicked() signal that can be connected to any slots 
     - Uses hoverEnterEvent() and hoverLeaveEvent() to change color when mouse is hovered over
     - Uses onMousePres() event to “emit” it’s clicked() signal
     
The first thing we will do in this class is to draw the rect and style it , then we will draw the text using
the QGaphicsTextItem which we will be inheriting first.
 
       The implementation of the code in the controlcenter.hfile :
       
```javascript
#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
class controlcenter:public QObject, public QGraphicsRectItem{
 Q_OBJECT
public:
 // Create a constructor
 controlcenter(QString name, QGraphicsItem* parent=NULL);
 // Create public methods (events)
 void mousePressEvent(QGraphicsSceneMouseEvent *event);
 void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
 void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
 void clicked();
private:
 QGraphicsTextItem* text;
};
#endif // CONTROLCENTER_H
```
    Then the implementation of these methods in the controlcenter.cpp file will be like this :

```javascript
#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
 // draw the rect
 setRect(0,0,200,50);
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::darkCyan);
 setBrush(brush);
 // draw the text
 text = new QGraphicsTextItem(name,this);
 int xPos = rect().width()/2 - text->boundingRect().width()/2;
 int yPos = rect().height()/2 - text->boundingRect().height()/2;
 text->setPos(xPos,yPos);
 // allow responding to hover events
 setAcceptHoverEvents(true);
}
```

Regarding the mousePressEvent() function , what will happen here is whenever the mouse is pressed
on a button the clicked signal will be activated and that will be done emit clicked() , and whatever we
conncet this single to will be activated once the clicked signal is emited.

```javascript
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
 emit clicked();
}
```
In hoverEnterEvent() function we will just change the color to cyan so once we hover over a button
the color of this button will turn into cyan .

```javascript
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
 // change color to cyan
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::cyan);
 setBrush(brush);
}
```
In hoveLeaveEvent() function , once we are no longer hovering over a button , its color will return
back to dark cyan.

```javascript
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
 // change color to dark cyan
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::darkCyan);
 setBrush(brush);
}
```
Once we launch the game , we don’t want the game to be the first thing we see , instead we want a
main menu that has some buttons that give us a choice on how to proceed in the game . to do that
we are going to create a new member function for the hexgame class called displayMainMenu .
So inside the mai.cpp and after creating an instance of our game , and after showing it , we don’t
want to directly start the game as we did before , instead we will display the main meu : 

```javascript
int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 game = new Game();
 game->show();
 game->displayMainMenu();
 return a.exec();
}
```
The main menu is going to display a play button and when that play button is clicked its going to
activate the start method and we are going to achieve that by connecting the play button clicked
signal to the hexgame class’s start slot , which means we have to turn the start method in to a slot in
the hexgame.h

    Showing the displayMaiinMenu in main.cpp:
    
```javascript
int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 game = new Game();
 game->show();
 game->displayMainMenu();
 return a.exec();
}
```
    In the implementation of the displayMainMenu() function in the hexgame.cpp , we will firs create the
    title text : 
    
```javascript
     void hexgame::displayMainMenu(){
 // create the title text
 QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Hex Warz"));
 QFont titleFont("comic sans",50);
 titleText->setFont(titleFont);
 int txPos = this->width()/2 - titleText->boundingRect().width()/2;
 int tyPos = 150;
 titleText->setPos(txPos,tyPos);
 scene->addItem(titleText);
```
    

    Creating the play button : then we will create the play button which we will connect to the start slot
    using the signal clicked() , then we will add it to our scene .
    
```javascript
// create the play button
 Button* playButton = new Button(QString("Play"));
 int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
 int byPos = 275;
 playButton->setPos(bxPos,byPos);
 connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
 scene->addItem(playButton);
```

    Creating the quit button : Same thing with the quit button , the only difference is in the signal , as we
    will connect the quit button to the close signal.

```javascript
// create the quit button
 Button* quitButton = new Button(QString("Quit"));
 int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
 int qyPos = 350;
 quitButton->setPos(qxPos,qyPos);
 connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
 scene->addItem(quitButton);
}
```
    Here is the result of the main menu that we created :

![5](https://user-images.githubusercontent.com/98289987/152775660-ace0071c-b640-4e48-bf52-8ee99ba9c0e7.PNG)

The next step is to make the game menu which will hold the general user interface elements shown
in this little representation that will make it easy to understand what we are trying to create . 

![6](https://user-images.githubusercontent.com/98289987/152775724-eef41d7c-b853-41e3-b127-890f517e143b.PNG)

We will create a method called drawPannel in the hexgame.h to essentially draw the panels of our
game ,then we will implement the function in the hexgame.cpp file as shown below 

```javascript
void hexgame::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
 // draws a panel at the specified location with the specified properties
 QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(color);
 panel->setBrush(brush);
 panel->setOpacity(opacity);
 scene->addItem(panel);
}
```

After that we will create another function called drawGUI() that will use the previous function
drawPannel() used to create the left and right panels and the text above them .

    The implementation of the drawGUI() function in hexgame.cpp is as shown below :
    
```javascript

void hexgame::drawGUI(){
 // draw the left panel
 drawPanel(0,0,150,768,Qt::darkCyan,1);
 // draw the right panel
 drawPanel(874,0,150,768,Qt::darkCyan,1);
 // place player 1 text
 QGraphicsTextItem* p1 = new QGraphicsTextItem("Player 1's Cards: ");
 p1->setPos(25,0);
 scene->addItem(p1);
 // place player 2 text
 QGraphicsTextItem* p2 = new QGraphicsTextItem("Player 2's Cards: ");
 p2->setPos(874+25,0);
 scene->addItem(p2);
 ```
 
 Then we will create two functions() that will basically serve as an indicator for who’s player it is to
play the game . the two methods are getWhosTurn() and setWhosTurn() , and their implementation
in the hexgame.cpp is as shown below : 

```javascript
QString hexgame::getWhosTurn(){
return whosTurn_;
}
void hexgame::setWhosTurn(QString player){
 // change the QString
 whosTurn_ = player;
 // change the QGraphicsTextItem
 whosTurnText->setPlainText(QString("Whos turn: ") + player);
}
 ```
    Then we will go to the drwGUI() function so we can display who’s turn it is on the scene of the game : 
    
    The drawGUI() function :
    
   ```javascript
    // place whosTurnText
 whosTurnText = new QGraphicsTextItem();
 setWhosTurn(QString("PLAYER1"));
 whosTurnText->setPos(490,0);
 scene->addItem(whosTurnText);
  ```

The purpose of this part is to draw the cards(hexes) in the Box of player 1 and in the box of player 2 as
well that can be placed by the player on the field or on the board, just as sort of remarque, we call them
cards when they are on the boxes and hexes when they are on the board.

 So, the first step is to create a bunch of cards. To do so, we are going to create methods in the hexgame
class named player1cards and player2cards.

 Then, we have to create another method called createNewCard that will create a new card for each
player and add it to the specefic list, after we are going to use the draw cards function which will
traverse through this list and draw them into the screen, so the implementation is working :
In the hexgame.h we need to add the code below:

coooooooooode hereeeeeeee

    The implementation of our two methods is added in the hexgame.cpp as following:
    
  ```javascript
    
   void hexgame::createNewCard(QString player){
 // create the card
 hexagone* card = new hexagone();
// we need to give a card a set of owner method
 card->setOwner(player);
 // add the card to the proper list and proper player
 if (player == QString("PLAYER1")){
 player1Cards.append(card);
 }
 else {
 player2Cards.append(card);
 }
 // draw the cards
 drawCards();
}
``` 
The code above is used to create just one, so we need to creat a bunch of cards for both players using the
method createIntialCards(), that's why we declare it in the hexgame.h, then we fill it up with:

```javascript
void hexgame::createInitialCards(){
 // create player 1's cards
 for (size_t i = 0, n = 5; i < n; i++){
 createNewCard(QString("PLAYER1"));
 }
 // create player 2's cards
 for (size_t i = 0, n = 5; i < n; i++){
 createNewCard(QString("PLAYER2"));
 }
 drawCards();
}
``` 
    After we have to set the owner by owner method,this is its implementation:
    .h
    // setters
```javascript
 void setAttackOf(int side, int attack);
 void setOwner(QString player);
``` 
.cpp 

```javascript
void hexagone::setOwner(QString player){
 owner = player;
}
``` 
But, we didn't finish our task yet, cause we didn't call the drawCards method yet to draw them into our
screen after getting rid of all the old cards, to do so we add the implementation in the hexgame.cpp:

```javascript
void hexgame::drawCards(){
 // traverse through list of cards and draw them
 // remove all of player1's cards from the scene
 for (size_t i = 0, n = player1Cards.size(); i < n; i++){
 scene->removeItem(player1Cards[i]);
 }
 // remove all of player2's cards from the scene
 for (size_t i = 0, n = player2Cards.size(); i < n; i++){
 scene->removeItem(player2Cards[i]);
 }
 // draw player1's cards
 for (size_t i = 0, n = player1Cards.size(); i < n; i++){
 Hex* card = player1Cards[i];
 card->setPos(13,25+85*i);
 scene->addItem(card);
 }
 // draw player2's cards
 for (size_t i = 0, n = player2Cards.size(); i < n; i++){
 Hex* card = player2Cards[i];
 card->setPos(874+13,25+85*i);
 scene->addItem(card);
 }
}
``` 
To finish the task, we have to do start() method in the same class and create our previous method
createInitialCards() after we draw the GUI.
```javascript
void hexgame::start(){
 // clear the screen
 scene->clear();
 // test code TODO remove
 hexagoneboard = new Hexagoneboard();
 hexagoneboard->placeHexes(100,100,3,3);
 drawGUI();
 createInitialCards();
}
``` 
**Summary:**

This is basically going to create our cards, then add them to the proper list (each one keeps track of a
specific player), after we will draw them. So the test will give us the next form:

![image](https://user-images.githubusercontent.com/98289987/152781520-5410c5bf-f760-4c68-b589-ad9030a69fb5.png)

Moving on now to the next part, we will here try to allow the placement of hexes and that's means inside
the board (called cards on the lists and hexes on the board), in other terms allow the player who has the
turn to click the cards on the box and then move them into the board. Effectively a card is a hexe that
has not been placed yet.

So, the hexgame class need to know which card we are trying to place using getters and setters for this
purpose, so we add in the hexagone.h the setters and getters below:

```javascript
//Create setters
 void setIsPlacedto(bool a);
 //Create getters
 bool getIsPlacedto();
private:
 bool isPlacedto;
``` 

Another thing that we need to know is which player own the hexe using setOwner(), one note about this
is that the previous method should change the hexe's color accordingly, so each player has a different
color. So the implementation is working as you can see below:

First, we add the setter and getter setOwner() /already created/ and getOwner(), we are working in the
same class hexagone.h.

```javascript
//Create setters
 void setOwner(QString player);
//Create getters
 QString getOwner()
 ``` 
    Then, we fill the getter in the hexagone.cpp with:
 ```javascript
 QString hexagone::getOwner(){
 return owner;
}
``` 
    The same thing for the getIsPlacedto():
```javascript
bool hexagone::getIsPlacedto(){
 return isPlacedto;
}
``` 
Now, let's change the color to the respective owner, we are going to use bleu for the first plyaer, red for
the second and grey for no one or neutral hexe. Let's start implementing:

    In hexagone.cpp we add the following code:
```javascript
void hexagone::setOwner(QString player){
 // Set the owner (player)
 owner = player;
 // We have to change the color of hexagones
 if (player == QString("NOONE")){
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::lightGray);
 setBrush(brush);
 }
 if (player == QString("PLAYER1")){
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::blue);
 setBrush(brush);
 }
 if (player == QString("PLAYER2")){
 QBrush brush;
 brush.setStyle(Qt::SolidPattern);
 brush.setColor(Qt::red);
 setBrush(brush);
 }
}
``` 

We want that all of the hexes to belong to no one, so after creating hexes, we are going to set owner to
no one initially in hexagoneboard.cpp :

```javascript
void hexagoneboard::createHexColumn(int x, int y, int numOfRows){
// initialize
 hex->setOwner(QString("NOONE"));
}
``` 
When we click the chosen card and move the mouse, the hexgame class must make that clicked card
follow the mouse kind of drag and drop the card. In the first place, we will create a pointer that refers to
the card which we want to place, so let's go to the hexgame.h and add the attribute:

```javascript
// public attributes
 hexagone* cardToPlace;
 ```
    In the hexgame.cpp, we need to initialize the cardToPlace to null.
 
 ```javascript
 void hexgame::start(){
 // initialize
 cardToPlace = NULL;
}
  ```
  We should first check if the hexe is neutral, if so we have to delete it and add this placed card into it, click
a hexe by player then drag it and replace a neutral hexe on the board. First we need to make that hexe
follow the mouse around, then when we clicks on an empty neutral hexe we want to place it instead of
the neutral one. For the mouse move event, the implementation is seen below :

      In hexgame.cpp
 ```javascript
 // events
 void mouseMoveEvent(QMouseEvent *event);
                  
 ```
 Now, the next thing is when we pick up a card and it's moving with us, when we click on a neutral hexe
we want to place it there, so let's go ahead inside the hexagone class and we will define a
mousePressEvent:

```javascript
//Add event
 void mousePressEvent(QGraphicsSceneMouseEvent* event);
             
 ```
 And now, what's happens to the hexe according to it's placement and when we click on a hexe?
 
    In hexagone.cpp

```javascript
void hexagone::mousePressEvent(QGraphicsSceneMouseEvent *event){
 // Case of the hexagone is not placed (in this case called a card) then pick it up
 if (getIsPlacedto() == false){
 game->pickUpCard(this);
 }
 // Otherwise (the hexagone is placed),replace it
 else {
 game->placeCard(this);
 }
}
```
As we can see, we haven't declare the pickUpCard() and the placeCard() methods yet, so let's go to the
hexgame.h and add it:
```javascript
// public methods
 void pickUpCard(hexagone* card);
 ```
    Then comes the implementation in the hexgame.cpp
   ```javascript   
 void hexgame::pickUpCard(hexagone *card){
 // picks up the specified card
 if (card->getOwner() == getWhosTurn() && cardToPlace == NULL){
 cardToPlace = card;
 originalPos = card->pos();
 return;
}
}
void hexgame::placeCard(hexagone *hexToReplace){
 // replaces the specified hex with the cardToPlace
 cardToPlace->setPos(hexToReplace->pos());
 hexBoard->getHexes().removeAll(hexToReplace);
 hexBoard->getHexes().append(cardToPlace);
 scene->removeItem(hexToReplace);
 cardToPlace->setIsPlaced(true);
 removeFromDeck(cardToPlace,getWhosTurn());
 //find neighbors
 cardToPlace->findNeighbors();
 cardToPlace->captureNeighbors();
 // make card to place null
 cardToPlace = NULL;
 // replace the placed card w a new one
 createNewCard(getWhosTurn());
 // make it the next players turn
 nextPlayersTurn();
 numCardsPlaced++;
 if (numCardsPlaced >= hexBoard->getHexes().size()){
 hexgameOver();
 }
}
  ```
  We have to declare two functions, the first switch the turns and the second takes a card that we want to
remove from whos deck in hexgame.h

```javascript
// public methods
 void nextPlayersTurn();
 void removeFromDeck(hexagone *card,QString player);
  ```
    Their implementation is given as shown:
```javascript
    void hexgame::nextPlayersTurn(){
 if (getWhosTurn() == QString("PLAYER1")){
 setWhosTurn(QString("PLAYER2"));
 }
 else {
 setWhosTurn(QString("PLAYER1"));
 }
}
void hexgame::removeFromDeck(hexagone *card, QString player){
 if (player == QString("PLAYER1")){
 // remove from player 1
 player1Cards.removeAll(card);
 }
 if (player == QString("PLAYER2")){
 // remove from player 1
 player2Cards.removeAll(card);
 }
}
  ```
  Let's make sure that we take care of this original position attribute, so for the game class we will give an
attribute which will keep track of the last cards or the card picked up and it's original position in case of
canceling the placing. 

    hexgame.h
  ```javascript
    // public attributes
 QPointF originalPos;
 
  ```
  
    The result of all this is given in the image below:
   ![image](https://user-images.githubusercontent.com/98289987/152783533-fcb28cb5-c53c-47d0-b081-27d0be392ca7.png)
   
But we still out of our object which is regenerate new cards instead of the placed ones into the
fields(player 1's Cards and player 2's Cards), but before that, we need to handle the case of if we don't
want to move a card then if we right click, it should move back. Let's go back in the hexagone class and
add a mousePressEvent():

 ```javascript
// events
 void mousePressEvent(QMouseEvent* event);
 
  ```
    It's implementation
```javascript
    void hexgame::mousePressEvent(QMouseEvent *event){
 // make right click return cardToPlace to originalPos
 if (event->button() == Qt::RightButton){
 if (cardToPlace){
 cardToPlace->setPos(originalPos);
 cardToPlace = NULL;
 return;
 }
 }
 QGraphicsView::mousePressEvent(event);
}
 ```
 
Return to our purpose which is regenerating cards, so we will modify in the placeCard() method in the
hexgame.cpp:

```javascript
void hexgame::placeCard(hexagone *hexToReplace){
 // replace the placed card with a new one
 createNewCard(getWhosTurn());
 // make it the next players turn
 nextPlayersTurn();
}
 ```
 The final result of this task is here:
 
![image](https://user-images.githubusercontent.com/98289987/152786104-a1386ba5-28c0-4525-ab5e-fe0f3edde2d9.png)

**Summary:**

As a summary of this part, we can say that we cheek if the card is placed or not,the we give them an
owner with a different color, after that we made the clicked card follow the mouse and when you drug it
in the board, the neutral hexe is replaced by our new placed card called hexe then we generate new
cards instead of the placed ones, and finally, we switch the players turn.Kind of remark, we call the
placed cards a hexes and the not placed cards are just cards.

Let's skip to the next part, the goal of this part is to generate a random attack for each side, so basically
for the cards not for the hexes, we want ro generate a random number for each side which represents
the attack value of that side.

Let's start our task by initializing the sides attack to 0, so let's start implementing in hexagone class.

    hexagone.cpp :
  ```javascript
 hexagone::hexagone(QGraphicsItem *parent){
 // Initializing side attacks to 0
 side0Attack = 0;
 side1Attack = 0;
 side2Attack = 0;
 side3Attack = 0;
 side4Attack = 0;
 side5Attack = 0;
  }
  ```
  Now, after we have the actual representation of the attack value of each side, let's create graphics text
item for them, so the implementation is in the same class as the previouse.

```javascript
hexagone::hexagone(QGraphicsItem *parent){
// Create QGraphicsTextItems to represent visually each side's attack
 QGraphicsTextItem* text0 = new QGraphicsTextItem(QString::number(0),this);
 QGraphicsTextItem* text1 = new QGraphicsTextItem(QString::number(0),this);
 QGraphicsTextItem* text2 = new QGraphicsTextItem(QString::number(0),this);
 QGraphicsTextItem* text3 = new QGraphicsTextItem(QString::number(0),this);
 QGraphicsTextItem* text4 = new QGraphicsTextItem(QString::number(0),this);
 QGraphicsTextItem* text5 = new QGraphicsTextItem(QString::number(0),this);
}
```
The main problem here is later, we are going to modify the set attack of member function to basically
change the text. To do so, we will create a qlist on the hexagone.h:

```javascript
class hexagone: public QGraphicsPolygonItem{
QList<QGraphicsTextItem*> attackTexts;
}
```
Then we are going to add each of this pointers to Q graphics text items to our attack text QList on
hexagone.cpp

```javascript
hexagone::hexagone(QGraphicsItem *parent){
attackTexts.append(text0);
 attackTexts.append(text1);
 attackTexts.append(text2);
 attackTexts.append(text3);
 attackTexts.append(text4);
 attackTexts.append(text5);
// Set the position of every attack text
 text0->setPos(50,0);
 text1->setPos(20,15);
 text2->setPos(20,40);
 text3->setPos(50,55);
 text4->setPos(80,40);
 text5->setPos(80,15);
}
```
We will set the position of each of this text items as shown above.

    After that, we have to traverse through all of the items (which they are in a list), and make them invisible
    by default.

```javascript
hexagone::hexagone(QGraphicsItem *parent){
 // Make all attacks texts invisible
 for (size_t i = 0, n = attackTexts.size(); i < n; i++){
 attackTexts[i]->setVisible(false);
 }
}
```

    To make them visible again, we need to add a setter in hexagone.h:
    
 ```javascript
    //Create setters
 void displaySideAttacks();
 ```
 Then it's implementation :
 
 ```javascript
 void hexagone::displaySideAttacks(){
 // Make all the side attacks texts visible
 for (size_t i = 0, n = attackTexts.size(); i < n; i++){
 attackTexts[i]->setVisible(true);
 }
}
  ```
  Whenever we create a new card, we want to set the attack values of each of its sides to a random, in
other terms the players are going to get cards with a random attacks values, to do so we have to add the
code below to thw hexgame.cpp:

 ```javascript
void hexgame::createNewCard(QString player){
 // randommize side attacks of card
 for (size_t i = 0, n = 6; i < n; i++){
 // generate a random number
 int randNum = rand() % 6 + 1; // random number 1 - 6
 card->setAttackOf(i,randNum);
 }
}
  ```
  As we know, we need to add the implementation of the setAttackOf() to make the previous code valid
and actually to change the actual attack and the text that represents the attack.

    In hexagone.cpp : 
    
 ```javascript
void hexagone::setAttackOf(int theside, int theattack){
 // We set the attack of the specified side and modify it's text
 switch (theside){
 case 0:
 side0Attack = theattack;
 attackTexts[0]->setPlainText(QString::number(theattack));
 case 1:
 side1Attack = theattack;
 attackTexts[1]->setPlainText(QString::number(theattack));
 case 2:
 side2Attack = theattack;
 attackTexts[2]->setPlainText(QString::number(theattack));
 case 3:
 side3Attack = theattack;
 attackTexts[3]->setPlainText(QString::number(theattack));
 case 4:
 side4Attack = theattack;
 attackTexts[4]->setPlainText(QString::number(theattack));
 case 5:
 side5Attack = theattack;
 attackTexts[5]->setPlainText(QString::number(theattack));
 }
}
 ```
 
    The next step so far is to make the attack visible (remember that we set them to invisible), using the
    code below.

    hexgame.cpp:
 ```javascript
void hexgame::createNewCard(QString player){
// make side attacks visible
 card->displaySideAttacks();
}

```
    Taaaada! Here is the result : 
    
![image](https://user-images.githubusercontent.com/98289987/152788121-c8498423-1c92-4c51-856c-15b26e81c7a4.png)

**Summary:**

To close this task, we resume that we did well the job which is to generate a random side attacks,
generate a text to represent those side attacks and also creat random cards essentially, so by doing that
the players now get a rid of cards and now it's possible to place the cards. The plan is when you place a
card, the concept is to compare two adjacent touching sides and the greater one will conquer the lesser
one, and this is the goal of our next task.

Move on now to the next part, as we said, the task here is to allow each of the hexes to know its
neighbors, then we will compare respective sides of attack for different colors.

So to detect the neighbors, we are going to create a bunch of lines that protrude out from the center of
the hexe, so the neighbors will be the ones that collide with this line, the last one must be rotated to 60
degrees from the original one ( 360/6= 60).

To achieve that point, we create a method called
createLines(), and a QList as well, so their implementation on the hexagone.h is given:

 ```javascript
class hexagone: public QGraphicsPolygonItem{
 //Create setters
 void createLines();
private:
 QList<QGraphicsLineItem*> lines;
 QList<hexagone*> neighbors;
 }
```
    The implementation of the method is given below:

```javascript
void hexagone::createLines(){
 QPointF hexCenter(x()+60,y()+40);
 QPointF finalPt(hexCenter.x(),hexCenter.y()-65);
 QLineF ln(hexCenter,finalPt);
 for (size_t i = 0, n = 6; i < n; ++i){
 QLineF lnCopy(ln);
 lnCopy.setAngle(90+60*i);
 QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy,this);
 lines.append(line);
 line->setVisible(false);
 }
}
```
    We need too to create this lines upon the construction of hexe, so we will go to the hexagone.cpp and
    add it :

```javascript
hexagone::hexagone(QGraphicsItem *parent){
 // Create lines
 createLines();
}
```
    Now, we will create a member function for traversing through this list of lines and finding the neighbors
    using the method findNeighbors() declared in hexagone.h like:
    
```javascript
 //Create setters
 void findNeighbors();
 ```
    Then, we are going to define it in hexagone.cpp.
        
```javascript
  void hexagone::findNeighbors(){
 for (size_t i = 0, n = lines.size(); i < n; i++){
 // if the line collides with an item of type Hex, add it to neighbors
 QList<QGraphicsItem*> cItems = lines[i]->collidingItems();
 for (size_t j = 0; j < cItems.size(); j++){
 hexagone* item = dynamic_cast<hexagone*>(cItems[j]);
 if (cItems[j] != this && item){
 neighbors.append(item);
 }
 }
 }
}
```
    Now, we just need a place to call this function, the natural place is when we place a card.
    hexgame.cpp
```javascript
   void hexgame::placeCard(hexagone *hexToReplace){
 //find neighbors
 cardToPlace->findNeighbors();
}
```
    The result is given as the previous one cause the lines are hidden
    
**Summary:**

To conclude, in this task, we did two things, the first is to drew lines protruding from the center of each
hexe and the second is to traverse those lists of lines to find out the neighbors of each hexe.

Finally comes the last part, so the goal of it is to count hexes and decide who won when the last card is
placed, and after that display a game over window with a replay and quit buttons.

So, to keep track of the number of cards that are placed, we have to create a numCardPlaced() function
inside the placeCard() in hexgame class.

    hexgame.h
  ```javascript
    class hexgame: public QGraphicsView{
// public attributes
 int numCardsPlaced;
}
```
    Then, we have to initialize the number of placed cards to 0.
    
    hexgame.cpp 
 ```javascript
    void hexgame::start(){
 // initialize
 cardToPlace = NULL;
 numCardsPlaced = 0;
}
```  
    Every time, we have to check if the number of placed cards is greater than the total number of hexes on
    the board, if so use hexgameOver() function.

    hexgameOver() is called when the last card has placed, and it will count who has the more hexes at the
    end.
    So, we are going to modify the hexgame.cpp
    
   ```javascript
  void hexgame::placeCard(hexagone *hexToReplace){
 numCardsPlaced++;
 if (numCardsPlaced >= hexBoard->getHexes().size()){
 hexgameOver();
 }
}
```
As we know, the hexgameover() function is not defined yet, so let's define it with the public methods in
the hexgame.h 
```javascript
class hexgame: public QGraphicsView{
// public methods
 void hexgameOver();
}
```
Then implement it in the hexgame.cpp as we know (now the process is very clair), but before we move
on to the implementation, we said that our method will be able to determine the player who has the
most hexes at the end, then display the game over window.
 ```javascript
 void hexgame::hexgameOver(){
 // count hexes, determine who has more, set messege
 int p1hexes = 0;
 int p2hexes = 0;
 for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i){
 if (hexBoard->getHexes()[i]->getOwner() == QString("PLAYER1")){
 p1hexes++;
 }
 else if (hexBoard->getHexes()[i]->getOwner() == QString("PLAYER2")){
 p2hexes++;
 }
 }
 QString messege;
 if (p1hexes > p2hexes){
 messege = "Player 1 has won the game!";
 }
 else if (p2hexes > p1hexes){
 messege = "Player 2 has won the game!";
 }
 else {
 messege = "Ha! Tie game!";
 }
 displayhexgameOverWindow(messege);
 }
```
Now, we are done with hexgameover() function, but our task still incomplete. To avoid that, we need to
set the displayhexgameOverWindow() method.

This method will:

   - Disable everything in the scene.
   - Darken it.
   - Show a Quit button and a play again button.
   
    To do so, first we have to create our method inside public methods in hexgame.h
    
 ```javascript
class hexgame: public QGraphicsView{
 // public methods
 void displayhexgameOverWindow(QString textToDisplay);
 }
```
    Then, it comes the implementation. hexgame.cpp
    
```javascript
void hexgame::displayhexgameOverWindow(QString textToDisplay){
 // disable all scene items
 for (size_t i = 0, n = scene->items().size(); i < n; i++){
 scene->items()[i]->setEnabled(false);
 }
 // pop up semi transparent panel
 drawPanel(0,0,1024,768,Qt::black,0.65);
 // draw panel
 drawPanel(312,184,400,400,Qt::lightGray,0.75);
 // create playAgain button
 controlcenter* playAgain = new controlcenter(QString("Play Again"));
 playAgain->setPos(410,300);
 scene->addItem(playAgain);
 connect(playAgain,SIGNAL(clicked()),this,SLOT(restarthexgame()));
 // create quit button
 controlcenter* quit = new controlcenter(QString("Quit"));
 quit->setPos(410,375);
 scene->addItem(quit);
 connect(quit,SIGNAL(clicked()),this,SLOT(close()));
 // create text annoucning winner
 QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
 overText->setPos(460,225);
 scene->addItem(overText);
}
```
    Last thing left to do is make this restarthexgame() slot, that's done by add the slot in hexgame.h
    class hexgame: public QGraphicsView{
        
```javascript
public slots:
 void start();
 void restarthexgame();
}
```
Now, the restarthexgame() is working by clearing all the player's cards, clear hexes, clear the scene and
use the start() function to start the game. To do all of that, we need to add it to the implementation of
the previous function.

    hexgame.cpp
```javascript
    void hexgame::restarthexgame(){
 // clear some stuff (player cards, the scene, hexes) then call start()
 player1Cards.clear();
 player2Cards.clear();
 hexBoard->getHexes().clear();
 scene->clear();
 start();
}
```
As a result we get the following output : 
![image](https://user-images.githubusercontent.com/98289987/152791036-87b054c3-dee6-4731-af93-225324287ce6.png)
