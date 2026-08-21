#pragma once

#include <SFML/Graphics.hpp>

float getRandomNum();

void respawnBallPosition(
    sf::CircleShape& ball
);

void moveBall(
    sf::CircleShape& ball,
    int& lives,
    float verticalBallSpeed,
    float dt
);