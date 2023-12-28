#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <deque>   
#include <iterator> 
#include <conio.h>
#include <windows.h>

using namespace std;

struct coordinates;

enum moving { STOP = 0, LEFT, RIGHT, DOWN, UP };
moving direction;

bool gameOver;
bool refresh;
const int SNAKEHEAD = 0;
const int ROWS = 10;
const int COLS = 10;
const char APPLEDRAW = '@';
const char SNAKEDRAW = '0';
const char MAPDRAW = '.';

struct coordinates
{
    int x;
    int y;
};

int appleX, appleY;
int score = 2;
vector<vector<char>> map;
deque<coordinates> snake; 

coordinates coord;

void Initialization() {
    gameOver = false;
    coord.x = ROWS / 2;
    coord.y = COLS / 2;
    snake.push_back(coord);
    coord.x = (ROWS / 2) + 1;
    snake.push_back(coord);
    appleY = rand() % ROWS;
    appleX = rand() % COLS;
    score = 2;
    direction = LEFT;
}

void Draw() {

    system("cls");
    for (int i = 0; i < ROWS; i++) {
        vector<char> row;
        for (int j = 0; j < COLS; j++)
        {
            // Проверка, является ли текущая ячейка частью змейки
            bool isSnakeSegment = false;
            for (const auto& segment : snake) {
                if (segment.x == j && segment.y == i) {
                    row.push_back(SNAKEDRAW);
                    isSnakeSegment = true;
                    break;
                }
            }

            if (!isSnakeSegment) {
                if (i == appleY && j == appleX) {
                    row.push_back(APPLEDRAW);
                }
                else {
                    row.push_back(MAPDRAW);
                }
            }
        }
        map.push_back(row);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        }
    }
}

void Logic() {
    coordinates newHead = snake.front();
    switch (direction)
    {
    case LEFT:
        newHead.x--;
        break;
    case RIGHT:
        newHead.x++;
        break;
    case DOWN:
        newHead.y++;
        break;
    case UP:
        newHead.y--;
        break;
    case 'r':
        gameOver = true;
        break;
    }

    for (const auto& segment : snake) {
        if (newHead.x == segment.x && newHead.y == segment.y or (newHead.x == -1) or (newHead.x == 10) or (newHead.y == 10) or (newHead.y == -1)) {
            // Столкновение с самой собой
            gameOver = true;
            break;
        }
    }



    snake.push_front(newHead);


    // Проверка столкновения с яблоком
    if (newHead.x == appleX && newHead.y == appleY) {
        score++;
        if (score == ROWS * COLS) {
            gameOver = true;
            cout << "WIN!" << endl;
        }
        appleY = rand() % ROWS;
        appleX = rand() % COLS;
    }
    else {
        snake.pop_back();
    }
} 

int main() {
    Initialization();
     while (!gameOver) {
        Draw();
        Input();
        Logic();
        map.clear();
        Sleep(350);         
    } 
    return 0;
}
