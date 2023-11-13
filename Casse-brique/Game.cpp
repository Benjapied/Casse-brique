#include "Game.h"
#include "FileManager.h"
#include "Brick.h"
#include <string>

Game::Game(sf::RenderWindow* renderer) {
	m_renderer = renderer;
    m_brickArray = nullptr;

}

void Game::Shoot(Rectangle* cannon, std::vector<Circle*>* balls, sf::Color* col) {
    Circle* boule = new Circle(m_renderer);
    boule->SetSize(10, 10);
    boule->SetColor(col);
    boule->SetPosition(cannon->m_positionX + cannon->m_width * cannon->m_direction.x, cannon->m_positionY + cannon->m_height / 2 * cannon->m_direction.y);
    boule->ChangeDirection(cannon->m_direction.x, cannon->m_direction.y);
    balls->insert(balls->begin(), boule);
}

void Game::LoadLevel(const char* path, sf::Color** ColorArray)
{
    std::string text = FileManager::returnText(path);

    float x = 0;
    float y = 0;

    for (int i = 0; i < 72; i++)
    {
        if (text[i] == ' ')
            x += 128;
        else if (text[i] == '\n') {
            y += 50;
        }
        else if (text[i] == 'b') {
            m_brickArray->push_back(new Brick(this->m_renderer, ColorArray, x, y));

        }

    }
}

void Game::DrawBricks()
{
    for (int i = 0; i < m_brickArray->size(); i++)
    {
        m_brickArray->at(i)->Draw();
    }
}