#include "Circle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Circle::Circle(sf::RenderWindow* renderer): GameObject(renderer) {
	m_shape = new sf::CircleShape(m_width);
	if (m_shape == nullptr)
		std::cout << "Erreur de charegement du cercle";
}