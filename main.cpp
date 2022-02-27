#include<iostream>
#include <conio.h>
#include<windows.h>

using namespace std;
bool gameOver;
int tailX[100], tailY[100];
int nTail;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 1; ++i) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 1; ++i) {
        cout << "#";
    }
    cout << endl;
    cout << "score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'w':
                dir = UP;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2x, prev2y;
    for (int i = 1; i < nTail; i++) {
        prev2x = tailX[i];
        prev2y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2x;
        prevY = prev2y;

    }
    switch (dir) {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;

    }
    if(x >= width) x=0 ; else if(x < 0) x = width - 1;
    if(y >= height ) y=0; else if(y < 0 ) y = height - 1;
    for (int i = 0; i < nTail; ++i) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(5);
    }
    cout << "game over!" << endl;
    return 0;
}
