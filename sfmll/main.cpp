#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

const int BOARD_SIZE = 9;
const int CELL_SIZE = 80;  
const int WINDOW_WIDTH = BOARD_SIZE * CELL_SIZE;
const int WINDOW_HEIGHT = BOARD_SIZE * CELL_SIZE;

bool showmove=false;
	vector<pair<int, int>> startlocation  = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
	                                        ,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2}, 
	                                              {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6}};
	 
	
	vector<pair<int, int>> endlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };

	string rook = "C:/Users/Loma/Desktop/shogi/pawn.png";

	vector<pair<string, string>>mark = {{"rook","white" }};
	
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-7,-2,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,7,2,8,8,8,8,8,8,8,8,8
						   };

	Sprite f[40];
	
void loadsprite() {
	 int size = 48;

	for (int i = 0; i < 40; i++)
	{
		int n =  pawnid[i];
		int x = abs(n) - 1;
		int y =  n>0?1:0;
		f[i].setTextureRect(IntRect(size * x, size * y, size, size));
		f[i].setPosition(size*startlocation[i].first, size * startlocation[i].second );
	}



 }





int main()
{ 
	
	 
	RenderWindow window( VideoMode(431, 431), "maibork");
	Texture item;
	Texture board;
	item.loadFromFile( rook );
	board.loadFromFile("C:/Users/Loma/Desktop/shogi/board.png");
	for (int i = 0; i < 40; i++)
	{
		f[i].setTexture(item);

	}
	loadsprite();
	Sprite b(board);
	while (window.isOpen())
	{

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();


			for (int i = 0; i < 40; i++)
			{
				 if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					 
					sf::FloatRect spriteBounds = f[i].getGlobalBounds();
					if (spriteBounds.contains(e.mouseButton.x, e.mouseButton.y)) {
						 
						 cout << startlocation[i].first<<","<<startlocation[i].second << endl;
						f[i].setColor(sf::Color::Red);  
					}
				}
			}
		}

		 
			









		}




		//draw
    window.clear();
	window.draw(b);
	for (int i = 0; i < 40; i++)
	{
		window.draw(f[i]);

	}
	window.display(); 


	}


	
	return 0;
}
