#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include"kaipushpongtai.h"
#include<cstdlib>
#include<ctime>
#include"ui.h"
#pragma once
using namespace std;
using namespace sf;

class shogiengine
{
public:

	bool showmove = false;
	vector<string> moveHistory; // ��������� moveHistory
	void recordMove(std::string moveString); // �����ѧ��ѹ recordMove
	vector<pair<int, int>> startlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };


	vector<pair<int, int>> resetlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},



												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };




	vector<pair<string, string>>markforreset = { {"lance","black" },{"knight","black" },{"silver","black" },{"gold","black" },{"king","black" },{"gold","black" },{"silver","black" },{"knight","black" },{"lance","black" },{"rook","black" }
	,{ "bishop","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },
		{"lance","white"},{"knight","white"},{"silver","white"},{"gold","white"},{"king","white"},{"gold","white"},{"silver","white"},{"knight","white"},{"lance","white"},{"rook","white"}
	,{"bishop","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"} };
	vector<pair<string, string>>mark = { {"lance","black" },{"knight","black" },{"silver","black" },{"gold","black" },{"king","black" },{"gold","black" },{"silver","black" },{"knight","black" },{"lance","black" },{"rook","black" }
	,{ "bishop","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },
		{"lance","white"},{"knight","white"},{"silver","white"},{"gold","white"},{"king","white"},{"gold","white"},{"silver","white"},{"knight","white"},{"lance","white"},{"rook","white"}
	,{"bishop","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"} };
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-2,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,2,7,8,8,8,8,8,8,8,8,8
	};
	vector<int> pawnidforrset = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-2,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,2,7,8,8,8,8,8,8,8,8,8
	};

	vector<int> capturepawnid = { -2,-3,-4,-5,-7,-8,-9, 2,3,4,5,7,8,9 };
	vector<pair<string, string>> deathmark = { {"rook","white"},{"gold","white"},{"silver","white"} ,{ "knight","white" },{"bishop","white"} ,{ "pawn","white" },{"lance","white"}
	,{"rook", "black" },{"gold","black"},{"silver","black"} ,{ "knight","black" },{"bishop","black"} ,{ "pawn","black" },{"lance","black"} };
	int deathcount[14];
	Sprite gamble;
	Sprite atk[81];
	Texture yestex;
	Texture notex;
	Texture promotetex;
	Texture gambletex;
	Sprite yes;
	Sprite no;
	Sprite promote;
	int alreadydead[40];
	int amdead[40];
	int  showatk[81];
	int  showmvt[81];
	int showdeadmark[14];
	int dead[40];
	int ispromoted[40];
	int iscapture[40];
	int isdropped[40];
	bool promotecheck = false;
	Sprite f[40];
	Sprite mvt[81];
	static int turn;
	int size = 48;
	bool move = false;
	int borderx = 70;
	int bordery = 40;
	bool gambleon = false;
	bool normalsprite = false;
	bool deathsprite = false;
	vector<int> capturedPieces;  
	Sprite capturedSprites[40];  
	Sprite capturedSprites2[16];
	void smoothmove(int);
	void resetgame(ui&);
	bool isPathBlocked(int, int, int);
	void loadsprite();
	void loadtile();
	bool walkcheck(int, int, int);
	bool occupiedcheck(int, int, int);
	string enermycheck(int, int, int);
	void promoted(int);
	void capturePiece(int);
	void drawCapturedPieces(RenderWindow&);
	void loadcapturesprite();
	void diecount();
	bool dropCheck(int, int, int);
	void loadtextureyesno(path);
	void drawpromotecheck(RenderWindow&);
	int gamblechange(int);
	Sprite esc;
	Texture esctex;
	Sprite restart;
	Texture restarttex;
	Sprite conti;
	Texture contitex;
	Sprite back;
	Texture backtex;
	Sprite blackwin;
	Texture blackwintex;
	Sprite whitewin;
	Texture whitewintex;
	Sprite number[16];
	Texture numbertex;
};

