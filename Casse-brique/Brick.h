#pragma once
#include "Rectangle.h"
class Color;

class Brick : public Rectangle
{
public:
	int m_life;
	sf::Color** m_colorArray;

	Brick(sf::RenderWindow* renderer, sf::Color** colorArray);

	void Hit();
};