#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include "Brick.h"
#include <vector>
class Game
{
public:

	sf::RenderWindow* m_renderer;
	std::vector<Brick*>*m_bricks;
	Game(sf::RenderWindow* renderer);
	void Shoot(Rectangle* cannon, std::vector<Circle*>* balls, sf::Color* col);
	void DeleteBall(std::vector<Circle*>* balls, int* i);
};

