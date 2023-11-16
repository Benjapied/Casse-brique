#include "Brick.h"
#include <vector>
#include <SFML/Graphics.hpp> 
#include "TextureManager.h"
 
Brick::Brick(sf::RenderWindow* renderer, std::vector<sf::Texture*>textureArray, int x, int y): Rectangle(renderer) {
	m_life = 2;
	m_textureArray = textureArray;

	this->SetTexture(m_textureArray[1]);
	this->SetSize(120,50);
	this->SetPosition(x+4, y+2);
};

void Brick::Hit()
{
	m_life--;
	if (m_life > 0) {
		this->SetTexture(m_textureArray[m_life - 1]);
	}
}


