#pragma once
#include "Rectangle.h"
#include <vector>
class Color;
class TextureManager;
namespace sf {
	class Texture;
}

class Brick : public Rectangle
{
public:
	int m_life;
	std::vector<sf::Texture*> m_textureArray;

	Brick(sf::RenderWindow* renderer, std::vector<sf::Texture*>textureArray, int x, int y);

	void Hit();
};



