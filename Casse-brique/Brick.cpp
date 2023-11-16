#include "Brick.h"
#include <vector>
#include <SFML/Graphics.hpp> 
#include "TextureManager.h"
 
Brick::Brick(sf::RenderWindow* renderer, std::vector<sf::Texture*>textureArray, int x, int y): Rectangle(renderer) {
	m_life = 2;
	m_textureArray = textureArray;

	this->SetTexture(m_textureArray[1]);
	this->ResizeTexture(280, 240, 1409, 740);
	this->SetSize(76,46);
	this->SetPosition(x, y);
};

void Brick::Hit()
{
	m_life--;
	if (m_life > 0) {
		this->SetTexture(m_textureArray[m_life - 1]);
		this->ResizeTexture(120, 153, 1409, 740);
	}
}


