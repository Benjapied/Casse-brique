#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include <vector>
class Game
{
public:

	sf::RenderWindow* m_renderer;
	Game(sf::RenderWindow* renderer);
	void Shoot(Rectangle* cannon, std::vector<Circle*>* balls, sf::Color* col);
};

