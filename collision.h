#pragma once

#include <SFML/Graphics.hpp>

void collisionDetect(
    sf::CircleShape& ball,
    sf::RectangleShape& basket,
    int& score
);