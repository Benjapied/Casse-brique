#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* renderer, sf::Color* Col, GameObject* Cannon) : Circle(renderer) {
    m_renderer = renderer;
    this->SetSize(15, 15);
    this->SetColor(Col);
    this->SetPosition(Cannon->m_positionX + Cannon->m_width * Cannon->m_direction.x, Cannon->m_positionY + Cannon->m_height / 2 * Cannon->m_direction.y);
    this->ChangeDirection(Cannon->m_direction.x, Cannon->m_direction.y);
}
