#include "GameObject.h"
#include <SFML/Graphics.hpp>

#include "Math.h"

using namespace sf;

GameObject::GameObject(const char* type, RenderWindow* renderer)
{
	m_positionX = 0;
	m_positionY = 0;
	m_width = 1;
	m_height = 1;
	m_renderer = renderer;

	m_direction = Vector2f(1,-1);

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
	m_renderer->draw(*m_shape);
}

void GameObject::SetColor(Color* color) 
{
	m_shape->setFillColor(*color);
}

void GameObject::ChangeDirection(float x,float y) {
	m_direction = { x,y };
	this->normaliezVector();
}

void GameObject::normaliezVector() 
{
	Math::normalize(&m_direction.x, &m_direction.y);
}


void GameObject::Move(float Deltatime) {
	this->SetPosition(m_positionX + (m_direction.x * Deltatime * 100.f), m_positionY + (m_direction.y * Deltatime * 100.f));
}
