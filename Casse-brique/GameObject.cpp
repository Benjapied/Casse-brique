#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Math.h"

using namespace sf;

GameObject::GameObject( RenderWindow* renderer)
{
	m_positionX = 0;
	m_positionY = 0;
	m_width = 1;
	m_height = 1;
	m_renderer = renderer;
	m_velocity = 1;

	m_direction = Vector2f (0,1);
	m_rotationAxis = Vector2f (0.5, 0);

	//shape can be a rectangle or a circle
	
	m_shape = new CircleShape(m_width);
	
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
};

void GameObject::Draw()
{
	m_renderer->draw(*m_shape);
};

void GameObject::SetColor(Color* color)
{
	m_shape->setFillColor(*color);
};

void GameObject::SetDirectionMouse(float x, float y)
{
	this->ChangeDirection( x - m_positionX, y - m_positionY);
}

void GameObject::Move(float dT)
{
	this->SetPosition(m_positionX + (m_direction.x * dT * 100.f * m_velocity ), m_positionY + (m_direction.y * dT * 100.f * m_velocity));
}

void GameObject::Rotate(float x, float y)
{
	m_shape->setOrigin(m_rotationAxis);
	float mouseAngle = -atan2(x - m_positionX, y - m_positionY) * 180 / 3.14159;
	this->m_shape->setRotation(mouseAngle);
}

void GameObject::ChangeDirection(float x,float y) {
	m_direction = { x,y };
	this->normaliezVector();
}

void GameObject::normaliezVector() 
{
	if (m_direction.x == 0 && m_direction.y == 0)
		return;
	Math::normalize(&m_direction.x, &m_direction.y);
}
