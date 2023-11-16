#pragma once
#include <vector>
#include <string>
#include <map>

namespace sf {
	class Font;
	class Text;
	class RenderWindow;
}
class GameObject;

class FontManager
{
public:
	std::vector <sf::Font*> m_fontTab;
	std::map<std::string,sf::Text*> m_texts;

	FontManager();

	void addFont(const char* path);

	void addText(const char*, int font);

	void drawAllTexts(sf::RenderWindow* oWindow);

	void drawText(sf::RenderWindow* oWindow, const char* text);
};

