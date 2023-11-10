#include "Brick.h"
#include <SFML/Graphics.hpp> 

Brick::Brick(sf::RenderWindow* renderer, sf::Color** colorArray): Rectangle(renderer) {
	m_life = 3;

	this->SetColor(m_colorArray[m_life]);
	this->SetSize(200,20);
};

void Brick::Hit()
{
	m_life--;
	this->SetColor(m_colorArray[m_life]);
}