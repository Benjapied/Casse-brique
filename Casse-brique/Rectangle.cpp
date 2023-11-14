#include "Rectangle.h"
#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>

Rectangle::Rectangle(sf::RenderWindow* renderer) : GameObject(renderer) {
	//On place un objet rectangle dans l'attribut shape
	m_shape = new sf::RectangleShape(sf::Vector2<float>(m_width, m_height));
};