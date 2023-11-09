#include "Circle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Circle::Circle(sf::RenderWindow* renderer): GameObject(renderer) {
	m_shape = new sf::CircleShape(m_width/2);
	m_rotationAxis = sf::Vector2f(0.5, 0.5);
}