int shogiengine::turn = 1;
int shogiengine::gamblechange(int id) {
	deathcount[id]--;
	string name = deathmark[id].first;
	string color = deathmark[id].second;
	string namechange;
	int idchange;
	switch (rand() % 8 + 1)
	{
	case 1:
		namechange = "rook";
		idchange = 2;
		break;
	case 2:
		namechange = "gold";
		idchange = 3;
		break;
	case 3:
		namechange = "silver";
		idchange = 4;
		break;
	case 4:
		namechange = "knight";
		idchange = 5;
		break;
	case 5:
		namechange = "bishop";
		idchange = 7;
		break;
	case 6:
		namechange = "pawn";
		idchange = 8;
		break;
	case 7:
		namechange = "lance";
		idchange = 9;
		break;
	case 8:
		return 0;
		break;
	}

	for (int i = 0; i < 14; i++)
	{
		if (deathmark[i].first == namechange && deathmark[i].second == color) {

			deathcount[i]++;
			break;
		}


	}

	for (int i = 0; i < 40; i++)
	{
		if (deathmark[id] == mark[i] && dead[i] == 1) {

			idchange = color == "black" ? idchange * -1 : idchange;
			pawnid[i] = idchange;
			mark[i].first = namechange;
			break;
		}
	}

	return 0;

}
void shogiengine::loadtextureyesno(path  p) {
	gambletex.loadFromFile(p.gambletex);
	yestex.loadFromFile(p.yestexe);
	notex.loadFromFile(p.notexe);
	yes.setTexture(yestex);
	no.setTexture(notex);
	gamble.setTexture(gambletex);
	yes.setPosition(76 + borderx, 196 + bordery);
	no.setPosition(270 + borderx, 196 + bordery);
	gamble.setPosition(575, 415);
	esctex.loadFromFile(p.escape);
	esc.setTexture(esctex);
	esc.setPosition(875 + borderx, 0);
	restarttex.loadFromFile(p.restart);
	restart.setTexture(restarttex);
	restart.setPosition(350 + borderx, 50 + bordery);
	contitex.loadFromFile(p.conti);
	conti.setTexture(contitex);
	conti.setPosition(350 + borderx, 150 + bordery);
	backtex.loadFromFile(p.back);
	back.setTexture(backtex);
	back.setPosition(350 + borderx, 250 + bordery);
	blackwintex.loadFromFile(p.blackwin);
	blackwin.setTexture(blackwintex);
	blackwin.setPosition(300 + borderx, 80 + bordery);
	whitewintex.loadFromFile(p.whitewin);
	whitewin.setTexture(whitewintex);
	whitewin.setPosition(300 + borderx, 80 + bordery);
	promotetex.loadFromFile(p.promotettex);
	promote.setTexture(promotetex);
	promote.setPosition(134 + borderx, 100 + bordery);
}


void shogiengine::drawpromotecheck(RenderWindow& window) {

	if (promotecheck) {
		window.draw(promote);
		window.draw(yes);
		window.draw(no);
	}

}

void shogiengine::smoothmove(int current) {
	float speed = 4;
	Vector2f target(startlocation[current].first * size + borderx, startlocation[current].second * size + bordery);

	Vector2f shogilocate = f[current].getPosition();
	Vector2f direction = target - shogilocate;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 1) {
		direction /= length;

		f[current].move(direction * speed);
	}
	else
	{
		move = false;
		for (int i = 0; i < 40; i++)
		{
			dead[i] = amdead[i];
			f[i].setPosition(size * startlocation[i].first + borderx, size * startlocation[i].second + bordery);
		}
	}
}

void shogiengine::resetgame(ui& ui) {

	for (int i = 0; i < 40; i++)
	{

		f[i].setPosition(size * resetlocation[i].first + borderx, size * resetlocation[i].second + bordery);
		startlocation[i].first = resetlocation[i].first;
		startlocation[i].second = resetlocation[i].second;
		dead[i] = 0;
		ispromoted[i] = 0;
		turn = 1;
		amdead[i] = 0;
		alreadydead[i] = 0;
		mark[i] = markforreset[i];
		pawnid[i] = pawnidforrset[i];

	}
	for (int i = 0;i < 14;i++) { deathcount[i] = 0; }

	promotecheck = false;
	for (int i = 0; i < 81; i++)
	{
		showmvt[i] = 0;
		showatk[i] = 0;
	}
	turn = 1;
	normalsprite = false;
	deathsprite = false;
	moveHistory.clear();
	ui.loadtext();
	loadsprite();
}

