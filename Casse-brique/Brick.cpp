#include "Brick.h"
#include <SFML/Graphics.hpp> 

Brick::Brick(sf::RenderWindow* renderer, sf::Color** colorArray, int x, int y): Rectangle(renderer) {
	m_life = 3;
	m_colorArray = colorArray;

	this->SetColor(m_colorArray[2]);
	this->SetSize(120,50);
	this->SetPosition(x+4, y+2);
};

void Brick::Hit()
{
	m_life--;
	if(m_life > 0)
		this->SetColor(m_colorArray[m_life-1]);
}

