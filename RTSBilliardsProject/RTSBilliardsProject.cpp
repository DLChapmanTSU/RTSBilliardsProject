// RTSBilliardsProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//ENSURE TARGET PLATFORM IS x64
//WILL NOT RUN OTHERWISE
//CHECK README IF LINKER ERRORS ARE FOUND
//For best results, run in release mode

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Particle.h"
#include "ParticleSystem.h"

struct Wall {
public:
    sf::Vector2f m_pointOne;
    sf::Vector2f m_pointTwo;
    sf::Vector2f m_wallDirection;
    std::pair<sf::Vector2f, sf::Vector2f> m_normals;
};

bool CheckForStaticCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2);
void CalculateCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2);
bool CheckForSideCollision(Ball& b, Wall& w);
bool CheckForMovingCollision(Ball& b1, Ball& b2);
void CalculateMovingCollision(Ball& b1, Ball& b2);
void TakeShot(sf::Vector2f m, Ball& b1);


int main()
{
    // All SFML types and functions are contained in the sf namespace

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "Billiards Simulation");
    std::cout << "Billiards: Starting" << std::endl;

    sf::Vector2f(100.0f, 100.0f);
    std::srand((unsigned int)time(NULL));
    sf::Font font;

    if (!font.loadFromFile("dogica.ttf")) {
        return 0;
    }

    std::vector<Ball> balls;
    std::vector<Wall> walls;

    balls.push_back(Ball(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::Blue, 0));
    balls.push_back(Ball(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::Red, 1));
    balls.push_back(Ball(sf::Vector2f(500.0f, 350.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::Red, 2));

    Wall wallOne;
    wallOne.m_pointOne = sf::Vector2f(55.0f, 5.0f);
    wallOne.m_pointTwo = sf::Vector2f(745.0f, 5.0f);
    wallOne.m_wallDirection = wallOne.m_pointTwo - wallOne.m_pointOne;
    Wall wallTwo;
    wallTwo.m_pointOne = sf::Vector2f(5.0f, 55.0f);
    wallTwo.m_pointTwo = sf::Vector2f(5.0f, 545.0f);
    wallTwo.m_wallDirection = wallTwo.m_pointTwo - wallTwo.m_pointOne;
    Wall wallThree;
    wallThree.m_pointOne = sf::Vector2f(795.0f, 55.0f);
    wallThree.m_pointTwo = sf::Vector2f(795.0f, 545.0f);
    wallThree.m_wallDirection = wallThree.m_pointTwo - wallThree.m_pointOne;
    Wall wallFour;
    wallFour.m_pointOne = sf::Vector2f(55.0f, 595.0f);
    wallFour.m_pointTwo = sf::Vector2f(745.0f, 595.0f);
    wallFour.m_wallDirection = wallFour.m_pointTwo - wallFour.m_pointOne;
    Wall wallFive;
    wallFive.m_pointOne = sf::Vector2f(55.0f, 5.0f);
    wallFive.m_pointTwo = sf::Vector2f(5.0f, 55.0f);
    wallFive.m_wallDirection = wallFive.m_pointTwo - wallFive.m_pointOne;
    Wall wallSix;
    wallSix.m_pointOne = sf::Vector2f(745.0f, 5.0f);
    wallSix.m_pointTwo = sf::Vector2f(795.0f, 55.0f);
    wallSix.m_wallDirection = wallSix.m_pointTwo - wallSix.m_pointOne;
    Wall wallSeven;
    wallSeven.m_pointOne = sf::Vector2f(5.0f, 545.0f);
    wallSeven.m_pointTwo = sf::Vector2f(55.0f, 595.0f);
    wallSeven.m_wallDirection = wallSeven.m_pointTwo - wallSeven.m_pointOne;
    Wall wallEight;
    wallEight.m_pointOne = sf::Vector2f(795.0f, 545.0f);
    wallEight.m_pointTwo = sf::Vector2f(745.0f, 595.0f);
    wallEight.m_wallDirection = wallEight.m_pointTwo - wallEight.m_pointOne;

    float dx = wallOne.m_pointTwo.x - wallOne.m_pointOne.x;
    float dy = wallOne.m_pointTwo.y - wallOne.m_pointOne.y;
    wallOne.m_normals.first = sf::Vector2f(-dy, dx);
    wallOne.m_normals.second = -wallOne.m_normals.first;

    dx = wallTwo.m_pointTwo.x - wallTwo.m_pointOne.x;
    dy = wallTwo.m_pointTwo.y - wallTwo.m_pointOne.y;
    wallTwo.m_normals.first = sf::Vector2f(-dy, dx);
    wallTwo.m_normals.second = -wallTwo.m_normals.first;

    dx = wallThree.m_pointTwo.x - wallThree.m_pointOne.x;
    dy = wallThree.m_pointTwo.y - wallThree.m_pointOne.y;
    wallThree.m_normals.first = sf::Vector2f(dy, -dx);
    wallThree.m_normals.second = -wallThree.m_normals.first;

    dx = wallFour.m_pointTwo.x - wallFour.m_pointOne.x;
    dy = wallFour.m_pointTwo.y - wallFour.m_pointOne.y;
    wallFour.m_normals.first = sf::Vector2f(dy, -dx);
    wallFour.m_normals.second = -wallFour.m_normals.first;

    dx = wallFive.m_pointTwo.x - wallFive.m_pointOne.x;
    dy = wallFive.m_pointTwo.y - wallFive.m_pointOne.y;
    wallFive.m_normals.first = sf::Vector2f(-dy, dx);
    wallFive.m_normals.second = -wallFive.m_normals.first;

    dx = wallSix.m_pointTwo.x - wallSix.m_pointOne.x;
    dy = wallSix.m_pointTwo.y - wallSix.m_pointOne.y;
    wallSix.m_normals.first = sf::Vector2f(-dy, dx);
    wallSix.m_normals.second = -wallSix.m_normals.first;

    dx = wallSeven.m_pointTwo.x - wallSeven.m_pointOne.x;
    dy = wallSeven.m_pointTwo.y - wallSeven.m_pointOne.y;
    wallSeven.m_normals.first = sf::Vector2f(-dy, dx);
    wallSeven.m_normals.second = -wallSeven.m_normals.first;

    dx = wallEight.m_pointTwo.x - wallEight.m_pointOne.x;
    dy = wallEight.m_pointTwo.y - wallEight.m_pointOne.y;
    wallEight.m_normals.first = sf::Vector2f(-dy, dx);
    wallEight.m_normals.second = -wallEight.m_normals.first;

    walls.push_back(wallOne);
    walls.push_back(wallTwo);
    walls.push_back(wallThree);
    walls.push_back(wallFour);
    walls.push_back(wallFive);
    walls.push_back(wallSix);
    walls.push_back(wallSeven);
    walls.push_back(wallEight);

    //Checks to see if a collision has been made for each ball each frame
    //Simulation will not attempt to register a collision with the same object more than once
    std::vector<bool> hasBallCollided;

    for (size_t i = 0; i < balls.size(); i++)
    {
        hasBallCollided.push_back(false);
    }

    bool shotTaken{ false };
    bool gameOver{ false };
    bool gameWin{ false };

    /*sf::Color c = sf::Color::Green;
    sf::Vector2f p = sf::Vector2f(500.0f, 500.0f);
    sf::Vector2f v = sf::Vector2f(0.0f, -1.0f);*/

    //Particle system initiation
    ParticleSystem system(10, 5, sf::Vector2f(500.0f, 500.0f), 0.0f, 360.0f, 1, sf::Color::Green, 0.1f);

    // Main loop that continues until window is closed
    while (window.isOpen())
    {
        //Handling SFML inputs
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::MouseButtonPressed:
                //Fires starter ball if the shot has yet to be taken
                if (shotTaken == false) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                        TakeShot(mousePos, balls[0]);
                        shotTaken = true;
                    }
                }
                break;
            case sf::Event::KeyReleased:
                //Resets the game state with the balls at a random position on the screen
                if (shotTaken == true) {
                    if (event.key.code == sf::Keyboard::R) {
                        for (size_t i = 0; i < balls.size(); i++)
                        {
                            std::cout << "Ball " << i << std::endl;
                            bool placeOkay{ false };
                            while (placeOkay == false)
                            {
                                balls[i].SetVelocity(sf::Vector2f(0.0f, 0.0f));
                                balls[i].SetPosition(sf::Vector2f((float)(std::rand() % 720) + 60, (float)(std::rand() % 520) + 60));
                                if (i == 0) {
                                    balls[i].SetColor(sf::Color::Blue);
                                }
                                else {
                                    balls[i].SetColor(sf::Color::Red);
                                }

                                for (size_t j = 0; j < balls.size(); j++) {
                                    if (balls[j].GetIndex() == balls[i].GetIndex()) {
                                        continue;
                                    }
                                    float rad = balls[j].GetRadius() + balls[i].GetRadius();
                                    sf::Vector2f diff = balls[j].GetPosition() - balls[i].GetPosition();
                                    float diffLength = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));

                                    if (diffLength > rad) {
                                        std::cout << "No Overlap" << std::endl;
                                        placeOkay = true;
                                    }
                                    else {
                                        placeOkay = false;
                                        std::cout << "Overlap" << std::endl;
                                        break;
                                    }
                                }
                            }
                        }

                        shotTaken = false;
                        gameOver = false;
                        gameWin = false;
                    }
                }
                break;
            default:
                break;
            }
        }

        bool collisionMade{ false };

        //Main simulation
        if (shotTaken == true && gameOver == false) {
            for (size_t i = 0; i < balls.size(); i++)
            {
                //Checks collisions for each moving ball against every other ball that isn't itself
                if (balls[i].GetVelocity().x != 0.0f || balls[i].GetVelocity().y != 0.0f) {
                    for (size_t j = 0; j < balls.size(); j++)
                    {
                        if ((balls[i].GetIndex() != balls[j].GetIndex()) && hasBallCollided[j] == false) {
                            //If the other ball isn't moving, a moving collision is checked
                            if (balls[j].GetVelocity().x >= 0.0001f || balls[j].GetVelocity().y >= 0.0001f || balls[j].GetVelocity().x <= -0.0001f || balls[j].GetVelocity().y <= -0.0001f) {
                                bool collision = CheckForMovingCollision(balls[i], balls[j]);
                                hasBallCollided[i] = collision;

                                if (collision == true) {
                                    system.Reset();
                                    sf::Vector2f particlePos = (balls[j].GetPosition() - balls[i].GetPosition()) / 2.0f;
                                    particlePos = balls[i].GetPosition() + particlePos;
                                    system.SetRootPosition(particlePos);

                                    if (balls[i].GetColor() == sf::Color::Blue && balls[j].GetColor() == sf::Color::Red) {
                                        balls[j].SetColor(sf::Color::Blue);
                                    }
                                    else if (balls[i].GetColor() == sf::Color::Red && balls[j].GetColor() == sf::Color::Blue) {
                                        balls[i].SetColor(sf::Color::Blue);
                                    }
                                }
                            }
                            else { //Otherwise, a static collision is checked
                                bool collision = CheckForStaticCollision(balls[i], balls[j], balls[i].GetVelocity(), balls[i].GetRadius(), balls[j].GetRadius());
                                if (collision == true) {
                                    system.Reset();
                                    sf::Vector2f particlePos = (balls[j].GetPosition() - balls[i].GetPosition()) / 2.0f;
                                    particlePos = balls[i].GetPosition() + particlePos;
                                    system.SetRootPosition(particlePos);

                                    if (balls[i].GetColor() == sf::Color::Blue && balls[j].GetColor() == sf::Color::Red) {
                                        balls[j].SetColor(sf::Color::Blue);
                                    }
                                    else if (balls[i].GetColor() == sf::Color::Red && balls[j].GetColor() == sf::Color::Blue) {
                                        balls[i].SetColor(sf::Color::Blue);
                                    }
                                }
                            }
                        }
                    }
                    //If the ball has not hit another ball, a wall collision is checked
                    if (hasBallCollided[i] == false) {
                        for (size_t j = 0; j < walls.size(); j++)
                        {
                            hasBallCollided[i] = CheckForSideCollision(balls[i], walls[j]);
                        }
                    }
                }
            }

            for (size_t i = 0; i < balls.size(); i++)
            {
                balls[i].Update();
                hasBallCollided[i] = false;
            }

            gameOver = true;

            //Ends the game if all balls have reached a near stationary point
            for (size_t i = 0; i < balls.size(); i++)
            {
                if ((balls[i].GetVelocity().x <= 0.00001f && balls[i].GetVelocity().x >= -0.00001f && balls[i].GetVelocity().y <= 0.00001f && balls[i].GetVelocity().y >= -0.00001f) == false) {
                    gameOver = false;
                    break;
                }
            }

            //If the game is over, the user is declared the winner if all balls have turned to blue
            if (gameOver == true) {
                gameWin = true;

                for (size_t i = 0; i < balls.size(); i++)
                {
                    if (balls[i].GetColor() != sf::Color::Blue) {
                        gameWin = false;
                        break;
                    }
                }

                if (gameWin == true) {
                    std::cout << "Winner" << std::endl;
                }
                else {
                    std::cout << "Loser" << std::endl;
                }
            }
        }

        system.Update();




        //Clears window
        window.clear();

        //Rendering to window
        for (size_t i = 0; i < balls.size(); i++)
        {
            balls[i].Render(window);
        }

        //Renders walls
        for (size_t i = 0; i < walls.size(); i++)
        {
            sf::VertexArray line(sf::LinesStrip, 2);

            line[0].position = walls[i].m_pointOne;
            line[1].position = walls[i].m_pointTwo;
            window.draw(line);
        }

        //Renders aiming reticle if the shot hasn't been taken
        if (shotTaken == false) {
            sf::CircleShape aim(10.0f);
            aim.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
            aim.setOrigin(aim.getRadius(), aim.getRadius());
            aim.setFillColor(sf::Color::Transparent);
            aim.setOutlineColor(sf::Color::White);
            aim.setOutlineThickness(2.0f);

            window.draw(aim);

            sf::Vector2f distance(sf::Vector2f(sf::Mouse::getPosition(window)) - balls[0].GetPosition());
            float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));

            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = balls[0].GetPosition();
            line[1].position = sf::Vector2f(sf::Mouse::getPosition(window));

            window.draw(line);
        }

        //Renders win or loss text if the game is over
        if (gameOver == true) {
            if (gameWin == true) {
                sf::Text text;
                text.setFont(font);
                text.setString("You Win");
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Green);
                window.draw(text);
            }
            else {
                sf::Text text;
                text.setFont(font);
                text.setString("You Lose");
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Red);
                window.draw(text);
            }
        }

        //Render the particle system
        system.Render(window);

        //Push all rendered objects to the screen
        window.display();
    }

    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}

