#include "Game.h"
#include "FileManager.h"
#include "Brick.h"
#include "Bullet.h"
#include <string>
#include <iostream>

Game::Game(sf::RenderWindow* renderer) {
	m_renderer = renderer;

}

void Game::Shoot(Rectangle* cannon, sf::Color* col) {
    m_bulletArray.push_back(new Bullet(m_renderer, col, cannon));
}

void Game::LoadLevel(const char* path, sf::Color** ColorArray)
{
    std::string text = FileManager::returnText(path);

    std::cout << text;

    float x = 0;
    float y = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
            x += 128;
        else if (text[i] == '\n') {
            y += 50;
            x = 0;
        }
        else if (text[i] == 'b') {
            m_brickArray.push_back(new Brick(this->m_renderer, ColorArray, x, y));
            x += 128;
        }

    }
}

void Game::DrawBricks()
{
    if (!m_brickArray.empty())
    {
        for (int i = 0; i < m_brickArray.size(); i++)
        {
            m_brickArray[i]->Draw();
        }
    }
}

void Game::DeleteBrick(int i) {
    if (m_brickArray[i]->m_life == 0) {
        m_brickArray.erase(m_brickArray.begin() + i);
    }
}


void Game::DeleteBall(int i) {
    m_bulletArray.erase(m_bulletArray.begin() + i);
}
