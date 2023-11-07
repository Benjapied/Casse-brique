#pragma once
#include <SFML/System.hpp>

namespace sf
{
	class Shape;
	class RenderWindow;
	class Color;
}

class GameObject
{
public:
	float m_positionX;
	float m_positionY;
	float m_width;
	float m_height;
	float m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_rotationAxis;

	sf::Shape* m_shape;
	sf::RenderWindow* m_renderer;

	GameObject(const char* type, sf::RenderWindow* renderer);

	void SetPosition(float x, float y);

	void SetSize(float w, float h);

	void Draw();

	void SetColor(sf::Color* color);

	void SetDirectionMouse(float x, float y);

	void ChangeDirection(float x, float y);

	void Move(float dT);

	void normaliezVector();

	void Rotate(float x, float y);
};