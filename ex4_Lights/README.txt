"ex4 Lights Game"
============================================================
The name of the First student name : natan grosman
The ID of the First student : 314840182
The name of the second student name : avigdor shatz
The ID of the second student : 313134777

============================================================
general description:
a fun puzzle game
player have a board with a "puzzle" that he has to solve.
A player is shown a hexagon board with points ("light bulbs") scattered at equal intervals.
From each point one or more arms comes out. The maximum number of arms is 6 arms for points that are not on
Hexagon borders. When the arms of Adjacent points are aimed at each other and connected to the bulbs.
The central bulb is always on, and any bulb connected to the bulb is lit. (Even through other bulbs). The player's goal is to light all the bulbs on the board.
The bulbs turns 60 degrees, along with her arms. Pressing the mouse  button
The bulbs is rotated clockwise, the direction of the right button - counterclockwise.
 
============================================================
The Classes desighn:

Game - manages the game loop.
Board - manages all the logic of the board.
Point - responsiblle for the point and his edges, with some operations on them.

============================================================
Algorithms:
To turn on the light in all connected bulbs, I used 'bfs' algorithm starting from the middle point.

in order to create random level, I connected all the points using bfs again,
but I added some twist: 
to make the level better and more random. I started a queue with the middle point, and on each iteration
I chose a random number between 1 and the num of Adjacent points avalable (but not more than 4).
than the enqueued point connects only to that random num of neighbor points.

============================================================
