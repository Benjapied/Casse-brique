#include "Game.h"

Game::Game(sf::RenderWindow* renderer) {
	m_renderer = renderer;
    m_bricks =nullptr;
}

void Game::Shoot(Rectangle* cannon, std::vector<Circle*>* balls, sf::Color* col) {
    Circle* boule = new Circle(m_renderer);
    boule->SetSize(10, 10);
    boule->SetColor(col);
    boule->SetPosition(cannon->m_positionX + cannon->m_width * cannon->m_direction.x, cannon->m_positionY + cannon->m_height / 2 * cannon->m_direction.y);
    boule->ChangeDirection(cannon->m_direction.x, cannon->m_direction.y);
    balls->insert(balls->begin(), boule);
}

void Game::DeleteBall(std::vector<Circle*>* balls, int* i) {
    balls->erase(balls->begin() + *i);
}

