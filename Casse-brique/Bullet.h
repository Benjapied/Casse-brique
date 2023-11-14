#pragma once
#include "Circle.h"
class Color;
class Bullet : public Circle
{
public:
	Bullet(sf::RenderWindow* renderer, sf::Color* Col, GameObject* Cannon);

};
