#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    unsigned int scrnwidth = 1920;
    unsigned int scrnheight = 1080;

    float squashAmount = 0.f; 
    float squashRecoverySpeed = 3.f;


    // Boundary Dimensions:
    float boundaryheight = 900.f;
    float boundarywidth = 1000.f;
    float boundaryPositionX = 400.f;
    float boundaryPositionY = 80.f;
    float boundaryOutline = 8.f;

    float leftWall = boundaryPositionX; 
    float rightWall= boundaryPositionX + boundarywidth;
    float topWall = boundaryPositionY; 
    float bottomWall = boundaryPositionY + boundaryheight;
    // Ball Dimensions:
    float radius = 50.f;
    float ballPositionX = 800.f;
    float ballPositionY = 80.f;

    // Ball Movement:
    float velocityX = 900.f; // Horizontal Movement
    float velocityY = 3.f;   // Vertical Movement
    float acc_gravity = 980.f;
    float restitution = 0.9f;

    bool resting = false;

    sf::RenderWindow window(
        sf::VideoMode({scrnwidth, scrnheight}),
        "Basic Physics Simulation");

    // Ball
    sf::CircleShape ball(radius);
    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition({ballPositionX, ballPositionY});
    ball.setOrigin({radius, radius}); // sets the origin to (r,r)

    // Boundary
    sf::RectangleShape boundary(
        sf::Vector2f(boundarywidth, boundaryheight));

    boundary.setPosition({boundaryPositionX, boundaryPositionY});
    boundary.setFillColor(sf::Color::Transparent);
    boundary.setOutlineThickness(boundaryOutline);
    boundary.setOutlineColor(sf::Color::Blue);

    // Creating a clock in SFML :
    sf::Clock clock;

    while (window.isOpen())
    {

        float dt = clock.restart().asSeconds();
        // For 16 milliseconds the dt becomes 0.016 ;
        // time for one frame

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        

        if (!resting)
        {
            ball.move({velocityX * dt, velocityY * dt});
            // The ball moves downward with velocity of v(y)=3.f;
            // Acceleration due to gravity=  0.5f
            // Then horizontal movement is also added
            velocityY += acc_gravity * dt; // final velocity
        }

        if(squashAmount>0.f){
            squashAmount-= squashRecoverySpeed*dt; 
            if(squashAmount<0.f){
                squashAmount=0.f; 
            }
        }
        // Floor Wall:
        if (ball.getPosition().y + radius >= boundaryheight + boundaryPositionY)
        {
            
            ball.setPosition(
                {ball.getPosition().x, bottomWall - radius}

            );
            float impactSpeed = std::abs(velocityY);
            squashAmount= std::min(impactSpeed/1500.f,0.4f) ;
            velocityY = -velocityY * restitution;
        }

        // Left Wall:
        if (ball.getPosition().x - radius <= boundaryPositionX)
        {
            ball.setPosition(
                {leftWall + radius, ball.getPosition().y});
            velocityX = -velocityX * restitution;
        }

        // Right Wall:
        if (ball.getPosition().x + radius >= boundaryPositionX + boundarywidth)
        {
            ball.setPosition(
                { rightWall - radius, ball.getPosition().y});
            velocityX = -velocityX * restitution;
        }

        // Ceiling Wall:
        if (ball.getPosition().y - radius <= boundaryPositionY)
        {
            ball.setPosition(
                {ball.getPosition().x, topWall+radius});
            velocityY = -velocityY * restitution;
        }

        // if(std::abs(velocityY)<10.f){
        //     velocityY = 0.f ;
        //     resting = true;

        // }
        // else{
        // std::cout<<velocityY<<std::endl;
        // std::cout<<ball.getPosition().x<<","<<ball.getPosition().y<<std::endl;
        // }
        ball.setScale({
            1.f + squashAmount, 
            1.f - squashAmount
        });



        window.clear(sf::Color::Black);
        window.draw(boundary);
        window.draw(ball);
        window.display();
         
    }

   

    return 0;
}