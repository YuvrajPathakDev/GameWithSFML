#include "Collision.h"
#include "Ball.h"


void collisionDetect(
    sf::CircleShape& ball , 
    sf::RectangleShape& basket,
    int &score 
)
{
    auto ballBounds = ball.getGlobalBounds(); 
    auto basketBounds = basket.getGlobalBounds() ; 

    if (ballBounds.findIntersection(basketBounds)){
        // std::cout<<"Caught\n";
        score++; 
        // std::cout<<"Score:"<<score<<std::endl; 
        respawnBallPosition(ball);

    }
}