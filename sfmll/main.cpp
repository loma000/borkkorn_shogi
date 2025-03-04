
#include"shogiengine.h"
#include"ui.h"
#include"kaipushpongtai.h"
#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <thread>
#include <atomic>
#include <iomanip> 
#include <sstream> 









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
	//history and text
	string movedPieceName;
	string moveString;
	string moveStringgam;
	//mainmenu
	Texture menu_bg;
	menu_bg.loadFromFile(path.menu_bg);
	Sprite menu_bgs;
	menu_bgs.setTexture(menu_bg);
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

	//winner

	sf::Font font;
	font.loadFromFile("Minecraft.ttf");
	Text popup;
	popup.setFont(font);
	popup.setString("Press R to Restart!");
	popup.setFillColor(Color::White);
	popup.setCharacterSize(26);
	popup.setPosition(400, 320);


	bool isblackwin = false;
	bool iswhitewin = false;
	//tutorial
	Sprite tutorialSprite;
	int tutorialPage = 0;
	tutorialSprite.setTexture(textures[tutorialPage]);

	shogi.numbertex.loadFromFile(path.texnumber);
	bool Gamestatus = false;
	bool TutorialScreen = false;
	for (int i = 0; i < 40; i++)
	{
		shogi.f[i].setTexture(item);

	}
	for (int i = 0; i < 16; i++)
	{

		shogi.number[i].setTexture(shogi.numbertex);
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
	ui mode(window.getSize().x, window.getSize().y);

	mode.loadtext();
	thread bgmThread(loopSound); //play background music
	bgmThread.detach();
	//time
	Clock clock1;
	Clock clock2;
	float countdownTime1 = 1200.99f;
	float countdownTime2 = 1200.99f;
	bool timerActive1 = true;
	bool timerActive2 = false;



	Font font1;
	if (!font1.loadFromFile("Roboto-Black.ttf"))  // ตรวจสอบพาธให้ถูกต้อง
	{
		std::cerr << "Error loading font!" << std::endl;
		return -1;
	}
	Text countdownText1;
	countdownText1.setFont(font1);
	countdownText1.setCharacterSize(30);
	countdownText1.setFillColor(sf::Color::Black);
	countdownText1.setPosition(578, 426);  // กำหนดตำแหน่งของข้อความบนหน้าจอ

	FloatRect textBounds1 = countdownText1.getLocalBounds();
	RectangleShape textBorder1(sf::Vector2f(textBounds1.width + 148, textBounds1.height + 50));
	textBorder1.setFillColor(sf::Color::White); // โปร่งใส
	textBorder1.setOutlineThickness(1);              // ความหนาของเส้นกรอบ
	textBorder1.setOutlineColor(sf::Color::Black);
	textBorder1.setPosition(countdownText1.getPosition().x - 5, countdownText1.getPosition().y - 5);

	Text countdownText2;
	countdownText2.setFont(font1);
	countdownText2.setCharacterSize(30);
	countdownText2.setFillColor(sf::Color::Black);
	countdownText2.setPosition(578, 46);  // กำหนดตำแหน่งของข้อความบนหน้าจอ

	FloatRect textBounds2 = countdownText2.getLocalBounds();
	RectangleShape textBorder2(sf::Vector2f(textBounds2.width + 148, textBounds2.height + 50));
	textBorder2.setFillColor(sf::Color::White); // โปร่งใส
	textBorder2.setOutlineThickness(1);              // ความหนาของเส้นกรอบ
	textBorder2.setOutlineColor(sf::Color::Black);
	textBorder2.setPosition(countdownText2.getPosition().x - 5, countdownText2.getPosition().y - 5);


	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::R)) {
				shogi.resetgame(mode);
				countdownTime1 = 1200.99f;
				countdownTime2 = 1200.99f;
				isblackwin = false;
				iswhitewin = false;
			}
			if (Gamestatus == true) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					escnow = true;
					isblackwin = false;
					iswhitewin = false;
				}
			}
			if (event.type == Event::MouseMoved) {

				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF = window.mapPixelToCoords(mousePosition);


				if (!gamemodescreen) {
					menu.updateMenuHover(mousePosF, false);  // Update hover effect
				}
				else {
					mode.updateMenuHover(mousePosF, true);
				}
			}


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				if (!Gamestatus && !gamemodescreen) { // Menu screen
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
						gamemode = 3;
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


				else if (Gamestatus == true) {
					if (shogi.esc.getGlobalBounds().contains(mousePos)) {
						escnow = true;
						isblackwin = false;
						iswhitewin = false;
					}

					if (shogi.conti.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
					}
					if (shogi.restart.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
						countdownTime1 = 1200.99f;
						countdownTime2 = 1200.99f;
						shogi.resetgame(mode);

					}
					if (shogi.back.getGlobalBounds().contains(mousePos) && escnow == true) {
						escnow = false;
						Gamestatus = false;
						countdownTime1 = 1200.99f;
						countdownTime2 = 1200.99f;
						timerActive1 = false;
						timerActive2 = false;
						shogi.resetgame(mode);
					}
					if (escnow == false) {


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
											shogi.amdead[i] = 1;
											//cout << shogi.mark[i].first << " " << i << " dead" << endl;
											shogi.ispromoted[i] = 0;

											break;
										}
									}

									int first = shogi.startlocation[current].first;
									int second = shogi.startlocation[current].second;
									shogi.normalsprite = false;
									shogi.startlocation[current].first = x;
									shogi.startlocation[current].second = y;
									//f[current].setPosition(size * startlocation[current].first, size * startlocation[current].second);
									shogi.promoted(current);
									bool isPromotedMove = shogi.ispromoted[current] == 1;
									//cout << current << " " << shogi.ispromoted[current] << endl;
									shogi.showatk[j] = 0;
									//cout << "isclickatk";
									PlaySound(TEXT("asset/capture.wav"), NULL, SND_FILENAME | SND_ASYNC);
									shogi.turn++;
									spriteMoved = true;
									// ---       ǹ      ͺѹ ֡    ѵ  ---
									string movedPieceName = shogi.mark[current].first;
									pair<int, int> startLocation = shogi.startlocation[current];
									pair<int, int> endLocation;
									Vector2f atkPosition = shogi.atk[j].getPosition(); //     ͵           ͤ    Ѵਹ
									endLocation.first = int((atkPosition.x - shogi.borderx) / shogi.size);
									endLocation.second = int((atkPosition.y - shogi.bordery) / shogi.size);
									string capturedPieceName = "";
									for (int i = 0; i < 40; i++) { //  Ҫ     ҡ   ١ Թ
										if (endLocation.first == shogi.startlocation[i].first && endLocation.second == shogi.startlocation[i].second && shogi.dead[i] == 0) {
											capturedPieceName = shogi.mark[i].first;
											break;
										}
									}

									moveString = (shogi.turn % 2 == 0 ? "White" : "Black"); //   Ѻ   Թ    
									if (isPromotedMove) {
										moveString += " " + movedPieceName + " (Promote) From (" + to_string(first + 1) + "," + to_string(second + 1) + ") To (" + to_string(endLocation.first + 1) + "," + to_string(endLocation.second + 1) + ")";
									}
									else {
										moveString += " " + movedPieceName + " From (" + to_string(first + 1) + "," + to_string(second + 1) + ") To (" + std::to_string(x + 1) + "," + std::to_string(y + 1) + ")";
									}
									if (!capturedPieceName.empty()) {
										moveString += " and Slay " + capturedPieceName;
									}
									if (!shogi.promotecheck) { shogi.recordMove(moveString); }
									// ---     ǹ        ---

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

												//cout << shogi.deathcount[current];
												current = i;
												shogi.loadsprite();
												break;
											}
										}
									}
									int first = shogi.startlocation[current].first;
									int second = shogi.startlocation[current].second;
									shogi.startlocation[current].first = (position.x - shogi.borderx) / shogi.size;
									shogi.startlocation[current].second = (position.y - shogi.bordery) / shogi.size;
									if (shogi.normalsprite)
									{

										shogi.promoted(current);
									}
									else
									{
										//cout << "sus";
										shogi.f[current].setPosition(shogi.size * shogi.startlocation[current].first + shogi.borderx, shogi.size * shogi.startlocation[current].second + shogi.bordery);
									}

									//cout << current << " " << shogi.ispromoted[current] << endl;
									shogi.showmvt[k] = 0;
									shogi.normalsprite = false;
									//cout << "isclickmvt";
									PlaySound(TEXT("asset/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
									shogi.turn++;
									spriteMoved = true;

									// ---  ѹ ֡    ѵ  ---
									movedPieceName = shogi.mark[current].first;
									pair<int, int> startLocation = shogi.startlocation[current];
									pair<int, int> endLocation;
									Vector2f mvtPosition = shogi.mvt[k].getPosition(); //     ͵           ͤ    Ѵਹ
									endLocation.first = int((mvtPosition.x - shogi.borderx) / shogi.size);
									endLocation.second = int((mvtPosition.y - shogi.bordery) / shogi.size);
									bool isPromotedMove = shogi.ispromoted[current] == 1;

									moveString = (shogi.turn % 2 == 0 ? "White" : "Black"); //   Ѻ   Թ    

									if (isPromotedMove) {
										moveString += " " + movedPieceName + " (Promote) From (" + to_string(first + 1) + "," + to_string(second + 1) + ") To (" + to_string(endLocation.first + 1) + "," + to_string(endLocation.second + 1) + ")";
									}
									else if (shogi.deathsprite == true) {
										moveString += " " + movedPieceName + " Revive at (" + to_string(endLocation.first + 1) + "," + to_string(endLocation.second + 1) + ")";
									}
									else {
										moveString += " " + movedPieceName + " From (" + to_string(first + 1) + "," + to_string(second + 1) + ") To (" + to_string(endLocation.first + 1) + "," + to_string(endLocation.second + 1) + ")";
									}
									if (!shogi.promotecheck) { shogi.recordMove(moveString); }
									shogi.deathsprite = false;
									// ---     ǹ        ---

									break;

								}
							}
						}
						if (shogi.gamble.getGlobalBounds().contains(mousePos) && shogi.gambleon && gamemode == 1) {
							shogi.turn++;
							PlaySound(TEXT("asset/button1.wav"), NULL, SND_FILENAME | SND_ASYNC);
							shogi.gamblechange(current);
							if (shogi.gambleon == true) {
								moveStringgam = (shogi.turn % 2 == 0 ? "White" : "Black");
								moveStringgam += " " + movedPieceName + " is gamble and got something";
								if (!shogi.promotecheck)shogi.recordMove(moveStringgam);
							}
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
								//cout << shogi.dead[i] << endl;
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
								//cout << current << endl;
								shogi.deathsprite = true;
								shogi.gambleon = true;
								break;
							}
						}
						if (shogi.yes.getGlobalBounds().contains(mousePos) && shogi.promotecheck) {

							shogi.move = true;
							shogi.ispromoted[current] = 1;
							moveString += " and Promote";
							shogi.recordMove(moveString);
							shogi.promotecheck = false;
						}
						if (shogi.no.getGlobalBounds().contains(mousePos) && shogi.promotecheck) {

							shogi.move = true;
							moveString += " and no Promote";
							shogi.recordMove(moveString);
							shogi.promotecheck = false;
						}

					}




				}
			}





		}
		//time
		if (Gamestatus == true) {
			Time elapsed1 = clock1.getElapsedTime();
			Time elapsed2 = clock2.getElapsedTime();
			int t1 = elapsed1.asSeconds();
			int t2 = elapsed2.asSeconds();

			if (escnow == false && isblackwin == false && iswhitewin == false) {
				if (shogi.turn % 2 == 0)
				{

					timerActive1 = false;
					timerActive2 = true;
				}
				else if (shogi.turn % 2 == 1)
				{

					timerActive1 = true;
					timerActive2 = false;


				}if (timerActive1 == true) {
					if (t1 / 1 == 1) {
						countdownTime1 -= elapsed1.asSeconds();
						clock1.restart();
					}

				}
				else if (timerActive1 == false) {
					clock1.restart();

				}
				if (timerActive2 == true) {
					if (t2 / 1 == 1) {
						countdownTime2 -= elapsed2.asSeconds();
						clock2.restart();
					}

				}
				else if (timerActive2 == false) {
					clock2.restart();

				}if (countdownTime1 < 0.99f) {
					timerActive1 = false;
					isblackwin = true;

				}
				else if (countdownTime2 < 0.99f) {
					timerActive2 = false;
					iswhitewin = true;
				}

			}
			else {
				timerActive1 = false;
				timerActive2 = false;
			}



			int minutes1 = static_cast<int>(countdownTime1) / 60;
			int seconds1 = static_cast<int>(countdownTime1) % 60;
			int minutes2 = static_cast<int>(countdownTime2) / 60;
			int seconds2 = static_cast<int>(countdownTime2) % 60;
			stringstream timeStream1;
			timeStream1 << minutes1 << ":" << setw(2) << setfill('0') << seconds1;  // ใช้ setw ที่ seconds1
			stringstream timeStream2;
			timeStream2 << minutes2 << ":" << setw(2) << setfill('0') << seconds2;

			countdownText1.setString("P1:  " + std::to_string(minutes1) + ":" + std::to_string(seconds1));
			countdownText2.setString("P2:  " + std::to_string(minutes2) + ":" + std::to_string(seconds2));


		}

		for (int i = 0;i < 40;i++) {
			if (shogi.dead[i] == 1 && shogi.mark[i].first == "king") {
				if (shogi.mark[i].second == "white") {
					if (escnow) {
						isblackwin = false;
					}
					else {
						isblackwin = true;
					}
				}
				else {
					if (escnow) {
						iswhitewin = false;
					}
					else {
						iswhitewin = true;
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
				window.draw(menu_bgs);
				mode.draw(window, true);
			}
			else {
				window.draw(menu_bgs);
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


		mode.deawtext(window, Gamestatus, shogi.moveHistory);
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
		if (gamemode == 3) {
			window.draw(textBorder1);  // วาดกรอบก่อนข้อความ
			window.draw(countdownText1);
			window.draw(textBorder2);  // วาดกรอบก่อนข้อความ
			window.draw(countdownText2);
		}
		if (escnow) {
			window.draw(overlay);
			window.draw(shogi.restart);
			window.draw(shogi.conti);
			window.draw(shogi.back);
		}

		if (isblackwin) {
			window.draw(overlay);
			window.draw(shogi.blackwin);
			window.draw(popup);
		}
		if (iswhitewin) {
			window.draw(overlay);
			window.draw(shogi.whitewin);
			window.draw(popup);

		}


		//cout << current<<showmove;


		window.display();


	}



	return 0;
}