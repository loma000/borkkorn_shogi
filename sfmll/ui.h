#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include"shogiengine.h"
#include"kaipushpongtai.h"
using namespace std;
#define Menu_Items 3
#define Mode_Items 4
using namespace sf;
#pragma once

class ui
{
private:
	Font font;
	Text menu[Menu_Items];
	Text mode[Mode_Items];
public:
	 

	ui(float width, float height);
	

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