bool shogiengine::isPathBlocked(int x, int y, int id) {
	string piece = mark[id].first;
	string color = mark[id].second;
	int sx = startlocation[id].first, sy = startlocation[id].second;

	  
	if (piece == "rook" || piece == "bishop" || ispromoted[id] == 1) {
		 
		if (piece == "bishop" && ispromoted[id] == 1) {
			if (abs(x - sx) <= 1 && abs(y - sy) <= 1) {
				return false;  
			}
		}
		 
		if (piece == "rook" && ispromoted[id] == 1) {
			if (abs(x - sx) == 1 && abs(y - sy) == 1) {
				return false; 
			}
		}

		 
		int dx = (x > sx) ? 1 : (x < sx) ? -1 : 0;
		int dy = (y > sy) ? 1 : (y < sy) ? -1 : 0;

		 
		if ((piece == "bishop" || (piece == "bishop" && ispromoted[id] == 1)) && abs(x - sx) != abs(y - sy)) {
			return true; 
		}
		if ((piece == "rook" || (piece == "rook" && ispromoted[id] == 1)) && dx != 0 && dy != 0) {
			return true;  
		}

		 
		int cx = sx + dx, cy = sy + dy;
		while (cx != x || cy != y) {
			for (int i = 0; i < 40; i++) {
				if (startlocation[i].first == cx && startlocation[i].second == cy && dead[i] == 0) {
					return true;  
				}
			}
			cx += dx;
			cy += dy;
		}
	}

 
	if (piece == "lance" && ispromoted[id] == 0) {
		int dir = (color == "black") ? 1 : -1; 
		int cy = sy + dir;  
		while (cy != y) {
			for (int i = 0; i < 40; i++) {
				if (startlocation[i].first == sx && startlocation[i].second == cy && dead[i] == 0) {
					return true;  
				}
			}
			cy += dir;  
		}
	}

	return false;  
}





void shogiengine::loadsprite() {


	for (int i = 0; i < 40; i++)
	{
		int n = pawnid[i];
		int x = abs(n) - 1;
		int y = n > 0 ? 1 : 0;
		f[i].setTextureRect(IntRect(size * x, size * y, size, size));
		f[i].setPosition(size * startlocation[i].first + borderx, size * startlocation[i].second + bordery);
	}

}

void shogiengine::loadtile() {

	int k = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			atk[k].setPosition(size * j + borderx, size * i + bordery);
			mvt[k].setPosition(size * j + borderx, size * i + bordery);
			k++;
		}

	}



}
bool shogiengine::walkcheck(int x, int y, int id) {
	string piece = mark[id].first;
	string color = mark[id].second;
	int sx = startlocation[id].first, sy = startlocation[id].second;

	 
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
	return false;

}

bool  shogiengine::occupiedcheck(int x, int y, int id) {
	bool occupied;




	for (int i = 0; i < 40; i++)
	{
		if (x == startlocation[i].first && y == startlocation[i].second) {

			occupied = false;
			break;
		}
		else occupied = true;

	}



	return  occupied;

}

