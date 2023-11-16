#pragma once
#include "Rectangle.h"
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Brick.h"
#include "Bullet.h"
#include <vector>

class Brick;
class Color;
class TextureManager;
class FontManager;

class Game
{
public:

	sf::RenderWindow* m_renderer;
	std::vector<Rectangle*> m_wallArray;
	std::vector<Brick*> m_brickArray;
	std::vector<Bullet*> m_bulletArray;

	TextureManager* m_textureArray;
	FontManager* m_fontManager;

	Rectangle* m_cannon;
	Rectangle* m_background;
	Rectangle* m_crossair;
	sf::Color cRed;
	sf::Color cBlue;
	sf::Color cGreen;
	sf::Color cYellow;
	bool m_mouseState;
	int m_bulletLimit;

	Game(sf::RenderWindow* renderer);

	void Shoot();

	void LoadLevel(const char* path);

	void BulletMove(float dT);
	void BulletWallCol();
	void BulletBrickCol();
	void DrawBricks();
	void DrawBullets();
	void DeleteBrick();
	void DeleteBall();
	void CannonRotate(sf::Vector2i localPosition);
	void GameLoop();
	bool WinCondition();
	bool LooseCondition();
};

