#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

const int BOARD_SIZE = 9;
const int CELL_SIZE = 80;  
const int WINDOW_WIDTH = BOARD_SIZE * CELL_SIZE;
const int WINDOW_HEIGHT = BOARD_SIZE * CELL_SIZE;

class Piece
{
public:
	vector<pair<int, int>> startlocation = { {1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1},{9,1}
	                                        ,{2,2},{8,2},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},{8,3},{9,3} };
	vector<pair<int, int>> endlocation = { {1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1},{9,1}
										,{2,2},{8,2},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},{8,3},{9,3} };

	string rook = "C:/Users/Loma/Desktop/shogi/shogitest.png";

	vector<String>mark = {rook  };
	
	vector<int> pawnid = { 9,5,4,3,1,3,4,5,9,7,2,8,8,8,8,8,8,8,8,8,
						   -9,-5,-4,-3,-1,-3,-4,-5,-9,-7,-2,-8,-8,-8,-8,-8,-8,-8,-8,-8, };

};

void loadsprite() {




 }





int main()
{ 
	
	Piece piece;
	RenderWindow window( VideoMode(431, 431), "SFML works!");
	Texture text;
	Texture board;
	text.loadFromFile(piece.mark[0]);
	board.loadFromFile("C:/Users/Loma/Desktop/shogi/board.png");
	 
	 
	Sprite b(board);
	while (window.isOpen())
	{

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();










		}




		//draw
    window.clear();
	window.draw(b);
	window.display(); 


	}


	
	return 0;
}