//Checks to see if a collision between a moving and stationary ball is possible
bool CheckForStaticCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2) {
    //Calculates vector between the two balls
    sf::Vector2f a;

    a.x = b2.GetPosition().x - b1.GetPosition().x;
    a.y = b2.GetPosition().y - b1.GetPosition().y;

    //Gets the length of A and the length of the velocity of the moving ball
    //Then makes them unit length
    float lengthV = std::sqrt((v.x * v.x) + (v.y * v.y));
    float lengthA = std::sqrt((a.x * a.x) + (a.y * a.y));

    a.x /= lengthA;
    a.y /= lengthA;

    v.x /= lengthV;
    v.y /= lengthV;

    //Dot product of unit vectors
    float dot = (a.x * v.x) + (a.y * v.y);

    //uses the dot product to calculate the angle between the two vectors
    float q = std::acos(dot);

    float sinQ = std::sin(q);

    //Calculates the distance between the centre of the stationary ball, and the nearest point of the moving balls velocity
    float d = sinQ * lengthA;

    //If d is not smaller than the combined radi of the two balls, there is no collision. Otherwise, the program moves to the next stage
    if (d < (r1 + r2)) {
        //Calculates e, which along with d and the combined radi of the balls forms a triangle
        //The length of the side e therefore represents the distance between the centre of the first ball when in contact with the other ball, and the end of the velocity vector
        float r = r1 + r2;
        float e = std::sqrt((r * r) - (d * d));

        //Calculates the length of vc + e, which can then tell us the length of vc by taking away e
        float vceSum = std::cos(q) * lengthA;
        float vc = vceSum - e;

        //If the length of vc is larger than 0 and withing the length of the velocity vector, a collision is made
        if (vc <= lengthV && vc >= 0.0f) {
            //Snap the moving ball to the collision point
            sf::Vector2f newPos = b1.GetPosition();

            newPos.x += (v.x * vc) * 0.99f;
            newPos.y += (v.y * vc) * 0.99f;

            b1.SetPosition(newPos);

            //Calculates the impulse of the collision
            CalculateCollision(b1, b2, v, r1, r2);
            return true;
        }
        else {
            //std::cout << "vc longer than |V|" << std::endl;
            return false;
        }
    }
    else {
        //std::cout << "No Collision" << std::endl;
        return false;
    }


}

