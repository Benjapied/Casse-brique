#pragma once
namespace sf {
	class Texture;
}
class GameObject;

class TextureManager
{
public:
	sf::Texture* m_texture;

	TextureManager(const char* path);

	void SetTexture(GameObject* obj);

	void Resize(GameObject* obj, int x, int y, int w, int h);
};

