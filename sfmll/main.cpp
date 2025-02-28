
#include"shogiengine.h"
#include"ui.h"
#include"kaipushpongtai.h"
#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <thread>
#include <atomic>





ui::ui(float width, float height)
{
	if (!font.loadFromFile("Roboto_Black.ttf")) {
		///for handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(Vector2f(width / 2, height / (Menu_Items + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Tutorial");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(Vector2f(width / 2, height / (Menu_Items + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(Vector2f(width / 2, height / (Menu_Items + 1) * 3));

	mode[0].setFont(font);
	mode[0].setFillColor(Color::Red);
	mode[0].setString("Normal Mode");
	mode[0].setOrigin(mode[0].getGlobalBounds().width / 2, mode[0].getGlobalBounds().height / 2);
	mode[0].setPosition(Vector2f(width / 2, height / (Mode_Items + 1) * 1));

	mode[1].setFont(font);
	mode[1].setFillColor(Color::White);
	mode[1].setString("Gamble Mode");
	mode[1].setOrigin(mode[1].getGlobalBounds().width / 2, mode[1].getGlobalBounds().height / 2);
	mode[1].setPosition(Vector2f(width / 2, height / (Mode_Items + 1) * 2));

	mode[2].setFont(font);
	mode[2].setFillColor(Color::White);
	mode[2].setString("3");
	mode[2].setOrigin(mode[2].getGlobalBounds().width / 2, mode[2].getGlobalBounds().height / 2);
	mode[2].setPosition(Vector2f(width / 2, height / (Mode_Items + 1) * 3));

	mode[3].setFont(font);
	mode[3].setFillColor(Color::White);
	mode[3].setString("Back");
	mode[3].setOrigin(mode[3].getGlobalBounds().width / 2, mode[3].getGlobalBounds().height / 2);
	mode[3].setPosition(Vector2f(width / 2, height / (Mode_Items + 1) * 4));
}


void ui::draw(RenderWindow& window, bool isMode) {
	if (isMode) {
		for (int i = 0; i < Mode_Items; i++) {
			window.draw(mode[i]);
		}
	}
	else {
		for (int i = 0; i < Menu_Items; i++) {
			window.draw(menu[i]);
		}
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

bool ui::isNormalclicked(Vector2f mousePos)
{
	return mode[0].getGlobalBounds().contains(mousePos);
}

bool ui::isGambleClicked(Vector2f mousePos)
{
	return mode[1].getGlobalBounds().contains(mousePos);
}

bool ui::isgamemode3clicked(Vector2f mousePos)
{
	return mode[2].getGlobalBounds().contains(mousePos);
}

bool ui::isBackClicked(Vector2f mousePos)
{
	return mode[3].getGlobalBounds().contains(mousePos);
}

atomic<bool> keepPlaying(true);

void loopSound() {
	mciSendString(TEXT("open \"asset/bgsound.wav\" type waveaudio alias bgm"), NULL, 0, NULL);

	while (keepPlaying) {
		mciSendString(TEXT("play bgm from 0"), NULL, 0, NULL);
		Sleep(286000); // Adjust based on file length
	}

	mciSendString(TEXT("close bgm"), NULL, 0, NULL);
}




int main()
{
	srand(time(0));
	path path;
	shogiengine shogi;
	int count = 0;
	Texture back;
	back.loadFromFile(path.backgroud);
	Sprite backgroud(back);
	Texture moveabletile;
	Texture attacktile;
	int current = 0;
	RenderWindow window(VideoMode(1000, 500), "maibork");
	Texture item;
	Texture board;
	shogi.loadtextureyesno(path);
	attacktile.loadFromFile(path.atktiletex);
	moveabletile.loadFromFile(path.movetiletex);
	bool spriteMoved = false;
	item.loadFromFile(path.piece);
	board.loadFromFile(path.boards);
	Sprite b(board);
	b.setPosition(shogi.borderx, shogi.bordery);
	//mainmenu
	vector<sf::Texture> textures(5);
	textures[0].loadFromFile(path.tt1);
	textures[1].loadFromFile(path.tt2);
	textures[2].loadFromFile(path.tt3);
	textures[3].loadFromFile(path.tt4);
	textures[4].loadFromFile(path.tt5);

	//esc
	bool escnow = false;
	RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(Color(0, 0, 0, 128));

	//gamemode
	bool gamemodescreen = false;
	int gamemode = 0;


	Sprite tutorialSprite;
	int tutorialPage = 0;
	tutorialSprite.setTexture(textures[tutorialPage]);


	bool Gamestatus = false;
	bool TutorialScreen = false;
	for (int i = 0; i < 40; i++)
	{
		shogi.f[i].setTexture(item);

	}
	for (int i = 0; i < 16; i++)
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
	window.setFramerateLimit(50);
	ui menu(window.getSize().x, window.getSize().y);
	ui mode(window.getSize().x, window.getSize().y);
	thread bgmThread(loopSound); //play background music
	bgmThread.detach();
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
			if (Gamestatus == true) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					escnow = true;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

				if (!Gamestatus) { // Menu screen
					if (menu.isPlayClicked(mousePos)) {
						cout << " Play button clicked! Switching to game mode." << endl;
						gamemodescreen = true;
						PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
						cout << "gamemode selection";
					}
					else if (menu.isTutorialClicked(mousePos)) {
						cout << " Clicked tutorial" << endl;
						PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
						TutorialScreen = true;
					}
					if (TutorialScreen) {
						if (tutorialPage == 0) {
							FloatRect moreRulesButton(225, 380, 145, 45); // (x, y, width, height)
							FloatRect moveSetsButton(430, 380, 145, 45);
							FloatRect GambleRuleButton(635, 380, 145, 45);
							if (moreRulesButton.contains(mousePos)) {
								cout << "1!" << endl;
								PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
								tutorialPage = 1;
								tutorialSprite.setTexture(textures[tutorialPage]);
							}
							if (moveSetsButton.contains(mousePos)) {
								cout << "2" << endl;
								PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
								tutorialPage = 2;
								tutorialSprite.setTexture(textures[tutorialPage]);
							}
							if (GambleRuleButton.contains(mousePos)) {
								cout << "Gamble rule clicked";
								PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
								tutorialPage = 4;
								tutorialSprite.setTexture(textures[tutorialPage]);
							}
						}
						else if (tutorialPage == 2) {
							FloatRect moveSets2Button(860, 400, 145, 45);
							if (moveSets2Button.contains(mousePos)) {
								cout << "3!" << endl;
								PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
								tutorialPage = 3;
								tutorialSprite.setTexture(textures[tutorialPage]);
							}
						}
						FloatRect backButton(860, 20, 145, 45);



						if (backButton.contains(mousePos)) {
							cout << "Back button clicked!" << endl;
							PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
							if (tutorialPage == 3) {
								tutorialPage = 2;  // Go from Page 3 to Page 2
							}
							else if (tutorialPage == 2 || tutorialPage == 1 || tutorialPage == 4) {
								tutorialPage = 0;  // Go from Page 2 to Page 0
							}
							else if (tutorialPage == 0) {
								TutorialScreen = false;

							}

							tutorialSprite.setTexture(textures[tutorialPage]);
						}




						// Separate event handling for keyboard input
						/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
							cout << "Exiting tutorial." << endl;
							TutorialScreen = false;
						}*/
					}



					else if (menu.isExitClicked(mousePos)) {
						PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
						cout << "Exit button clicked! Closing game." << endl;
						window.close();
					}

					if (gamemodescreen) {
						if (mode.isNormalclicked(mousePos)) {
							PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
							cout << "Normal Clicked";
							gamemode = 0;
							Gamestatus = true;
							gamemodescreen = false;
						}
						else if (mode.isGambleClicked(mousePos)) {
							PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
							cout << "Gamble Clicked";
							gamemode = 1;
							cout << "gamble mode onnnn";
							Gamestatus = true;
							gamemodescreen = false;
						}
						else if (mode.isgamemode3clicked(mousePos)) {
							PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
							cout << "gamemode 3 Clicked";
							Gamestatus = true;
							gamemodescreen = false;
						}
						else if (mode.isBackClicked(mousePos)) {
							PlaySound(TEXT("asset/button2.wav"), NULL, SND_FILENAME | SND_ASYNC);
							cout << "Back Clicked";
							gamemodescreen = false;
						}
					}

				}
				else if (Gamestatus == true) {
					 
					if (shogi.esc.getGlobalBounds().contains(mousePos)) {
						escnow = true;
					}
					
					if (shogi.conti.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
					}
					if (shogi.restart.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
						shogi.resetgame();

					}
					if (shogi.back.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
						Gamestatus = false;
						shogi.resetgame();
					}
					if (escnow == false){


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


									//f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
									shogi.promoted(current);
									cout << current << " " << shogi.ispromoted[current] << endl;
									shogi.showatk[j] = 0;
									cout << "isclickatk";
									PlaySound(TEXT("asset/capture.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
								PlaySound(TEXT("asset/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
								shogi.turn++;
								spriteMoved = true;
								break;

							}
						}
					}
					if (shogi.gamble.getGlobalBounds().contains(mousePos) && shogi.gambleon && gamemode == 1) {
						shogi.turn++;
						PlaySound(TEXT("asset/button1.wav"), NULL, SND_FILENAME | SND_ASYNC);
						shogi.gamblechange(current);
						shogi.gambleon = false;
					}
					if (shogi.showmove) {
						shogi.gambleon = false;
						shogi.showmove = false;
						for (int i = 0; i < 81; i++)
						{
							shogi.normalsprite = false;
							shogi.deathsprite = false;
							shogi.showmvt[i] = 0;
							shogi.showatk[i] = 0;
						}




					}

					for (int i = 0; i < 40; i++)
					{


						if (!shogi.move && shogi.f[i].getGlobalBounds().contains(mousePos) && !shogi.showmove && shogi.dead[i] == 0 && (shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white") && !shogi.promotecheck) {
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



						if (!shogi.move && shogi.capturedSprites2[i].getGlobalBounds().contains(mousePos) && !shogi.showmove && (shogi.turn % 2 == 0 && shogi.deathmark[i].second == "white" || shogi.turn % 2 == 1 && shogi.deathmark[i].second == "black") && shogi.showdeadmark[i] == 1 && !shogi.promotecheck) {
							current = i;
							shogi.showmove = true;
							spriteMoved = false;
							cout << current << endl;
							shogi.deathsprite = true;
							shogi.gambleon = true;
							break;
						}
					}
					if (shogi.yes.getGlobalBounds().contains(mousePos) && shogi.promotecheck) {

						shogi.move = true;
						shogi.ispromoted[current] = 1;
						shogi.promotecheck = false;
					}
					if (shogi.no.getGlobalBounds().contains(mousePos) && shogi.promotecheck) {

						shogi.move = true;
						shogi.promotecheck = false;
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
		if (!Gamestatus) {
			if (gamemodescreen) {
				mode.draw(window, true);
			}
			else {
				menu.draw(window, false);
			}
		}
		if (TutorialScreen == true) {
			window.draw(tutorialSprite);
		}
		else if (Gamestatus) {
			window.draw(backgroud);
			window.draw(shogi.esc);
			window.draw(b);
			for (int i = 0; i < 40; i++)
			{



				if (shogi.dead[i] == 0)
					window.draw(shogi.f[i]);



				if ((shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white") && shogi.ispromoted[i] == 1)
				{
					shogi.f[i].setColor(Color::Magenta);



				}
				else if (shogi.ispromoted[i] == 1)
				{
					shogi.f[i].setColor(Color::Red);


				}
				else if ((shogi.turn % 2 == 0 && shogi.mark[i].second == "black" || shogi.turn % 2 == 1 && shogi.mark[i].second == "white"))
				{
					shogi.f[i].setColor(Color::Color(193, 255, 146, 200));
				}
				else
				{
					shogi.f[i].setColor(Color::White);
				}





			}
			if (shogi.showmove)
			{
				if (shogi.normalsprite)shogi.f[current].setColor(Color::Yellow);




				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (shogi.enermycheck(j, i, current) == "null" && ((shogi.walkcheck(j, i, current) && shogi.normalsprite) || shogi.dropCheck(j, i, current) && shogi.deathsprite) && (!shogi.isPathBlocked(j, i, current) || shogi.deathsprite)) {
							shogi.showmvt[i * 9 + j] = 1;
							window.draw(shogi.mvt[i * 9 + j]);
						}
						else if (shogi.enermycheck(j, i, current) == "ally" && shogi.walkcheck(j, i, current))
						{

						}
						else if (shogi.normalsprite && shogi.enermycheck(j, i, current) == "enemy" && shogi.walkcheck(j, i, current) && !shogi.isPathBlocked(j, i, current))
						{
							shogi.showatk[i * 9 + j] = 1;
							window.draw(shogi.atk[i * 9 + j]);
						}


					}

				}
			}

		}
		shogi.drawpromotecheck(window);
		if (!shogi.move)
		{
			shogi.diecount();

		}
		shogi.drawCapturedPieces(window);
		if (gamemode == 1) {
			if (shogi.gambleon)
			{
				window.draw(shogi.gamble);
			}
		}
		if (escnow) {
			window.draw(overlay);
			window.draw(shogi.restart);
			window.draw(shogi.conti);
			window.draw(shogi.back);
		}


		//cout << current<<showmove;


		window.display();


	}



	return 0;
}