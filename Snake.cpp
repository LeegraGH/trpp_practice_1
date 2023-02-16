#include <iostream>
#include <conio.h> // берем из библиотеки функцию, котора позволит отслеживать, что нажал пользователь
#include <ctime> 
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 40; // ширина поля
const int heigth = 20; // длина поля
int x, y, fruitX, fruitY, fruitX1, fruitY1, score, bonusX, bonusY, k=0;
int tailX[100], tailY[100]; // координаты хвоста по x и y
int nTail; // количество элементов в хвосте
enum eDirection { STOP = 0, LEFT, RIGHT, DOWN, UP };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = heigth / 2 - 1;
    fruitX = rand() % (width - 3) + 1;
    fruitY = rand() % (heigth - 1) + 1;
    fruitX1 = rand() % (width - 3) + 1;
    fruitY1 = rand() % (heigth - 1) + 1;
    /*bonusX = rand() % (width - 3) + 1;
    bonusY = rand() % (heigth - 1) + 1;*/
    score = 0;
}

void Draw()
{
    system("cls"); // очистка терминала при каждом запуске ф-ии Draw
    for (int i=0;i<width;i++) cout << "*";
    cout << endl;

    for (int i = 0; i < heigth; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width-2) cout << "*";
            if (i == y && j == x)
            {
                cout << "O";
            }
            else if ((i == fruitY && j == fruitX) || (i == fruitY1 && j == fruitX1) && fruitY!=fruitY1 && fruitX!=fruitX1)
            {
                cout << "F";
            }
            else if (i == bonusY && j == bonusX && k>=4)
            {
                cout << "B";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == (j - 1) && tailY[k] == (i - 1))
                    {
                        print = true;
                        cout << "o";
                    }
                }
                if(!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input()
{
    if (_kbhit()) // _kbhit() возвращает true, если пользователь нажал на какую то кнопку
    {
        switch (_getch()) // _getch() определяет, какую именно клавишу нажал пользователь
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'z':
            dir = STOP;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x-1;
    tailY[0] = y-1;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    case UP:
        y--;
        break;
    }

    //if ((x > width) || (x < 0) || (y > heigth) || (y < 0)) gameOver = true;
    if (x < 0) x = width - 3;
    if (x > (width-3)) x = 1;
    if (y < 0) y = heigth - 1;
    if (y > heigth) y = 0;
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == (x - 1) && tailY[i] == (y - 1)) gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        k += 1;
        fruitX = rand() % (width - 3) + 1;
        fruitY = rand() % (heigth - 1) + 1;
        nTail++;
    }
    if (x == fruitX1 && y == fruitY1)
    {
        score += 10;
        k += 1;
        fruitX1 = rand() % (width - 3) + 1;
        fruitY1 = rand() % (heigth - 1) + 1;
        nTail++;
    }
    if (x == bonusX && y == bonusY)
    {
        score += 40;
        bonusX = rand() % (width - 3) + 1;
        bonusY = rand() % (heigth - 1) + 1;
        k = 0;
        nTail += 4;
    }
}

int main()
{
    srand(time(NULL));
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep (20);
    }
    return 0;
}
