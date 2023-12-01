#include "snake.h"
#include <conio.h>
#include <ctime>

namespace n_Snake
{
    int playerScore = 0;
    Direction dir = Direction::STOP;

    Snake::Snake()
    {
        snakeDir = Direction::RIGHT;
        snakeTailLength = 1;

        // Initialize head position (adjust the initialization according to your logic)
        headPosX[0] = 0;
        headPosY[0] = 0;
    }

    int Snake::getLength() const
    {
        return snakeTailLength;
    }

    int Snake::getSnakeHeadPosX(int index) const
    {
        return headPosX[index];
    }

    int Snake::getSnakeHeadPosY(int index) const
    {
        return headPosY[index];
    }

    int Snake::getSnakeTailX(int index) const
    {
        return snakeTailX[index];
    }

    int Snake::getSnakeTailY(int index) const
    {
        return snakeTailY[index];
    }

    void Snake::setDirection(Direction newDir)
    {
        snakeDir = newDir;
    }


    void Snake::updateGame(n_Apple::getApple& getApple, bool& isGameOver, int& playerScore, Measure& measure)
    {
        // Update the position of the snake's tail
        for (int i = snakeTailLength - 1; i > 0; --i)
        {
            snakeTailX[i] = snakeTailX[i - 1];
            snakeTailY[i] = snakeTailY[i - 1];
        }

        switch (snakeDir)
        {
        case Direction::UP:
            headPosY[0]--;
            break;
        case Direction::DOWN:
            headPosY[0]++;
            break;
        case Direction::LEFT:
            headPosX[0]--;
            break;
        case Direction::RIGHT:
            headPosX[0]++;
            break;
        default:
            break;
        }

        // Check for collisions with the walls
        if (headPosX[0] < 0 || headPosX[0] >= measure.width || headPosY[0] < 0 || headPosY[0] >= measure.height)
        {
            isGameOver = true;
            return;
        }

        // Check for collisions with the snake's own tail
        for (int i = 1; i < snakeTailLength; ++i)
        {
            if (snakeTailX[i] == headPosX[0] && snakeTailY[i] == headPosY[0])
            {
                isGameOver = true;
                return;
            }
        }

        // Check if the snake has eaten the apple
        if (headPosX[0] == getApple.getAppleX() && headPosY[0] == getApple.getAppleY())
        {
            // Increase the score and snake length
            playerScore += 1;
            snakeTailLength++;

            // Generate a new random position for the apple
            getApple.generateRandomPosition();
        }

        // Update the position of the first segment of the snake's tail
        snakeTailX[0] = headPosX[0];
        snakeTailY[0] = headPosY[0];
    }
    Direction GetDir::getUserInput()
    {
        Direction newDir = Direction::STOP;
        if (_kbhit())
        {
            
            switch (_getch())
            {
            case 'a':
                newDir = Direction::LEFT;
                break;

            case 's':
                newDir = Direction::DOWN;
                break;

            case 'd':
                newDir = Direction::RIGHT;
                break;

            case 'w':
                newDir = Direction::UP;
                break;

            case 'x':
                newDir = Direction::STOP;
                break;

            default:
                break;
            }
        }
        return newDir;
    }
   
}
