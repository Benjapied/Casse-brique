#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include "Game.h"
#include "Brick.h"
#include <vector>
#include "FileManager.h"


int main(int argc, char** argv)
{

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(1280, 960), "SFML");
    sf::Color cRed = sf::Color::Red;
    sf::Color cGreen= sf::Color::Green;
    sf::Color cBlue=sf::Color::Blue;
    sf::Color cYellow = sf::Color::Yellow;

    bool mouseState = false;
    

    Rectangle* cannon = new Rectangle(&oWindow);
    cannon->SetPosition(640, 700);
    cannon->SetSize(50, 100);
    cannon->SetColor(&cGreen);

    Rectangle* wallUp = new Rectangle(&oWindow);
    wallUp->SetPosition(0, -1);
    wallUp->SetSize(1280, 1);

    /*Rectangle* wallDown = new Rectangle(&oWindow);
    wallDown->SetPosition(0, 960);
    wallDown->SetSize(1280, 1);
    */
    Rectangle* wallLeft = new Rectangle(&oWindow);
    wallLeft->SetPosition(-1, 0);
    wallLeft->SetSize(1, 960);

    Rectangle* wallRight = new Rectangle(&oWindow);
    wallRight->SetPosition(1280, 0);
    wallRight->SetSize(1, 960);

    sf::Color* deezColorArray[3] = { &cRed,&cBlue,&cGreen };

    Rectangle* WallArray[3] = {wallUp,wallLeft,wallRight};

    Game* game = new Game(&oWindow);

    sf::Clock oClock;
    float fDeltaTime = 1;
    float clock = 0;

    game->LoadLevel("levels/level1.txt", deezColorArray);

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(oWindow);

        //UPDATE
        if (localPosition.y < cannon->m_positionY- cannon->m_width) {
            cannon->Rotate(localPosition.x, localPosition.y);
            cannon->ChangeDirection(localPosition.x - cannon->m_positionX, localPosition.y - cannon->m_positionY);
        }
        //objet->SetDirectionMouse(localPosition.x, localPosition.y);
        
        if (oEvent.type == sf::Event::MouseButtonPressed)
        {
            if (mouseState == false) {
                if (oEvent.mouseButton.button == sf::Mouse::Left)
                {
                    game->Shoot(cannon, &cBlue);
                    mouseState = true;
                }
            }
            
        }
        else if (oEvent.type == sf::Event::MouseButtonReleased) {
            mouseState = false;
        }


        for (int i = 0; i < game->m_bulletArray.size(); i++) {
            game->m_bulletArray[i]->Move(fDeltaTime);

            //Checking for wall collider
            for (int j = 0; j < 3; j++) {
                game->m_bulletArray[i]->Bounce(game->m_bulletArray[i]->Colision(WallArray[j]));
            }

            for (int a = 0; a < game->m_brickArray.size(); a++) {
                game->m_bulletArray[i]->Bounce(game->m_bulletArray[i]->Colision(game->m_brickArray[a]));
                if (game->m_bulletArray[i]->Colision(game->m_brickArray[a]) != 0)
                {
                    game->m_brickArray[a]->Hit();
                }
            }
            
            if (game->m_bulletArray[i]->m_positionY > 960) {
                game->DeleteBall(i);
            }
        }
        for (int k = 0; k < game->m_brickArray.size();k++) {
            game->DeleteBrick(k);
        }

        oWindow.clear();

        game->DrawBricks();
        game->DrawBalls();
        
        cannon->Draw();
        oWindow.display();

        clock += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
