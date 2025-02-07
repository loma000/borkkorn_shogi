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
	 
	
	vector<pair<int, int>> resetlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},



												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };

	string rook = "C:/Users/Loma/Desktop/shogi/pawn.png";
	vector<pair<string, string>>mark = { {"lance","black" },{"knight","black" },{"silver","black" },{"gold","black" },{"king","black" },{"gold","black" },{"silver","black" },{"knight","black" },{"lance","black" },{"rook","black" }
	,{ "bishop","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },
		{"lance","white"},{"knight","white"},{"silver","white"},{"gold","white"},{"king","white"},{"gold","white"},{"silver","white"},{"knight","white"},{"lance","white"},{"rook","white"}
	,{"bishop","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"} };
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-7,-2,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,7,2,8,8,8,8,8,8,8,8,8 
						   };
	Sprite atk[81];



	int  show[81];
	int dead[40];
	int ispromoted[40];
	int turn=1;
	Sprite f[40];
	Sprite mvt[81];
	int size = 48;

	void resetgame() {
		int size = 48;
		for (int i = 0; i < 40; i++)
		{
			 
			f[i].setPosition(size * resetlocation[i].first, size * resetlocation[i].second);
			startlocation[i].first = resetlocation[i].first;
			startlocation[i].second = resetlocation[i].second;
			dead[i] = 0;
			ispromoted[i] = 0;
			turn = 1;
		}



	}

	bool isPathBlocked(int x, int y, int id) {
		string piece = mark[id].first;
		string color = mark[id].second;
		int sx = startlocation[id].first, sy = startlocation[id].second;

		// Only applicable for sliding pieces: Rook, Bishop, Promoted Rook, Promoted Bishop, and Lance  
		if (piece == "rook" || piece == "bishop" || ispromoted[id] == 1) {
			// Promoted Bishop (Dragon Horse) moves like a bishop but also one square in any direction
			if (piece == "bishop" && ispromoted[id] == 1) {
				if (abs(x - sx) <= 1 && abs(y - sy) <= 1) {
					return false; // Can move like a king, no need to check path
				}
			}
			// Promoted Rook (Dragon King) moves like a rook but also one square diagonally
			if (piece == "rook" && ispromoted[id] == 1) {
				if (abs(x - sx) == 1 && abs(y - sy) == 1) {
					return false; // Can move one square diagonally, no need to check path
				}
			}

			// Compute direction of movement
			int dx = (x > sx) ? 1 : (x < sx) ? -1 : 0;
			int dy = (y > sy) ? 1 : (y < sy) ? -1 : 0;

			// Ensure Bishop moves diagonally and Rook moves straight
			if ((piece == "bishop" || (piece == "bishop" && ispromoted[id] == 1)) && abs(x - sx) != abs(y - sy)) {
				return true; // Invalid diagonal move
			}
			if ((piece == "rook" || (piece == "rook" && ispromoted[id] == 1)) && dx != 0 && dy != 0) {
				return true; // Invalid straight move
			}

			// Check if path is blocked
			int cx = sx + dx, cy = sy + dy;
			while (cx != x || cy != y) {
				for (int i = 0; i < 40; i++) {
					if (startlocation[i].first == cx && startlocation[i].second == cy && dead[i] == 0) {
						return true; // Path is blocked
					}
				}
				cx += dx;
				cy += dy;
			}
		}

		// Special case for the unpromoted lance (moves only straight forward)
		if (piece == "lance" && ispromoted[id] == 0) {
			int dir = (color == "black") ? 1 : -1; // Direction (black moves down, white moves up)
			int cy = sy + dir; // Move in the correct direction
			while (cy != y) {
				for (int i = 0; i < 40; i++) {
					if (startlocation[i].first == sx && startlocation[i].second == cy && dead[i] == 0) {
						return true; // Path is blocked
					}
				}
				cy += dir; // Continue moving forward
			}
		}

		return false; // Path is clear
	}





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
	string piece = mark[id].first;
	string color = mark[id].second;
	int sx = startlocation[id].first, sy = startlocation[id].second;

	// Direction modifier (1 for black, -1 for white)
	int dir = (color == "black") ? 1 : -1;

	if (piece == "pawn" && ispromoted[id] == 0) {
		return (x == sx && y == sy + dir);
	}

	if (piece == "lance" && ispromoted[id] == 0) {
		return (x == sx && y > sy && color == "black") || (x == sx && y < sy && color == "white");
	}

	if (piece == "knight" && ispromoted[id] == 0) {
		return (x == sx + 1 && y == sy + 2 * dir) || (x == sx - 1 && y == sy + 2 * dir);
	}

	if (piece == "silver" && ispromoted[id] == 0) {
		return (y == sy + dir && (x == sx - 1 || x == sx || x == sx + 1)) || (y == sy - dir && (x == sx - 1 || x == sx + 1));
	}

	if (piece == "gold" && ispromoted[id] == 0 || piece == "pawn" && ispromoted[id] == 1 || piece == "silver" && ispromoted[id] == 1 || piece == "knight" && ispromoted[id] == 1 || piece == "lance" && ispromoted[id] == 1) {
		return (y == sy + dir && (x == sx - 1 || x == sx || x == sx + 1)) || (y == sy && (x == sx - 1 || x == sx + 1)) || (y == sy - dir && x == sx);
	}

	if (piece == "bishop" && ispromoted[id] == 0) {
		return abs(x - sx) == abs(y - sy);
	}
	if (piece == "rook" && ispromoted[id] == 0) {
		return (x == sx || y == sy);
	}
	if (piece == "king" && ispromoted[id] == 0) {
		return abs(x - sx) <= 1 && abs(y - sy) <= 1;
	}
	if (piece == "bishop" && ispromoted[id] == 1) {
		return abs(x - sx) == abs(y - sy) || (abs(x - sx) == 1 && abs(y - sy) == 0) || (abs(x - sx) == 0 && abs(y - sy) == 1);
	}
	if (piece == "rook" && ispromoted[id] == 1) {
		return (x == sx || y == sy) || (abs(x - sx) == 1 && abs(y - sy) == 1);
	}
	return false;  // Invalid move

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
		 
		if (mark[i].second != mark[id].second&& x == startlocation[i].first && y == startlocation[i].second&& dead[i]==0) {
			enermy = "enemy";
			break;
		}
		else if(mark[i].second  == mark[id].second && x == startlocation[i].first && y == startlocation[i].second && dead[i] == 0)
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
	RenderWindow window( VideoMode(800, 431), "maibork");
	Texture item;
	Texture board;
	attacktile.loadFromFile("C:/Users/Loma/Desktop/shogi/attack.png");
	moveabletile.loadFromFile("C:/Users/Loma/Desktop/shogi/move.png");
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
			if (  Keyboard::isKeyPressed( Keyboard::R)) {
				resetgame();
			}

				 if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				     
					  if (!spriteMoved&&showmove)
				 {

				 
					for (int j = 0; j < 81; j++)
					{
						 
						if ( atk[j].getGlobalBounds().contains(mousePos)&&show[j] == 1) {
							Vector2f position = atk[j].getPosition();
							int x = int(position.x / size);
							int y = int(position.y / size);
							for (int i = 0; i < 40; i++)
							{
								if (x == startlocation[i].first && y == startlocation[i].second&&dead[i]==0) { dead[i] = 1;cout << mark[i].first << " " << i << " dead" << endl;
								
								 
								break;
								  }
							}

							startlocation[current].first = x;
							startlocation[current].second = y;


							f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
							promoted(current);
							cout << current << " " << ispromoted[current] << endl;
							show[j] = 0;
							cout << "isclick";
							turn++;
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
							turn++;
							spriteMoved = true;
							 break;

						}
					}
}


					 
					
					 
					

					 
					 for (int i = 0; i < 40; i++)
			{

					 
					if (f[i].getGlobalBounds().contains(mousePos) && !showmove&& dead[i] ==0&&(turn%2==0&&mark[i].second=="black"|| turn % 2 == 1 && mark[i].second == "white")) {
						current = i;
						showmove = true;
						spriteMoved = false;
						cout << dead[i] << endl;

						
						break;
					}  if (  showmove) {
						 
						showmove = false;
						for (int i = 0; i < 81; i++)
						{
							show[i] = 0;

						}
						 
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
else
{
	f[current].setColor(sf::Color::White);

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
			if (walkcheck(j, i, current)&&enermycheck(j, i, current) =="null"  && !isPathBlocked(j,i,current)  ) {
				show[i * 9 + j]=1;
				window.draw(mvt[i * 9 + j]);  
			}
			else if(enermycheck(j, i, current)=="ally" && walkcheck(j, i, current))
			{
				 
			}
			else if (enermycheck(j, i, current)=="enemy" && walkcheck(j, i, current)  && !isPathBlocked(j, i, current)  )
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