//Calculates the impulse of a static collision for both balls involved in the collision
//Considers the conservation of momentum from the moving ball to the static ball
void CalculateCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2) {
    //Calculates the direction of the force acting upon the static ball
    sf::Vector2f fd;
    fd.x = b2.GetPosition().x - b1.GetPosition().x;
    fd.y = b2.GetPosition().y - b1.GetPosition().y;

    //The direction is converted to a unit vector for ease of use
    float fdLength = std::sqrt((fd.x * fd.x) + (fd.y * fd.y));
    fd.x /= fdLength;
    fd.y /= fdLength;

    //Calculates a unit vector from the velocity of the moving ball
    sf::Vector2f vd = v;
    float vLength = std::sqrt((vd.x * vd.x) + (vd.y * vd.y));
    vd.x /= vLength;
    vd.y /= vLength;

    //Both unit vectors are used to find the angle of the collision by finding the dot product of the two vectors
    float dot = (fd.x * vd.x) + (fd.y * vd.y);
    float cosA = dot;

    //v1 = new velocity of the moving ball
    //v2 = new velocity of the static ball
    sf::Vector2f v1;
    sf::Vector2f v2;

    //Uses the cosine of the angle and the force direction to calculate the impulse of the static ball
    v2.x = cosA * fd.x;
    v2.y = cosA * fd.y;

    //Because of the conservation of mass, we can assume that the moving balls new trajectory will be the the remaining force that wasn't transferred to the static ball
    //i.e, the difference between the current velocity direction and the new velocity of the static ball
    v1.x = vd.x - v2.x;
    v1.y = vd.y - v2.y;

    //Multiplies the new velocities by the magnitude of the old velocities to keep them consistant with eachother
    v1 *= b1.GetRawVLength();
    v2 *= b1.GetRawVLength();

    //Sets the new velocities
    b1.SetVelocity(v1);
    b2.SetVelocity(v2);
}

