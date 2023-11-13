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

    std::vector<Circle*> balls;
    std::vector<Circle*>* ptrballs = &balls;

    bool mouseState = false;
    Circle* objet = new Circle(&oWindow);
    objet->SetPosition(640,50);
    objet->SetSize(50, 50);
    objet->SetColor(&cRed);
    objet->ChangeDirection(2, 1);
    objet->SetBounce(true);

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

    Game* test = new Game(&oWindow);

    sf::Clock oClock;
    float fDeltaTime = 1;
    float clock = 0;

    FileManager::returnText("levels/level1.txt");

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
        objet->Move(fDeltaTime);
        objet->Bounce(objet->Colision(cannon));
        //objet->SetDirectionMouse(localPosition.x, localPosition.y);
        
        for (int i = 0; i < 3; i++) {
               objet->Bounce(objet->Colision(WallArray[i]));
        }
        if (oEvent.type == sf::Event::MouseButtonPressed)
        {
            if (mouseState == false) {
                if (oEvent.mouseButton.button == sf::Mouse::Left)
                {
                    game->Shoot(cannon, ptrballs, &cBlue);
                    mouseState = true;
                }
            }
            
        }
        else if (oEvent.type == sf::Event::MouseButtonReleased) {
            mouseState = false;
        }

        oWindow.clear();
        for (int i = 0; i < balls.size(); i++) {
            balls[i]->Move(fDeltaTime);
            for (int j = 0; j < 3; j++) {
                balls[i]->Bounce(balls[i]->Colision(WallArray[j]));                
            }
            balls[i]->Draw();
            if (balls[i]->m_positionY > 960) {
                game->DeleteBall(&balls,&i);
            }
        }
        
        game->DrawBricks();
        objet->Draw();
        cannon->Draw();
        for (int i = 0; i < game->m_brickArray->size(); i++) {
            game->m_brickArray->at(i)->Draw();
        }
        oWindow.display();

        clock += fDeltaTime;

        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
