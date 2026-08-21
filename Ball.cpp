#include "Ball.h"
#include<random>
//Creating a random number:
float getRandomNum() {
    
    static std::random_device rd ; 
    static std::mt19937 gen(rd()); 
    static std::uniform_real_distribution<float>distrib(0.f,1860.f); 
    return distrib(gen); 


}


void respawnBallPosition(sf::CircleShape& ball){
    ball.setPosition({getRandomNum(), 10.f}); 


}
//the ball falling mechanism:
void moveBall(sf::CircleShape& ball, int& lives,float verticalBallSpeed,float dt  ){
    ball.move(sf::Vector2f(0.f, verticalBallSpeed*dt));


    auto ballPos = ball.getPosition(); 

        //1080.f :-> scrnheight    
        if (ballPos.y>= 1080.f){  
            respawnBallPosition(ball) ;
            lives--; 
            // std::cout<<"Lives"<<":"<<lives<<std::endl; 

        }
}   