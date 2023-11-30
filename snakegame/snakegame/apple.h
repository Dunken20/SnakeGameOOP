#include <random>
#include <chrono>

#ifndef APPLE_H
#define APPLE_H

namespace n_Apple
{
    class getApple
    {
    public:
        getApple(int gameWidth, int gameHeight) : width(gameWidth), height(gameHeight)
        {
            generateRandomPosition();
        }

        // Function to generate random coordinates for the apple
        void generateRandomPosition()
        {
            std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) };
            std::uniform_int_distribution<int> xDistribution(0, width - 1);
            std::uniform_int_distribution<int> yDistribution(0, height - 1);

            // Generate random coordinates for the apple
            fruitCordX = xDistribution(mt);
            fruitCordY = yDistribution(mt);
        }

        int getAppleX() const
        {
            return fruitCordX;
        }

        int getAppleY() const
        {
            return fruitCordY;
        }

    private:
        int fruitCordX;
        int fruitCordY;
        int width;
        int height;
    };
}

#endif // !APPLE_H