bool CheckForSideCollision(Ball& b, Wall& w) {

    bool hasCollided{ false };

    //Takes a point on the wall, which for this is always the center point
    sf::Vector2f k = w.m_pointOne + (w.m_wallDirection / 2.0f);

    //Decides which normal to use based on which side of the wall the ball is on
    sf::Vector2f ballToN1 = (k + w.m_normals.first) - b.GetPosition();
    sf::Vector2f ballToN2 = (k + w.m_normals.second) - b.GetPosition();
    float firstLength = std::sqrt((ballToN1.x * ballToN1.x) + (ballToN1.y * ballToN1.y));
    float secondLength = std::sqrt((ballToN2.x * ballToN2.x) + (ballToN2.y * ballToN2.y));
    sf::Vector2f n;

    if (firstLength < secondLength) {
        n = w.m_normals.first;
    }
    else {
        n = w.m_normals.second;
    }

    //sf::Vector2f n = w.m_normals.first;
    float nLength = std::sqrt((n.x * n.x) + (n.y * n.y));
    n /= nLength;
    sf::Vector2f p = b.GetPosition() - k;
    float pLength = std::sqrt((p.x * p.x) + (p.y * p.y));
    float dot = (p.x * n.x) + (p.y * n.y);
    //Gets the cosine of the angle between the normal and the balls trajectory
    float cosQ1 = dot / pLength;
    float q1 = std::acos(cosQ1);
    //Finds the angle between the plane and the trajectory of the ball in radians
    float q2 = 1.5708f - q1;

    //q1 and q2 should sum up to 90 degrees. If it doesn't, we know the ball is on the opposite side to the normal, so we try again with the opposite normal
    if ((q1 + q2) >= 1.571f || (q1 + q2) <= 1.5706f) {
        n = w.m_normals.second;
        nLength = std::sqrt((n.x * n.x) + (n.y * n.y));
        n /= nLength;
        p = b.GetPosition() - k;
        pLength = std::sqrt((p.x * p.x) + (p.y * p.y));
        dot = (p.x * n.x) + (p.y * n.y);
        cosQ1 = dot / pLength;
        q1 = std::acos(cosQ1);
        q2 = 1.5708f - q1;
    }

    //Finds the distance between the ball and the closest point on the wall
    float d = std::sin(q2) * pLength;
    sf::Vector2f v = b.GetVelocity();
    float vLength = std::sqrt((v.x * v.x) + (v.y * v.y));
    //Finds the cosine of the angle between the balls trajectory and the direction to the nearest point of the wall
    float cosS = ((v.x * -n.x) + (v.y * -n.y)) / vLength;
    //Gives the magnitude of the vector that will bring the ball into contact with the wall
    float vcLength = (d - b.GetRadius()) / cosS;

    //If the magnitude of vc falls withing the magnitude of the balls velocity, then a collision will take place this update
    if (vcLength <= vLength && vcLength >= 0.0f) {
        //Calculates the vector to the collision point (vc) and moves the ball to it
        sf::Vector2f vc = (v / vLength) * vcLength;
        sf::Vector2f position = b.GetPosition() + vc;

        float wallLength = std::sqrt((w.m_wallDirection.x * w.m_wallDirection.x) + (w.m_wallDirection.y * w.m_wallDirection.y));
        sf::Vector2f wallStartToBall = position - w.m_pointOne;
        sf::Vector2f wallEndToBall = position - w.m_pointTwo;
        float startToBallLength = std::sqrt((wallStartToBall.x * wallStartToBall.x) + (wallStartToBall.y * wallStartToBall.y));
        float endToBallLength = std::sqrt((wallEndToBall.x * wallEndToBall.x) + (wallEndToBall.y * wallEndToBall.y));
        //std::cout << wallLength << std::endl;
        //std::cout << toBallLength << std::endl;
        //std::cout << toBallLength - wallLength << std::endl;

        if (startToBallLength > wallLength + b.GetRadius() || endToBallLength > wallLength + b.GetRadius()) {
            return false;
        }

        //b.SetPosition(position);

        sf::Vector2f reflectedVector;

        //Reflects the balls velocity about the normal of the wall
        float reflectedDot = (v.x * n.x) + (v.y * n.y);
        reflectedVector = v - 2 * reflectedDot * n;

        if (reflectedVector != v) {
            b.SetVelocity(reflectedVector);
            hasCollided = true;
        }
    }

    return hasCollided;
}

