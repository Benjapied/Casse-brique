#include "Game.h"
#include "FileManager.h"


int main(int argc, char** argv)
{
    sf::RenderWindow oWindow(sf::VideoMode(1280, 960), "SFML");
    Game* game = new Game(&oWindow);

    game->LoadLevel("levels/leveld.txt");

    game->GameLoop();

    return 0;
}
