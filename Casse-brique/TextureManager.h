#pragma once
#include <vector>
namespace sf {
	class Texture;
}
class GameObject;

class TextureManager
{
public:
	std::vector <sf::Texture*> m_tab;

	TextureManager();

	void addTexture(const char* path);

	void SetTexture(GameObject* obj, int index);
};

