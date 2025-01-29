#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

const int BOARD_SIZE = 9;
const int CELL_SIZE = 48;
const int WINDOW_WIDTH = BOARD_SIZE * CELL_SIZE;
const int WINDOW_HEIGHT = BOARD_SIZE * CELL_SIZE;

bool showmove = false;
int current = -1;  // Track selected piece

vector<pair<int, int>> startlocation = {
    {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
    {1,1},{7,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},
    {8,8},{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8},
    {7,7},{1,7},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6}
};

Sprite atk[81];
Sprite f[40];
Sprite mvt[81];

void loadTileSprites() {
    int size = 48;
    int k = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            atk[k].setPosition(size * j, size * i);
            mvt[k].setPosition(size * j, size * i);
            k++;
        }
    }
}

bool isValidMove(int x, int y, int id) {
    return (x == startlocation[id].first && y == startlocation[id].second + 1) ||
        (x == startlocation[id].first && y == startlocation[id].second - 1);
}

bool isEnemy(int x, int y, int id) {
    for (int i = 0; i < 40; i++) {
        if (x == startlocation[i].first && y == startlocation[i].second && i != id) {
            return true;
        }
    }
    return false;
}

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shogi Movement");

    Texture boardTex, pieceTex, atkTex, moveTex;
    boardTex.loadFromFile("C:/Users/Loma/Desktop/shogi/board.png");
    pieceTex.loadFromFile("C:/Users/Loma/Desktop/shogi/pawn.png");
    atkTex.loadFromFile("C:/Users/Loma/Desktop/shogi/attacktile.png");
    moveTex.loadFromFile("C:/Users/Loma/Desktop/shogi/moveabletile.png");

    Sprite board(boardTex);

    for (int i = 0; i < 40; i++) {
        f[i].setTexture(pieceTex);
        f[i].setPosition(CELL_SIZE * startlocation[i].first, CELL_SIZE * startlocation[i].second);
    }

    for (int i = 0; i < 81; i++) {
        mvt[i].setTexture(moveTex);
        atk[i].setTexture(atkTex);
    }

    loadTileSprites();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (showmove) {
                    bool moved = false;
                    for (int j = 0; j < 81; j++) {
                        if (mvt[j].getGlobalBounds().contains(mousePos) || atk[j].getGlobalBounds().contains(mousePos)) {
                            Vector2f newPos = mvt[j].getPosition();
                            startlocation[current].first = newPos.x / CELL_SIZE;
                            startlocation[current].second = newPos.y / CELL_SIZE;
                            f[current].setPosition(newPos);
                            showmove = false;
                            moved = true;
                            break;
                        }
                    }

                    if (!moved) {
                        showmove = false; // If no valid move was clicked, cancel move mode
                    }
                }
                else {
                    for (int i = 0; i < 40; i++) {
                        if (f[i].getGlobalBounds().contains(mousePos)) {
                            current = i;
                            showmove = true;
                            break;
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(board);
        for (int i = 0; i < 40; i++) window.draw(f[i]);

        if (showmove) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (isValidMove(j, i, current) && !isEnemy(j, i, current)) {
                        window.draw(mvt[i * 9 + j]);
                    }
                    else if (isEnemy(j, i, current)) {
                        window.draw(atk[i * 9 + j]);
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}
