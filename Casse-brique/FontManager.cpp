#include "FontManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

FontManager::FontManager()
{
};

void FontManager::addFont(const char* path)
{
	m_fontTab.push_back(new sf::Font());

	if (!m_fontTab.back()->loadFromFile(path))
	{
		std::cout << "Loading failed";
		m_fontTab.pop_back();
		return;
	}
};

void FontManager::addText(const char* text, int font)
{
	if (m_fontTab.size() < font + 1)
		return;

	m_texts[text] = new sf::Text();
	m_texts[text]->setFont(*m_fontTab[font]);
	m_texts[text]->setString(text);

};

void FontManager::drawAllTexts(sf::RenderWindow* oWindow)
{
	if (m_texts.empty())
		return;
	for (std::map<std::string, sf::Text*>::iterator i = m_texts.begin(); i != m_texts.end(); i++)
	{
		oWindow->draw(*(i->second));
	}
};

void FontManager::drawText(sf::RenderWindow* oWindow, const char* text)
{
	oWindow->draw(*m_texts[text]);
};

void FontManager::settings(const char* text, int size, sf::Color* color, int x, int y)
{
	m_texts[text]->setCharacterSize(size);
	m_texts[text]->setFillColor(*color);
	m_texts[text]->setPosition(x,y);
};