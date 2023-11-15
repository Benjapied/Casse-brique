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

    //Brick* DeezBrick = new Brick(&oWindow, deezColorArray, 520, 80);

    Game* game = new Game(&oWindow);

    sf::Clock oClock;
    float fDeltaTime = 1;
    float clock = 0;

    game->LoadLevel("levels/level1.txt");

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
        
        
        if (oEvent.type == sf::Event::MouseButtonPressed) {
            if (game->m_mouseState == false) {
                if (oEvent.mouseButton.button == sf::Mouse::Left) {
                    game->Shoot();
                    game->m_mouseState = true;
                }
            }
        }
        else if (oEvent.type == sf::Event::MouseButtonReleased) {
            game->m_mouseState = false;
        }

        oWindow.clear();
        game->GameLoop(localPosition, fDeltaTime);
        oWindow.display();
        clock += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
