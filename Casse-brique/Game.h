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

class Game
{
public:

	sf::RenderWindow* m_renderer;
	std::vector<Rectangle*> m_wallArray;
	std::vector<Brick*> m_brickArray;
	std::vector<Bullet*> m_bulletArray;
	TextureManager* m_textureArray;
	Rectangle* m_cannon;
	sf::Color cRed;
	sf::Color cBlue;
	sf::Color cGreen;
	sf::Color cYellow;
	bool m_mouseState;

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
};

