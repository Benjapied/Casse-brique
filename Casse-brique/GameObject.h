#pragma once

namespace sf
{
	class Shape;
	class RenderWindow;
}

class GameObject
{
public:
	float m_positionX;
	float m_positionY;
	float m_width;
	float m_height;
	sf::Shape* m_shape;
	sf::RenderWindow* m_renderer;

	GameObject(char* type, sf::RenderWindow* renderer);

	void SetPosition(float x, float y);

	void SetSize(float w, float h);

	void Draw();
};