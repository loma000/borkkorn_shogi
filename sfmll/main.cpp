#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


const int BOARD_SIZE = 9;
const int CELL_SIZE = 80;  
const int WINDOW_WIDTH = BOARD_SIZE * CELL_SIZE;
const int WINDOW_HEIGHT = BOARD_SIZE * CELL_SIZE;

bool showmove = false;
	vector<pair<int, int>> startlocation  = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
	                                        ,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2}, 
	                                              {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6}};
	 
	
	vector<pair<int, int>> endlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };

	string rook = "C:/Users/Loma/Desktop/shogi/pawn.png";

	vector<pair<string, string>>mark = { {"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" }
	,{ "rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },
		{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"} 
	,{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"} };
	
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-7,-2,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,7,2,8,8,8,8,8,8,8,8,8
						   };

	Sprite f[40];
	Sprite mvt[81];
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

void loadtile() {
	int size = 48;
	int k = 0;
	for (int i = 0; i < 9; i++)
	{ 
		for (int j = 0; j < 9; j++)
		{
          mvt[k].setPosition(size * j, size * i);
		  k++;
		}
		
	}



}
bool check(  int x, int y, int id) {
	if (mark[id].first == "rook") {
		if(mark[id].second=="black")return  y == startlocation[id].first   && x == startlocation[id].second+1 ? true : false;
		if (mark[id].second == "white")return  y == startlocation[id].first   && x == startlocation[id].second -1? true : false;
		
} }
 



int main()
{ int size = 48;
	Texture moveabletile;
	int current=0;
	RenderWindow window( VideoMode(431, 431), "maibork");
	Texture item;
	Texture board;
	
	moveabletile.loadFromFile("C:/Users/Loma/Desktop/shogi/moveabletile.png");
	
	item.loadFromFile( rook );
	board.loadFromFile("C:/Users/Loma/Desktop/shogi/board.png");
	Sprite b(board);
	for (int i = 0; i < 40; i++)
	{
		f[i].setTexture(item);

	}
	for (int i = 0; i < 81; i++)
	{
		 mvt[i].setTexture(moveabletile);

	}
	loadsprite();
	loadtile();
	while (window.isOpen())
	{

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();


				 if (e.type == sf::Event::MouseButtonPressed) {

					 


				if (e.mouseButton.button == sf::Mouse::Left ) {
					
			for (int i = 0; i < 40; i++)
			{ 
					sf::FloatRect spriteBounds = f[i].getGlobalBounds();
					if (spriteBounds.contains(e.mouseButton.x, e.mouseButton.y) && !showmove) {
						current = i;
						showmove = true;
						cout << startlocation[i].first << "," << startlocation[i].second << " " << mark[i].first << " " << mark[i].second << " " << current << endl;
						f[i].setColor(sf::Color::Red);

						 

					}
					}
				}

				
			}
		 

		 if (e.type == sf::Event::KeyPressed) {
					if (e.key.code == sf::Keyboard::Space) {
						if (showmove)
						{
							showmove = false;
						}
						for (int i = 0; i < 40; i++)
						{
							f[i].setColor(sf::Color::White);

						}
					}
				}
			









		}




		//draw
    window.clear();
	window.draw(b);

	if (showmove)
	{

	
for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (check(i, j, current)) {
				 
				window.draw(mvt[i*9+j]);
			}


		}

	}}
	 
	

	cout << current<<showmove;

	for (int i = 0; i < 40; i++)
	{
		window.draw(f[i]);

	}
	window.display(); 


	}


	
	return 0;
}
