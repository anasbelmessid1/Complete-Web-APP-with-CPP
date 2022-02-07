# FinalProject-HexGame

*<h2>Introduction</h2>*

Let’s start by a short introduction to what the game is and what the gameplay is like .
Hex is a two player abstract strategy board game in which players attempt to connect opposite sides
of a hexagonal board. Hex was invented by mathematician and poet Piet Hein in 1942 and
independently by John Nash in 1948.

*Gameplay:

Two players alternatively taking turns placing hexes onto the board
 Each side of a hex has it’s own attack value
 When a a hex is placed , compare its side to all of its neighbours , if its attack value is greater
, “conquer” the neighbor .
 When the hex board is full announce the winner (the player with more hexes on the board)
First things first ,we are going to start by implementing the HexGame class which :
 Inherits from QGraphicsview
 Is Responsible for managing the global aspects of the game
And has the Attributes :
 Scene
 Hexboard
 Whosturn
And methods :
 Start () 
