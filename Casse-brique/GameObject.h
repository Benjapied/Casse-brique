#pragma once

namespace sf
{
	class Shape;
}

class GameObject
{
public:
	int m_positionX;
	int m_positionY;
	int m_width;
	int m_height;
	sf::Shape* shape;

	GameObject();
};