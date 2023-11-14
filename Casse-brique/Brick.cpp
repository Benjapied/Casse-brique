#include "Brick.h"
#include <SFML/Graphics.hpp> 

Brick::Brick(sf::RenderWindow* renderer, sf::Color** colorArray, int x, int y): Rectangle(renderer) {
	m_life = 3;
	m_colorArray = colorArray;

	this->SetColor(m_colorArray[0]);
	this->SetSize(128,50);
	this->SetPosition(x, y);
};

void Brick::Hit()
{
	m_life--;
	if (m_life == 0)
	{
		delete this;
		return;
	}
	this->SetColor(m_colorArray[m_life-1]);
}

