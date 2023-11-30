#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "apple.h"

namespace n_Snake
{
    enum class Direction
    {
        STOP,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    struct Measure
    {
        int width;
        int height;

        Measure() : width(80), height(20) {}
    };

    class Snake
    {
    private:
        Direction snakeDir;
        int snakeTailX[100];
        int snakeTailY[100];
        int headPosX[100];  
        int headPosY[100];  
        int snakeTailLength;

    public:
        Snake();
        int getLength() const;
        int getSnakeHeadPosX(int index) const;
        int getSnakeHeadPosY(int index) const;
        int getSnakeTailX(int index) const;
        int getSnakeTailY(int index) const;
        void setDirection(Direction newDir);
        void updateGame(n_Apple::getApple& getApple, bool& isGameOver, int& playerScore, Measure& measure);
    };


    class GetDir
    {
    public:
        Direction getUserInput();
    };
}

#endif // SNAKE_H
