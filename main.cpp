#include <SFML/Graphics.hpp> 
#include <iostream>
#include<random>
#include "gameData.h"
#include "Basket.h"
#include "Ball.h"
#include "collision.h"
#include "gamestate.h"



int main(){
    
    unsigned int scrnwidth = 1920; 
    unsigned int scrnheight = 1080; 

    //Basket Dimensions:
    float basketWidth = 150.f ; 
    float basketHeight =60.f;
    float initialBasketPosX = 900.f ;
    float initialBasketPosY = 1020.f ;
    float basketSpeed = 600.f ; //pixels per sec

    //Ball Dimension:
    float ballRadius = 30.f;
    float ballPosX = 960.f;
    float ballPosY = 10.f ; 
    float verticalBallSpeed = 900.f; //pixels per sec 

    gameData dataGame; // dataGame for the score, lives and gameStarted 
    // bool gameWon= false; 
    // bool gameLost = false; 
    GameState gameState = GameState::gameMenu ;




    sf::RenderWindow window(
        sf::VideoMode({scrnwidth, scrnheight}),//Defining the layout(w,h)
        "Catch IT "
    ); 

    //Creating the font 
    sf::Font font ; 
    if(!font.openFromFile("arial.ttf")){
        std::cout<<"Failed to return the file\n"; 
        return -1 ; 


    }

    //For the score text:
    sf::Text ScoreText (font); 
    ScoreText.setCharacterSize(15); 
    ScoreText.setPosition({10.f,10.f}); 
    ScoreText.setFillColor(sf::Color::White); 


    //For the lives text : 
    sf::Text LivesText (font); 
    LivesText.setCharacterSize(15); 
    LivesText.setPosition({10.f,25.f}); 
    LivesText.setFillColor(sf::Color::White);

    sf::Text resultText(font); 
    resultText.setCharacterSize(16); 
    resultText.setPosition({390.f ,290.f}); 
    resultText.setFillColor(sf::Color::Yellow); 




    //Defining the basket
    sf::RectangleShape basket (
        sf::Vector2f(basketWidth, basketHeight) 

        );
        
    //setting basket position
    basket.setPosition(
        sf::Vector2f(initialBasketPosX,initialBasketPosY)
    ); 

    //filling basket color 
    basket.setFillColor(sf::Color::Blue);

    sf::CircleShape ball(ballRadius); //20.f is radius 
    ball.setPosition(
        sf::Vector2f(ballPosX,ballPosY)

    );

    ball.setFillColor(sf::Color::Red); 
    sf::Clock clock ; 
    while (window.isOpen()){
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()){

            if(event->is<sf::Event::Closed>()){
                window.close(); 
            }

            if(event->is<sf::Event::KeyPressed>()){
                auto key = event->getIf<sf::Event::KeyPressed>()->code; 
                if(key== sf::Keyboard::Key::Enter){
                    gameState = GameState::gamePlaying; 
                }

            if(gameState== GameState::gameLost || gameState== GameState::gameWon)  {
                if(key == sf:: Keyboard::Key::Q){
                    window.close() ; 
                }

            if(key == sf:: Keyboard::Key::R){
                    //Reset everything ; 
                    dataGame.lives = 10;
                    dataGame.score = 0 ; 

                    // gameWon = false ; 
                    // gameLost = false ;
                    gameState = GameState:: gamePlaying ; 

                    basket.setPosition({initialBasketPosX, initialBasketPosY});
                    respawnBallPosition(ball); 

                }  
        
                }
            }
           
        }

        //Showing the score: 
        ScoreText.setString(
            "Score: "+ std::to_string(dataGame.score)
        ); 

        //Showing the lives:
        LivesText.setString(
            "Lives: "+ std::to_string(dataGame.lives)
            
        );

        // if(dataGame.gameStarted && !gameWon && !gameLost)
        
        if(gameState == GameState::gamePlaying ){
            moveBasket(basket,basketWidth,basketSpeed,dt);
            moveBall(ball,dataGame.lives,verticalBallSpeed,dt); 
            collisionDetect(ball, basket,dataGame.score ) ;
            if (dataGame.score>=10){
                gameState= GameState::gameWon;

            } 

            if (dataGame.lives<=0){
            gameState= GameState::gameLost; 
            }
        
        }

        if(gameState== GameState::gameWon){
            resultText.setString("YOU WIN!!!\n\nPlay Again - R\nExit - Q");
        }
        if(gameState== GameState::gameLost){
            resultText.setString("YOU LOSE!!!\n\nPlay Again - R\nExit - Q"); 
                }

        window.clear(sf::Color(30,30,50)); 
        window.draw(ScoreText); 
        window.draw(LivesText); 
        if (gameState== GameState::gamePlaying){
            window.draw(ball); 
            window.draw(basket);
            
        }
             
        if(gameState == GameState::gameLost || gameState== GameState::gameWon){
            window.draw(resultText); 
        }
        
        window.display(); 
    }
    return 0 ; 

}