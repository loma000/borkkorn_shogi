#include"shogiengine.h"
#include"ui.h"
#include"kaipushpongtai.h"
#include<iostream>





ui::ui(float width, float height)
{
	if (!font.loadFromFile("Roboto_Black.ttf")) {
		///for handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Tutorial");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 3));
}

void ui::draw(RenderWindow& window)
{
	for (int i = 0;i < Max_Items;i++) {
		window.draw(menu[i]);
	}
}

bool ui::isPlayClicked(Vector2f mousePos) {
	return menu[0].getGlobalBounds().contains(mousePos);

}

bool ui::isTutorialClicked(Vector2f mousePos)
{
	return menu[1].getGlobalBounds().contains(mousePos);
}

bool ui::isExitClicked(Vector2f mousePos)
{
	return menu[2].getGlobalBounds().contains(mousePos);
}



int main()
{ 
	path path;
	shogiengine shogi;
	int count=0;
	Texture back ;
	back.loadFromFile(path.backgroud);
	Sprite backgroud(back);
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
	//mainmenu
	vector<sf::Texture> textures(4);
	textures[0].loadFromFile(path.tt1);
	textures[1].loadFromFile(path.tt2);
	textures[2].loadFromFile(path.tt3);
	textures[3].loadFromFile(path.tt4);


	Sprite tutorialSprite;
	int tutorialPage = 0;
	tutorialSprite.setTexture(textures[tutorialPage]);


	bool Gamestatus = false;
	bool TutorialScreen = false;
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
	ui menu(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				shogi.resetgame();
			}


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

				if (!Gamestatus) { // Menu screen
					if (menu.isPlayClicked(mousePos)) {
						cout << " Play button clicked! Switching to game mode." << endl;
						Gamestatus = true;
					}
					else if (menu.isTutorialClicked(mousePos)) {
						cout << " Clicked tutorial" << endl;
						TutorialScreen = true;
					}
						if (TutorialScreen) {
							if (tutorialPage == 0) {
								FloatRect moreRulesButton(280, 380, 145, 45); // (x, y, width, height)
								FloatRect moveSetsButton(580, 380, 145, 45);
								if (moreRulesButton.contains(mousePos)) {
									cout << "1!" << endl;
									tutorialPage = 1;
									tutorialSprite.setTexture(textures[tutorialPage]);
								}
								if (moveSetsButton.contains(mousePos)) {
									cout << "2" << endl;
									tutorialPage = 2;
									tutorialSprite.setTexture(textures[tutorialPage]);
								}
							}
							else if (tutorialPage == 2) {
								FloatRect moveSets2Button(860, 400, 145, 45);
								if (moveSets2Button.contains(mousePos)) {
									cout << "3!" << endl;
									tutorialPage = 3;
									tutorialSprite.setTexture(textures[tutorialPage]);
								}
							}
							FloatRect backButton(860, 20, 145, 45);

								

								if (backButton.contains(mousePos)) {
									cout << "Back button clicked!" << endl;

									if (tutorialPage == 3) {
										tutorialPage = 2;  // Go from Page 3 to Page 2
									}
									else if (tutorialPage == 2 || tutorialPage == 1) {
										tutorialPage = 0;  // Go from Page 2 to Page 0
									}
									else if (tutorialPage == 0) {
										TutorialScreen = false;
										
									}

									tutorialSprite.setTexture(textures[tutorialPage]);
								}


							

							// Separate event handling for keyboard input
							if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
								cout << "Exiting tutorial." << endl;
								TutorialScreen = false;
							}
						}


					
					else if (menu.isExitClicked(mousePos)) {
						cout << "Exit button clicked! Closing game." << endl;
						window.close();
					}
				}
				else if (Gamestatus == true) {
					if (!spriteMoved && shogi.showmove)
					{


						for (int j = 0; j < 81; j++)
						{

							if (shogi.atk[j].getGlobalBounds().contains(mousePos) && shogi.showatk[j] == 1) {
								Vector2f position = shogi.atk[j].getPosition();
								int x = int((position.x - shogi.borderx) / shogi.size);
								int y = int((position.y - shogi.bordery) / shogi.size);
								for (int i = 0; i < 40; i++)
								{
									if (x == shogi.startlocation[i].first && y == shogi.startlocation[i].second && shogi.dead[i] == 0) {
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


						}
					}
					if (!spriteMoved && shogi.showmove)
					{


						for (int k = 0; k < 81; k++)
						{

							if (shogi.mvt[k].getGlobalBounds().contains(mousePos) && shogi.showmvt[k] == 1) {
								Vector2f position = shogi.mvt[k].getPosition();

								if (shogi.deathsprite)
								{
									shogi.deathcount[current]--;

									for (int i = 0; i < 40; i++)
									{
										if (shogi.deathmark[current] == shogi.mark[i] && shogi.dead[i] == 1) {
											if (shogi.mark[i].second == "black")
											{
												shogi.mark[i].second = "white";
											}
											else shogi.mark[i].second = "black";
											shogi.amdead[i] = 0;
											shogi.dead[i] = 0;
											shogi.alreadydead[i] = 0;
											shogi.pawnid[i] *= -1;

											cout << shogi.deathcount[current];
											current = i;
											shogi.loadsprite();
											break;
										}
									}
								}


								shogi.startlocation[current].first = (position.x - shogi.borderx) / shogi.size;
								shogi.startlocation[current].second = (position.y - shogi.bordery) / shogi.size;
								if (shogi.normalsprite)
								{
									shogi.move = true;
									shogi.promoted(current);
								}
								else
								{
									cout << "sus";
									shogi.f[current].setPosition(shogi.size * shogi.startlocation[current].first + shogi.borderx, shogi.size * shogi.startlocation[current].second + shogi.bordery);
								}


								
								cout << current << " " << shogi.ispromoted[current] << endl;
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
							shogi.deathsprite = false;
							shogi.showmvt[i] = 0;
							shogi.showatk[i] = 0;
						}

						break;


					}

					for (int i = 0; i < 40; i++)
					{


						if (!shogi.move && shogi.f[i].getGlobalBounds().contains(mousePos) && !shogi.showmove && shogi.dead[i] == 0 && (shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white")) {
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



						if (!shogi.move && shogi.capturedSprites2[i].getGlobalBounds().contains(mousePos) && !shogi.showmove && (shogi.turn % 2 == 0 && shogi.deathmark[i].second == "white" || shogi.turn % 2 == 1 && shogi.deathmark[i].second == "black")) {
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
		}
 



		if (shogi.move)
		{
			shogi.smoothmove(current);
		}



		//draw
    window.clear();
	if (!Gamestatus ) {
		menu.draw(window);
	}
	if (TutorialScreen == true) {
		window.draw(tutorialSprite);
	}
	else if(Gamestatus){
		window.draw(backgroud);
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
			if (shogi.enermycheck(j, i, current) == "null" && ((shogi.walkcheck(j, i, current) && shogi.normalsprite) ||  shogi.dropCheck(j, i, current) && shogi.deathsprite) && (!shogi.isPathBlocked(j, i, current)|| shogi.deathsprite)) {
				shogi.showmvt[i * 9 + j] = 1;
				window.draw(shogi.mvt[i * 9 + j]);
			}
			else if (shogi.enermycheck(j, i, current) == "ally" && shogi.walkcheck(j, i, current))
			{

			}
			else if (shogi.normalsprite&&shogi.enermycheck(j, i, current) == "enemy" && shogi.walkcheck(j, i, current) && !shogi.isPathBlocked(j, i, current))
			{
				shogi.showatk[i * 9 + j] = 1;
				window.draw(shogi.atk[i * 9 + j]);
			}


		}

	}
}
	
	}

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
