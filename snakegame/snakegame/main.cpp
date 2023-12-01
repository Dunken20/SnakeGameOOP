#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include "snake.h"
#include "apple.h"

int playerScore = 0;
int x, y;

n_Snake::GetDir dirInstance;

void render(std::string playerName, n_Apple::getApple& apple, n_Snake::Snake& snakePlayer, n_Snake::GetDir& dirInstance)
{
    system("cls");
    n_Snake::Measure gameMes;

    for (int i = 0; i < gameMes.width + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << '\n';

    // Inside the rendering loop
    for (int i = 0; i < gameMes.height; i++)
    {
        for (int j = 0; j <= gameMes.width; j++)
        {
            if (j == 0 || j == gameMes.width)
            {
                std::cout << "|";
            }

            // Check if the current position is the snake's head
            if (i == snakePlayer.getSnakeHeadPosY(0) && j == snakePlayer.getSnakeHeadPosX(0))
            {
                std::cout << "O"; // snake's head
            }
            else
            {
                bool prTail = false;
                for (int k = 0; k < snakePlayer.getLength(); ++k)
                {
                    // Check if the current position is any part of the snake's tail
                    if (snakePlayer.getSnakeTailX(k) == j && snakePlayer.getSnakeTailY(k) == i)
                    {
                        std::cout << "o"; // snake's tail
                        prTail = true;
                    }
                }

                // Check if the current position is not part of the snake or an apple
                if (!prTail && !(i == apple.getAppleY() && j == apple.getAppleX()))
                {
                    std::cout << " ";
                }
            }

            // Check if the current position is an apple
            if (i == apple.getAppleY() && j == apple.getAppleX())
            {
                std::cout << "*"; // apple
            }
        }
        std::cout << '\n';
    }

    for (int i = 0; i < gameMes.width + 2; i++)
    {
        std::cout << "-"; // bottom layer
    }
    std::cout << "\n";

    std::cout << playerName << " score: " << playerScore << "\n";

    // Get user input or handle game logic here
    n_Snake::Direction dir = dirInstance.getUserInput();
    snakePlayer.setDirection(dir);

}

class getStats
{
private:
    std::string getPlayerName;
    std::vector<std::string> getLeaderBoard;

public:
    // Constructor
    getStats(std::string playerName, std::vector<std::string> leaderBoard);

    // Function to save the score to a file
    void saveToFile(std::string& saveName)
    {
        std::fstream file;
        file.open("Stats.txt", std::fstream::app);
        if (file.is_open())
        {
            file << saveName;
            file.close();
        }
    }

    // Function to update the leaderboard with a new score
    bool score(std::string& player, int playerScore)
    {
        std::string entry = player + " " + std::to_string(playerScore);

        getLeaderBoard.push_back(entry);

        std::sort(getLeaderBoard.begin(), getLeaderBoard.end(), [](const std::string& a, const std::string& b) {
            // the score is separated from the player name by a space
            size_t posA = a.find_last_of(' ');
            size_t posB = b.find_last_of(' ');

            // Extract the scores and compare them
            int scoreA = std::stoi(a.substr(posA + 1));
            int scoreB = std::stoi(b.substr(posB + 1));

            return scoreA > scoreB;
            });

        return true;
    }
};

// Implementation of the constructor
getStats::getStats(std::string playerName, std::vector<std::string> leaderBoard)
{
    // Initialize the class members
    getPlayerName = playerName;
    getLeaderBoard = leaderBoard;
}

int main()
{
    int gameWidth = 45;
    int gameHeight = 25;

    n_Apple::getApple apple(gameWidth, gameHeight);
    n_Snake::Snake snakePlayer;

    n_Snake::Measure gameMes;  // Initialize gameMes
    x = gameMes.width / 2;
    y = gameMes.height / 2;
    playerScore = 0;
    bool isGameOver = false;

 

    apple.generateRandomPosition();


    while (true)
    {
        n_Snake::Direction dir = dirInstance.getUserInput();
        snakePlayer.setDirection(dir);

        // Update snake position
        snakePlayer.updateGame(apple, isGameOver, playerScore, gameMes);

        // Render the game
        render("player1", apple, snakePlayer, dirInstance);

        // Update playerScore 
        if (playerScore >= 100)
            break;

        Sleep(100);
    }

    return 0;
}
