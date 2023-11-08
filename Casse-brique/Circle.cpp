#include "Circle.h"
#include <SFML/Graphics.hpp>

Circle::Circle(sf::RenderWindow* renderer): GameObject(renderer) {
	m_shape = new sf::CircleShape(m_width);
}