#include "Game.h"
#include "FileManager.h"


int main(int argc, char** argv)
{
    sf::RenderWindow oWindow(sf::VideoMode(1280, 960), "SFML");
    oWindow.setMouseCursorVisible(false);
    Game* game = new Game(&oWindow);

    game->LoadLevel("levels/heart.txt");

    game->GameLoop();

    return 0;
}
