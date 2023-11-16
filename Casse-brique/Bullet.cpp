#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* renderer, sf::Texture* texture, GameObject* Cannon) : Circle(renderer) {
    m_renderer = renderer;
    this->SetTexture(texture);
    this->SetSize(30,30);
    this->SetPosition(Cannon->m_positionX + Cannon->m_width * Cannon->m_direction.x, Cannon->m_positionY + Cannon->m_height / 2 * Cannon->m_direction.y);
    this->ChangeDirection(Cannon->m_direction.x, Cannon->m_direction.y);
}