//Checks if a moving collision is possible
bool CheckForMovingCollision(Ball& b1, Ball& b2) {
    //Grabs positions and velocities for each.
    sf::Vector2f p1 = b1.GetPosition();
    sf::Vector2f p2 = b2.GetPosition();
    sf::Vector2f v1 = b1.GetVelocity();
    sf::Vector2f v2 = b2.GetVelocity();


    float combinedRadius{ b1.GetRadius() + b2.GetRadius() };

    float xp = p1.x - p2.x;
    float yp = p1.y - p2.y;
    float xv = v1.x - v2.x;
    float yv = v1.y - v2.y;

    //Calculates a b and c values for quadratic equation.
    float a = (xv * xv) + (yv * yv);
    float b = (2 * xp * xv) + (2 * yp * yv);
    float c = (xp * xp) + (yp * yp) - (combinedRadius * combinedRadius);

    if ((b * b) < (4 * a * c)) {
        return false;
    }

    //Calculates both possible results from the quadratic
    float positiveT = (-b + std::sqrt((b * b) - (4 * a * c))) / (2 * a);
    float negativeT = (-b - std::sqrt((b * b) - (4 * a * c))) / (2 * a);

    //Collision takes place if either result from the quadratic falls between 0 and 1.
    if ((positiveT >= 0.0f && positiveT <= 1.0f) || (negativeT >= 0.0f && negativeT <= 1.0f)) {
        CalculateMovingCollision(b1, b2);

        return true;
    }
    else {
        return false;
    }
}

