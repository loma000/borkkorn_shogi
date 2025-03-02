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


ui::ui(float width, float height)
{
	if (!font.loadFromFile("Roboto_Black.ttf")) {
		///for handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
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
	mode[0].setFillColor(Color::White);
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

void ui::updateMenuHover(Vector2f mousePos, bool showmode) {
	if (!showmode) {
		for (int i = 0; i < Menu_Items; i++) {
			if (menu[i].getGlobalBounds().contains(mousePos)) {
				menu[i].setFillColor(sf::Color::Red); // Change color on hover
			}
			else {
				menu[i].setFillColor(sf::Color::White); // Reset to white when not hovering
			}
		}
	}
	else {
		for (int i = 0; i < Mode_Items; i++) {
			if (mode[i].getGlobalBounds().contains(mousePos)) {
				mode[i].setFillColor(sf::Color::Red); // Change color on hover
			}
			else {
				mode[i].setFillColor(sf::Color::White); // Reset to white when not hovering
			}
		}
	}
}
