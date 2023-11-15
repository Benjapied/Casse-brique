#pragma once
#include "Rectangle.h"
#include <vector>
class Color;

class Brick : public Rectangle
{
public:
	int m_life;
	std::vector<sf::Color*> m_colorArray;

	Brick(sf::RenderWindow* renderer, std::vector<sf::Color*>colorArray, int x, int y);

	void Hit();
};



