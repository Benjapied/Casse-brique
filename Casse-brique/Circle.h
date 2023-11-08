#pragma once
#include "GameObject.h"

namespace sf {
	class CircleShape;
	class RenderWindow;
}
class Circle: public GameObject
{
public:
	Circle(sf::RenderWindow* renderer);
};

