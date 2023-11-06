#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

GameObject::GameObject(char* type, RenderWindow* renderer)
{
	m_positionX = 0;
	m_positionY = 0;
	m_width = 1;
	m_height = 1;
	m_renderer = renderer;

	//shape can be a rectangle or a circle
	if (type == "rectangle") {
		m_shape = new RectangleShape(Vector2<float>(m_width, m_height));
	}
	else if (type == "circle") {
		m_shape = new CircleShape(m_width);
	}
	this->SetSize(50, 50);
	
};

void GameObject::SetPosition(float x, float y)
{
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_shape->setPosition(x, y);
};

void GameObject::SetSize(float w, float h) 
{
	this->m_shape->setScale(h, w);
}

void GameObject::Draw()
{
	this->m_renderer->draw(this->m_shape);
}
