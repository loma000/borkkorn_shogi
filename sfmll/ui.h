#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include"shogiengine.h"
#include"kaipushpongtai.h"
using namespace std;
#define Max_Items 3
using namespace sf;
#pragma once

class ui
{
private:
	Font font;
	Text menu[Max_Items];
public:
	 

	ui(float width, float hiehgt);

	void draw(RenderWindow& window);
	bool isPlayClicked(Vector2f mousePos);
	bool isTutorialClicked(Vector2f mousePos);
	bool isExitClicked(Vector2f mousePos);
};

