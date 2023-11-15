#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"

TextureManager::TextureManager(const char* path)
{
	m_texture = new sf::Texture();
	if (!m_texture->loadFromFile(path))
		return;

};

void TextureManager::SetTexture(GameObject* obj)
{
	obj->m_shape->setTexture(m_texture);
};

void TextureManager::Resize(GameObject* obj, int x, int y, int w, int h)
{
	obj->m_shape->setTextureRect(sf::IntRect(x,y,h,w));
}