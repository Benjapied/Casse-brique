#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Math.h"

using namespace sf;

GameObject::GameObject(RenderWindow* renderer)
{
	m_positionX = 0;
	m_positionY = 0;
	m_width = 1;
	m_height = 1;
	m_renderer = renderer;
	m_velocity = 3;
	m_direction = Vector2f (0,1);
	m_rotationAxis = Vector2f (0.5, 0);
	m_bounce = 0;
	m_shape = nullptr;
};

void GameObject::SetPosition(float x, float y)
{
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_shape->setPosition(x, y);
};

void GameObject::SetSize(float w, float h)
{
	this->m_shape->setScale(w, h);
	this->m_width = w;
	this->m_height = h;
};

void GameObject::SetBounce(bool bounce)
{
	this->m_bounce = true;
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

int GameObject::Colision(GameObject* obj) {
	int sens = 0;

	int referenceX;
	int referenceY;

	bool xAxis = false;
	bool yAxis = false;
	if (this->m_width <= obj->m_width)
	{
		if (this->m_positionX <= obj->m_positionX + obj->m_width 
		&&  this->m_positionX >= obj->m_positionX 
		||	this->m_positionX + this->m_width <= obj->m_positionX + obj->m_width
		&&  this->m_positionX + this->m_width >= obj->m_positionX
		)
		{
			xAxis = true;
		}
	}
	else if (this->m_width > obj->m_width)
	{
		if (obj->m_positionX <= this->m_positionX + this->m_width
			&& obj->m_positionX >= this->m_positionX
			|| obj->m_positionX + obj->m_width <= this->m_positionX + this->m_width
			&& obj->m_positionX + obj->m_width >= this->m_positionX
			)
		{
			xAxis = true;
		}
	}

	if (this->m_height <= obj->m_height)
	{
		if ((this->m_positionY <= obj->m_positionY + obj->m_height
			&& this->m_positionY >= obj->m_positionY)
			|| (this->m_positionY + this->m_height <= obj->m_positionY + obj->m_height
			&& this->m_positionY + this->m_height >= obj->m_positionY)
			)
		{
			yAxis = true;
		}
	}
	else if (this->m_height > obj->m_height)
	{
		if ((obj->m_positionY <= this->m_positionY + this->m_height
			&& obj->m_positionY >= this->m_positionY)
			|| (obj->m_positionY + obj->m_height <= this->m_positionY + this->m_height
			&& obj->m_positionY + obj->m_height >= this->m_positionY)
			)
		{
			yAxis = true;
		}
	}

	if (yAxis == true && xAxis == true)
	{
		referenceX = Math::min(Math::abs(this->m_positionX - (obj->m_positionX + obj->m_width)), Math::abs(this->m_positionX + this->m_width - obj->m_positionX));
		referenceY = Math::min(Math::abs(this->m_positionY - (obj->m_positionY + obj->m_height)), Math::abs(this->m_positionY + this->m_height - obj->m_positionY));
		//if vertical bounce, return 1 
		//if horizontal bounce, return 2
		if (referenceX <= referenceY)
			return 1;
		else
			return 2;
	}
	return sens;
	
}

void GameObject::Bounce(int i)
{
	if (i == 0)
		return;
	else if (i == 1)
		this->ChangeDirection(-(m_direction.x), m_direction.y);
	else if (i == 2)
		this->ChangeDirection(m_direction.x, -(m_direction.y));
}