//Calculates the impulse of a moving collision
void CalculateMovingCollision(Ball& b1, Ball& b2) {
    sf::Vector2f p1 = b1.GetPosition();
    sf::Vector2f p2 = b2.GetPosition();
    sf::Vector2f v1 = b1.GetVelocity();
    sf::Vector2f v2 = b2.GetVelocity();

    //Generates vector from ball 1 to ball 2 and vice-versa
    sf::Vector2f ballOneToBallTwo = p2 - p1;
    sf::Vector2f ballTwoToBallOne = p1 - p2;

    //Length of both velocities and the vectors between balls
    //The vectors between balls will always have the same length
    float distanceLength = std::sqrt((ballOneToBallTwo.x * ballOneToBallTwo.x) + (ballOneToBallTwo.y * ballOneToBallTwo.y));
    float v1Length = std::sqrt((v1.x * v1.x) + (v1.y * v1.y));
    float v2Length = std::sqrt((v2.x * v2.x) + (v2.y * v2.y));

    //Calculates cosines of angles between ball 1 velocity and vector from ball 1 to ball 2
    //Also calculates cosine of angle between ball 2 velocity and vector from ball 2 to ball 1
    float cosA = (ballOneToBallTwo.x * v1.x) + (ballOneToBallTwo.y * v1.y);
    cosA /= (distanceLength * v1Length);
    float cosB = (ballTwoToBallOne.x * v2.x) + (ballTwoToBallOne.y * v2.y);
    cosB /= (distanceLength * v2Length);

    //Normalizes vector between balls to unit vectors
    sf::Vector2f fd1 = ballOneToBallTwo / (std::sqrt((ballOneToBallTwo.x * ballOneToBallTwo.x) + (ballOneToBallTwo.y * ballOneToBallTwo.y)));
    sf::Vector2f fd2 = -fd1;

    //Calculates impulse force for both balls
    //Mass is assumed to be 1, thus we don't need to factor it in to our equation
    sf::Vector2f forceOnB2 = cosA * v1Length * fd1;
    sf::Vector2f forceOnB1 = cosB * v2Length * fd2;

    //Calculates new velocities based on the conservation of energy
    sf::Vector2f newV2 = v2 + forceOnB2 - forceOnB1;
    sf::Vector2f newV1 = v1 + forceOnB1 - forceOnB2;

    b1.SetVelocity(newV1);
    b2.SetVelocity(newV2);
}

//Sets the velocity of the cue ball based on the position of the mouse
void TakeShot(sf::Vector2f m, Ball& b1) {
    sf::Vector2f direction = m - b1.GetPosition();
    float dLength = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    direction /= dLength;
    float power = dLength / 100.0f;
    if (power > 1.0f) {
        power = 1.0f;
    }
    direction *= power;

    b1.SetVelocity(direction);
}