string shogiengine::enermycheck(int x, int y, int id) {
	string enermy;


	for (int i = 0; i < 40; i++)
	{

		if (mark[i].second != mark[id].second && x == startlocation[i].first && y == startlocation[i].second && dead[i] == 0) {
			enermy = "enemy";
			break;
		}
		else if (mark[i].second == mark[id].second && x == startlocation[i].first && y == startlocation[i].second && dead[i] == 0)
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
void shogiengine::promoted(int id) {
	if ((mark[id].first == "knight" || mark[id].first == "lance" || mark[id].first == "pawn") && (startlocation[id].second >= 8 && mark[id].second == "black" || startlocation[id].second <= 0 && mark[id].second == "white") && ispromoted[id] == 0)
	{
		ispromoted[id] = 1;
		move = true;
	}
	else

		if (mark[id].first != "king" && mark[id].first != "gold" && (startlocation[id].second >= 6 && mark[id].second == "black" || startlocation[id].second <= 2 && mark[id].second == "white") && ispromoted[id] == 0)
		{
			promotecheck = true;
		}
		else
		{
			move = true;
		}
}




void shogiengine::capturePiece(int index) {

	for (int i = 0; i < 40; i++)
	{
		if (dead[i] == 1 && iscapture[i] == 0) {
			capturedPieces.push_back(i);
			iscapture[i] = 1;
			cout << "Piece " << i << " captured!" << endl;
		}
	}


}

void shogiengine::drawCapturedPieces(RenderWindow& window) {


	for (int i = 0; i < 14; i++)
	{

		if (deathcount[i] > 0)
		{

			showdeadmark[i] = 1;
			window.draw(capturedSprites2[i]);window.draw(number[i]);loadcapturesprite();
		}
		else showdeadmark[i] = 0;

	}
}
void shogiengine::diecount() {
	for (int i = 0;i < 40;i++) {
		for (int j = 0; j < 14; j++)
		{
			if (dead[i] == 1 && mark[i] == deathmark[j] && alreadydead[i] == 0)
			{
				alreadydead[i] = 1;
				deathcount[j]++;
				break;
			}
		}
	}



}

void shogiengine::loadcapturesprite() {

	for (int i = 0; i < 14; i++)
	{
		int n = capturepawnid[i];
		int x = abs(n) - 1;
		int y = i < 7 ? 0 : 1;
		int yy = deathcount[i] < 10 ? 0 : 1;
		capturedSprites2[i].setTextureRect(IntRect(size * x, size * y, size, size));

		if (deathcount[i] < 10)
		{
			number[i].setTextureRect(IntRect(size * (deathcount[i] - 1), size * yy, size, size));

		}
		else {

			number[i].setTextureRect(IntRect(size * (deathcount[i] - 10), size * yy, size, size));

		}
		if (i < 7)
		{
			capturedSprites2[i].setPosition(borderx - size, size * i + bordery);
			number[i].setPosition(borderx - size, size * i + bordery);

		}
		else
		{
			number[i].setPosition(borderx + size * 9, size * (i - 7) + bordery + 2 * size);
			capturedSprites2[i].setPosition(borderx + size * 9, size * (i - 7) + bordery + 2 * size);
		}
	}
}
bool shogiengine::dropCheck(int x, int y, int pieceIndex) {
	 
	if (x < 0 || x >= 9 || y < 0 || y >= 9)
		return false;

	 
	for (int i = 0; i < 40; i++) {
		if (dead[i] == 0 && startlocation[i].first == x && startlocation[i].second == y) {
			return false;  
		}
	}

	 
	 
	 
	string piece, color;
	if (deathsprite) {
		piece = deathmark[pieceIndex].first;
		color = deathmark[pieceIndex].second;
	}
	else {
		piece = mark[pieceIndex].first;
		color = mark[pieceIndex].second;
	}

	 
	if (piece == "pawn" || piece == "lance") {
		if ((color == "black" && y == 0) || (color == "white" && y == 8))
			return false;
	}
	 
	if (piece == "knight") {
		if ((color == "black" && y <= 1) || (color == "white" && y >= 7))
			return false;
	}

 
	if (piece == "pawn") {
		for (int i = 0; i < 40; i++) {
			if (dead[i] == 0 && mark[i].first == "pawn" && mark[i].second != color && ispromoted[i] == 0) {
				if (startlocation[i].first == x)
					return false;
			}
		}
	}
	 
	isdropped[pieceIndex] = 0;
	return true;


}
 
void shogiengine::recordMove(string moveString) {
	int currentTurn = (turn + 1) / 2; 
	string playerColor = (turn % 2 != 0) ? "Black" : "White";
	 
	if (turn % 2 == 0) { 
		cout << "\n======== Turn " << currentTurn << " ========\n";  
	}
	cout << "   " << playerColor << ": " << moveString << endl; 

	moveHistory.insert(moveHistory.begin(), moveString);
}
 