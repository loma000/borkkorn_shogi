#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
 
#include"kaipushpongtai.h"
using namespace std;
#define Menu_Items 3
#define Mode_Items 4
using namespace sf;
#pragma once

class ui
{
private:
	Text replay[8];
	Font font;
	Text menu[Menu_Items];
	Text mode[Mode_Items];
public:
	 

	ui(float width, float height);
	
	void deawtext(RenderWindow&, bool,vector<string> &);
	void loadtext();
	void draw(RenderWindow& window, bool showMode);
	bool isPlayClicked(Vector2f mousePos);
	bool isNormalclicked(Vector2f mousePos);
	bool isGambleClicked(Vector2f mousePos);
	bool isgamemode3clicked(Vector2f mousePos);
	bool isTutorialClicked(Vector2f mousePos);
	bool isExitClicked(Vector2f mousePos);
	bool isBackClicked(Vector2f mousePos);
	void updateMenuHover(Vector2f mousePos,bool showmode);
};

void ui::loadtext() {


	for (int i = 0; i < 8; i++)
	{
		replay[i].setFont(font);
		replay[i].setFillColor(Color::Black);

		replay[i].setCharacterSize(15);
		replay[i].setString( "");
		replay[i].setPosition(625, 60 + 47 * i);
	}



}

void ui::deawtext(RenderWindow& window, bool gamemode, vector<string>& history) {


	for (int i = 0; i < history.size()       &&  i < 8 ; i++)
	{
		replay[i].setString(history[i]);
	}


	for (int i = 0; i < 8 && gamemode; i++)
	{



		window.draw(replay[i]);
	}



}