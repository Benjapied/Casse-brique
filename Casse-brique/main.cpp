#include <SFML/Graphics.hpp>
#include "GameObject.h"

int main(int argc, char** argv)
{
    sf::Clock oClock;
    float fDeltaTime=0;

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML");

    GameObject* test = new GameObject("rectangle", &oWindow);
    sf::Color cBlue(0, 0, 255);
    test->SetPosition(50, 50);
    test->SetSize(150, 150);
    test->SetColor(&cBlue);
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

        //UPDATE
        test->Move(fDeltaTime);
        //DRAW
        

        oWindow.clear();

        test->Draw();

        oWindow.display();

        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}
