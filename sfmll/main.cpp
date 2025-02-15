#include"shogiengine.h"
#include"ui.h"
#include"kaipushpongtai.h"
#include"aieiei.h"




int main()
{ 
	path path;
	shogiengine shogi;
	  int count=0;
	   
	Texture moveabletile;
	Texture attacktile;
	int current=0;
	RenderWindow window( VideoMode(1000, 500), "maibork");
	Texture item;
	Texture board;
	attacktile.loadFromFile(path.atktiletex);
	moveabletile.loadFromFile(path.movetiletex);
	bool spriteMoved = false;
	item.loadFromFile(path.piece);
	board.loadFromFile(path.boards);
	Sprite b(board);
	b.setPosition(shogi.borderx, shogi.bordery);
	for (int i = 0; i < 40; i++)
	{
		shogi.f[i].setTexture(item);

	}
	for (int i = 0; i <16; i++)
	{
		shogi.capturedSprites2[i].setTexture(item);

	}
	for (int i = 0; i < 81; i++)
	{
		shogi.mvt[i].setTexture(moveabletile);
		shogi.atk[i].setTexture(attacktile);

	}
	shogi.loadcapturesprite();
	shogi.loadsprite();
	shogi.loadtile();
	window.setFramerateLimit(100);
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (  Keyboard::isKeyPressed( Keyboard::R)) {
				shogi.resetgame();
			}
			 

				 if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				     
					  if (!spriteMoved&& shogi.showmove)
				 {

				 
					for (int j = 0; j < 81; j++)
					{
						 
						if (shogi.atk[j].getGlobalBounds().contains(mousePos)&& shogi.showatk[j] == 1) {
							Vector2f position = shogi.atk[j].getPosition();
							int x = int((position.x - shogi.borderx) / shogi.size);
							int y = int((position.y - shogi.bordery) / shogi.size);
							for (int i = 0; i < 40; i++)
							{
								if (x == shogi.startlocation[i].first && y == shogi.startlocation[i].second&& shogi.dead[i]==0) {
									shogi.amdead[i] = 1;cout << shogi.mark[i].first << " " << i << " dead" << endl;
									shogi.ispromoted[i] = 0;
								 
								break;
								  }
							}

							





						
							shogi.normalsprite = false;
							shogi.startlocation[current].first = x;
							shogi.startlocation[current].second = y;

							shogi.move = true;
							//f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
							shogi.promoted(current);
							cout << current << " " << shogi.ispromoted[current] << endl;
							shogi.showatk[j] = 0;
							cout << "isclickatk";
							shogi.turn++;
							spriteMoved = true;
							
							
							break;
						};

						
					}}
				 if (!spriteMoved && shogi.showmove)
				 {

				 
					for (int k = 0; k < 81; k++)
					{
						 
						if (shogi.mvt[k].getGlobalBounds().contains(mousePos) && shogi.showmvt[k]==1) {
							Vector2f position = shogi.mvt[k].getPosition();
							
							if (shogi.deathsprite)
							{shogi.deathcount[current]--;
								
								for (int i = 0; i < 40; i++)
								{
								if(shogi.deathmark[current]==shogi.mark[i]&&shogi.dead[i]==1) {
									if (shogi.mark[i].second=="black")
									{
										shogi.mark[i].second = "white";
									}else shogi.mark[i].second = "black";
									shogi.amdead[i] = 0;
									shogi. dead[i] = 0;
									shogi.alreadydead[i] = 0;
									shogi.pawnid[i] *= -1;  

									cout << shogi.deathcount[current];
									current = i;
									shogi.loadsprite();
									break;
								}
								}
							}
							
							
							shogi.startlocation[current].first = (position.x- shogi.borderx) / shogi.size;
							shogi.startlocation[current].second = (position.y- shogi.bordery) / shogi.size;
							if (shogi.normalsprite)
							{
shogi.move = true;
							}
							else
							{
								cout << "sus";
shogi.f[current].setPosition(shogi.size * shogi.startlocation[current].first+ shogi.borderx, shogi.size * shogi.startlocation[current].second+ shogi.bordery);
							}
							
							
							shogi.promoted(current);
							cout << current<<" "<< shogi.ispromoted[current] << endl;
							shogi.showmvt[k] = 0;
	shogi.deathsprite = false;

							shogi.normalsprite = false;
							cout << "isclickmvt";
							shogi.turn++;
							spriteMoved = true;
							 break;

						}
					}
}

					if (shogi.showmove) {
						 
						shogi.showmove = false;
						for (int i = 0; i < 81; i++)
						{
							shogi.normalsprite = false;
							shogi.deathsprite =false;
							shogi.showmvt[i] = 0;
							shogi.showatk[i] = 0;
						}
						 
						break;

						 
					}
					 
					 for (int i = 0; i < 40; i++)
			{

					 
					if (!shogi.move && shogi.f[i].getGlobalBounds().contains(mousePos) && !shogi.showmove&& shogi.dead[i] ==0&&(shogi.turn%2==0&& shogi.mark[i].second=="black"|| shogi.turn % 2 == 1 && shogi.mark[i].second == "white")) {
						current = i;
						shogi.showmove = true;
						spriteMoved = false;
						cout << shogi.dead[i] << endl;
						shogi.normalsprite = true;
						
						break;
					}  
					} 

					 for (int i = 0; i < 14; i++)
					 {



						 if (!shogi.move && shogi.capturedSprites2[i].getGlobalBounds().contains(mousePos) && !shogi.showmove  && (shogi.turn % 2 == 0 && shogi.deathmark[i].second == "white" || shogi.turn % 2 == 1 && shogi.deathmark[i].second == "black")) {
							 current = i;
							 shogi.showmove = true;
							 spriteMoved = false;
							 cout << current << endl;
							 shogi.deathsprite = true;

							 break;
						 }  
					 }

				
			}
		 

		

		}

 

		if (shogi.move)
		{
			shogi.smoothmove(current);
		}



		//draw
    window.clear();
