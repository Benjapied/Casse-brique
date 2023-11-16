#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>

TextureManager::TextureManager()
{

};

void TextureManager::addTexture(const char* path)
{
	m_tab.push_back(new sf::Texture());

	if (!m_tab.back()->loadFromFile(path))
	{
		std::cout << "Loading failed";
		m_tab.pop_back();
		return;
	}
	
}

