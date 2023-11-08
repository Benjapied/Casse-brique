#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include "Circle.h"
#include "Rectangle.h"


int main(int argc, char** argv)
{

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(1280, 960), "SFML");
    sf::Color cRed(255, 0, 0);
    sf::Color cGreen(0, 255, 0);
    sf::Color cBlue(0, 0, 255);

    Circle* objet = new Circle(&oWindow);
    objet->SetPosition(50,50);
    objet->SetSize(100, 100);
    objet->SetColor(&cRed);

    Rectangle* cannon = new Rectangle(&oWindow);
    cannon->SetPosition(640, 900);
    cannon->SetSize(100, 50);
    cannon->SetColor(&cGreen);

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
        objet->Move(fDeltaTime);
        objet->SetDirectionMouse(localPosition.x, localPosition.y);

        oWindow.clear();

        objet->Draw();
        cannon->Draw();

        oWindow.display();

        clock += fDeltaTime;

        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
