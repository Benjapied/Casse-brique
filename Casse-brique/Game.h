#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include <vector>

class Brick;

class Game
{
public:

	sf::RenderWindow* m_renderer;
	std::vector<Brick*>* m_brickArray;

	Game(sf::RenderWindow* renderer);

	void Shoot(Rectangle* cannon, std::vector<Circle*>* balls, sf::Color* col);

	void LoadLevel(const char* path, sf::Color** ColorArray);

	void DrawBricks();
};

