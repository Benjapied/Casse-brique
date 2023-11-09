#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include <vector>


int main(int argc, char** argv)
{

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(1280, 960), "SFML");
    sf::Color cRed(255, 0, 0);
    sf::Color cGreen(0, 255, 0);
    sf::Color cBlue(0, 0, 255);

    std::vector<Circle*> balls;

    Circle* objet = new Circle(&oWindow);
    objet->SetPosition(640,50);
    objet->SetSize(50, 50);
    objet->SetColor(&cRed);
    objet->ChangeDirection(0, 1);
    objet->SetBounce(true);

    Rectangle* cannon = new Rectangle(&oWindow);
    cannon->SetPosition(640, 700);
    cannon->SetSize(50, 50);
    cannon->SetColor(&cGreen);

    Rectangle* wallUp = new Rectangle(&oWindow);
    wallUp->SetPosition(0, -1);
    wallUp->SetSize(1280, 1);

    Rectangle* wallDown = new Rectangle(&oWindow);
    wallDown->SetPosition(0, 960);
    wallDown->SetSize(1280, 1);

    Rectangle* wallLeft = new Rectangle(&oWindow);
    wallLeft->SetPosition(-1, 0);
    wallLeft->SetSize(1, 960);

    Rectangle* wallRight = new Rectangle(&oWindow);
    wallRight->SetPosition(1280, 0);
    wallRight->SetSize(1, 960);

    Rectangle* WallArray[4] = {wallUp,wallDown,wallLeft,wallRight};

    sf::Clock oClock;
    float fDeltaTime = 1;
    float clock = 0;

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
        cannon->Rotate(localPosition.x, localPosition.y);
        cannon->ChangeDirection(localPosition.x - cannon->m_positionX, localPosition.y - cannon->m_positionY);
        
        objet->Move(fDeltaTime);
        if (objet->Colision(cannon) != 0)
        {
            objet->Bounce();
        }
        //objet->SetDirectionMouse(localPosition.x, localPosition.y);
        
        for (int i = 0; i < 4; i++) {
            if (objet->Colision(WallArray[i]) != 0)
                objet->Bounce();
        }
        if (oEvent.type == sf::Event::MouseButtonPressed)
        {
            if (oEvent.mouseButton.button == sf::Mouse::Left)
            {
                Circle* ball = new Circle(&oWindow);
                ball->SetSize(10, 10);
                ball->SetColor(&cBlue);
                ball->SetPosition(cannon->m_positionX +cannon->m_height * cannon->m_direction.x, cannon->m_positionY+ cannon->m_width/2 * cannon->m_direction.y);
                ball->ChangeDirection(cannon->m_direction.x, cannon->m_direction.y);
                balls.insert(balls.begin(), ball);
            }
        }

        oWindow.clear();
        for (int i = 0; i < balls.size(); i++) {
            balls[i]->Move(fDeltaTime);
            balls[i]->Draw();
        }
        objet->Draw();
        cannon->Draw();

        oWindow.display();

        clock += fDeltaTime;

        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
