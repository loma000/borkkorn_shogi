#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#pragma once
using namespace std;
using namespace sf;

class shogiengine
{
public:

	bool showmove = false;
	vector<pair<int, int>> startlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };


	vector<pair<int, int>> resetlocation = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
											,{1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},



												  {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
											,{7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6} };




	
	vector<pair<string, string>>mark = { {"lance","black" },{"knight","black" },{"silver","black" },{"gold","black" },{"king","black" },{"gold","black" },{"silver","black" },{"knight","black" },{"lance","black" },{"rook","black" }
	,{ "bishop","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },{"pawn","black" },
		{"lance","white"},{"knight","white"},{"silver","white"},{"gold","white"},{"king","white"},{"gold","white"},{"silver","white"},{"knight","white"},{"lance","white"},{"rook","white"}
	,{"bishop","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"},{"pawn","white"} };
	vector<int> pawnid = { -9,-5,-4,-3,-1,-3,-4,-5,-9,-2,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8, 9,5,4,3,1,3,4,5,9,2,7,8,8,8,8,8,8,8,8,8
	};
	Sprite atk[81];


	int amdead[40];
	int  showatk[81];
	int  showmvt[81];
	int dead[40];
	int ispromoted[40];

	Sprite f[40];
	Sprite mvt[81];
	int turn = 1;
	int size = 48;
	bool move = false;
	int borderx = 40;
	int bordery = 40;


	void smoothmove(int);
	void  resetgame();
	bool isPathBlocked(int, int, int);
	void loadsprite();
	void loadtile();
	bool walkcheck(int, int, int);
	bool  occupiedcheck(int, int, int);
	string enermycheck(int, int, int);
	void  promoted(int);



};





void shogiengine::smoothmove(int current) {
	float speed =4;
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

void shogiengine::resetgame() {

	for (int i = 0; i < 40; i++)
	{

		f[i].setPosition(size * resetlocation[i].first + borderx, size * resetlocation[i].second + bordery);
		startlocation[i].first = resetlocation[i].first;
		startlocation[i].second = resetlocation[i].second;
		dead[i] = 0;
		ispromoted[i] = 0;
		turn = 1;
		amdead[i] = 0;
	}



}

bool shogiengine::isPathBlocked(int x, int y, int id) {
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


	if (mark[id].first != "king" && mark[id].first != "gold" && (startlocation[id].second >= 6 && mark[id].second == "black" || startlocation[id].second <= 2 && mark[id].second == "white"))
	{
		ispromoted[id] = 1;
	}




}