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
vector<pair<int, int>> startlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
										,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
											  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
										,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6}  };
	 
	
	vector<pair<int, int>> endlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };

	string rook = "C:/Users/Loma/Desktop/shogi/pawn.png";

	vector<pair<string, string>>mark = { {"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" }
	,{ "rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },{"rook","black" },
		{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"}
	,{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"},{"rook","white"}  };
	
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-7,-2,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,7,2,8,8,8,8,8,8,8,8,8 
						   };
	Sprite atk[81];



	int  show[81];
	int dead[40];
	int ispromoted[40];






















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
			atk[k].setPosition(size * j, size * i);
          mvt[k].setPosition(size * j, size * i);
		  k++;
		}
		
	}



}
bool walkcheck(int x, int y, int id) {
	bool walkcheck;
		if (mark[id].first == "rook") {
			if (mark[id].second == "black")walkcheck = x == startlocation[id].first && y == startlocation[id].second + 1 ? true : false;
			if (mark[id].second == "white")walkcheck = x == startlocation[id].first && y == startlocation[id].second - 1 ? true : false;
		}
		
 








	 





	return walkcheck ;

}
bool  occupiedcheck(int x, int y, int id) {
	bool   occupied;
	 



	for (int i = 0; i < 40; i++)
	{
		if (x == startlocation[i].first && y == startlocation[i].second) {
			 
				occupied = false;
			break;
		}
		else occupied = true;

	}



	return  occupied ;

}
 
string enermycheck(int x, int y,   int id) {
	string enermy;


	for (int i = 0; i < 40; i++)
	{
		 
		if (mark[i].second != mark[id].second&& x == startlocation[i].first && y == startlocation[i].second) {
			enermy = "enemy";
			break;
		}
		else if(mark[i].second  == mark[id].second && x == startlocation[i].first && y == startlocation[i].second)
		{
			enermy = "ally";
			break;
		}
		
		else {
			enermy = "null";
			 
		}
	}

	
	return enermy;

}
void promoted(int id) {
	 

	if ( startlocation[id].second >= 6 && mark[id].second == "black"|| startlocation[id].second <= 2 && mark[id].second == "white")
	{
		ispromoted[id] = 1;
	}
	 
	




}

int main()
{
	int size = 48; int count=0;
	Texture moveabletile;
	Texture attacktile;
	int current=0;
	RenderWindow window( VideoMode(431, 431), "maibork");
	Texture item;
	Texture board;
	attacktile.loadFromFile("C:/Users/Loma/Desktop/shogi/attacktile.png");
	moveabletile.loadFromFile("C:/Users/Loma/Desktop/shogi/moveabletile.png");
	bool spriteMoved = false;
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
		 atk[i].setTexture(attacktile);

	}
	loadsprite();
	loadtile();
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();


				 if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				     
					  if (!spriteMoved&&showmove)
				 {

				 
					for (int j = 0; j < 81; j++)
					{
						 
						if ( atk[j].getGlobalBounds().contains(mousePos)&&show[j] == 1) {
							Vector2f position = atk[j].getPosition();
							int x = int(position.x) / size;
							int y = int(position.y) / size;
							for (int i = 0; i < 40; i++)
							{
								if (x == startlocation[i].first && y == startlocation[i].second) { dead[i] = 1; break; }
							}

							startlocation[current].first = x;
							startlocation[current].second = y;


							f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
							promoted(current);
							cout << current << " " << ispromoted[current] << endl;
							show[j] = 0;
							cout << "isclick";
							 
							spriteMoved = true;
							
							
							break;
						};

						
					}}
				 if (!spriteMoved && showmove)
				 {

				 
					for (int k = 0; k < 81; k++)
					{
						 
						if (mvt[k].getGlobalBounds().contains(mousePos) &&show[k]==1) {
							Vector2f position = mvt[k].getPosition();
							startlocation[current].first = (position.x) / size;
							startlocation[current].second = (position.y) / size;
							f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
							promoted(current);
							cout << current<<" "<<ispromoted[current] << endl;
							show[k] = 0;
							cout << "isclick";
							spriteMoved = true;
							 break;

						}
					}
}


					 
					
					 
					

					 
					 for (int i = 0; i < 40; i++)
			{

					 
					if (f[i].getGlobalBounds().contains(mousePos) && !showmove&& dead[i] ==0) {
						current = i;
						showmove = true;
						spriteMoved = false;
						 

						
						break;
					}  if (  showmove) {
						 
						showmove = false;
						 
						 
						break;

						 
					}
					} 


				 
				
				


	

 
					 




			
			 





				 


				
			}
		 

		 /*if (e.type == sf::Event::KeyPressed) {
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
			*/









		}

//cout <<   "," << showmove << " " << spriteMoved << " "  << endl;
if (ispromoted[current] == 1)
{
	 
			f[current].setColor(sf::Color::Red);

		}
		



		//draw
    window.clear();
window.draw(b);
for (int i = 0; i < 40; i++)
	{
	
	
	
	if(dead[i]==0)
		window.draw(f[i]);

	}
	if (showmove)
	{

	
for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (walkcheck(j, i, current)&&enermycheck(j, i, current) =="null") {
				show[i * 9 + j]=1;
				window.draw(mvt[i * 9 + j]);  
			}
			else if(enermycheck(j, i, current)=="ally" && walkcheck(j, i, current))
			{
				 
			}
			else if (enermycheck(j, i, current)=="enemy" && walkcheck(j, i, current))
			{
				show[i * 9 + j] = 1;
				window.draw(atk[i * 9 + j]);
			}


		}

	}}
	 
	

	//cout << current<<showmove;

		
	window.display(); 


	}


	
	return 0;
}
