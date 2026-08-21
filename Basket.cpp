//moving the basket: 
#include "Basket.h"
void moveBasket (sf::RectangleShape& basket,float basketWidth, float basketSpeed,float dt ) {
    auto basketpos = basket.getPosition(); 
    // std::cout<<pos.x <<std::endl; 
    // std::cout<<pos.y<<std::endl ; 

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&& basketpos.x>0){
        basket.move(sf::Vector2f(-basketSpeed*dt,0.f));


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && basketpos.x+basketWidth<1920){
        basket.move (sf::Vector2f(basketSpeed*dt,0.f)); 
    }
}