window.draw(b);
for (int i = 0; i < 40; i++)
	{
	
	
	
	if(shogi.dead[i]==0)
		window.draw(shogi.f[i]);



	if ((shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white") && shogi.ispromoted[i] == 1)
	{
		shogi.f[i].setColor(sf::Color::Magenta);

		

	}
	else if(shogi.ispromoted[i] == 1)
	{
		shogi.f[i].setColor(sf::Color::Red);
		

	}
	else if ((shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white"))
	{
		shogi.f[i].setColor(sf::Color::Color(193,255,146,200));
	}
	else
	{
		shogi.f[i].setColor(sf::Color::White);
	}
	 




	}
	if (shogi.showmove)
	{

	
for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (shogi.enermycheck(j, i, current) == "null" && ((shogi.walkcheck(j, i, current) && shogi.normalsprite) ||  shogi.dropCheck(j,i,current) &&shogi.deathsprite) && !shogi.isPathBlocked(j, i, current)) {
				shogi.showmvt[i * 9 + j]=1;
				window.draw(shogi.mvt[i * 9 + j]);
			}
			else if(shogi.enermycheck(j, i, current)=="ally" && shogi.walkcheck(j, i, current))
			{
				 
			}
			else if (shogi.enermycheck(j, i, current)=="enemy" && shogi.walkcheck(j, i, current)  && !shogi.isPathBlocked(j, i, current)  )
			{
				shogi.showatk[i * 9 + j] = 1;
				window.draw(shogi.atk[i * 9 + j]);
			}


		}

	}}

	if (!shogi.move)
	{
shogi.diecount();
	
	}
	shogi.drawCapturedPieces(window);
	 
	//cout << current<<showmove;

		
	window.display(); 


	}


	
	return 0;
}
