#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include "Brick.h"
#include "Bullet.h"
#include <vector>

class Brick;

class Game
{
public:

	sf::RenderWindow* m_renderer;
	std::vector<Brick*> m_brickArray;
	std::vector<Bullet*> m_bulletArray;

	Game(sf::RenderWindow* renderer);

	void Shoot(Rectangle* cannon, sf::Color* col);

	void LoadLevel(const char* path, sf::Color** ColorArray);

	void DrawBricks();
	void DeleteBrick(int i);
	void DeleteBall(int i);
};

