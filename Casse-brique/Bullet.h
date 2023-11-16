#pragma once
#include "Circle.h"
namespace sf
{
	class Texture;
}
class Bullet : public Circle
{
public:
	Bullet(sf::RenderWindow* renderer, sf::Texture* texture, GameObject* Cannon);

};
