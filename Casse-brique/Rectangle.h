#pragma once
#include "GameObject.h"
namespace sf {
	class RenderWindow;
}

class Rectangle : public GameObject
{
public:
	Rectangle(sf::RenderWindow* renderer);
};