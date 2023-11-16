#include "Game.h"
#include "FileManager.h"
#include <SFML/Window/Mouse.hpp>
#include "Brick.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include <vector>

Game::Game(sf::RenderWindow* renderer) {

    cRed = sf::Color::Red;
    cGreen = sf::Color::Green;
    cBlue = sf::Color::Blue;
    cYellow = sf::Color::Yellow;

    m_textureArray = new TextureManager();
    m_textureArray->addTexture("img/pig.jpg");
    m_textureArray->addTexture("img/pigLow.jpg");
    m_textureArray->addTexture("img/background.jpg");
    m_textureArray->addTexture("img/red.png");
    m_textureArray->addTexture("img/slingShot.png");

	m_renderer = renderer;
    Rectangle* wallUp = new Rectangle(m_renderer);
    wallUp->SetPosition(0, -1);
    wallUp->SetSize(1280, 1);

    Rectangle* wallLeft = new Rectangle(m_renderer);
    wallLeft->SetPosition(-1, 0);
    wallLeft->SetSize(1, 960);

    Rectangle* wallRight = new Rectangle(m_renderer);
    wallRight->SetPosition(1280, 0);
    wallRight->SetSize(1, 960);

    m_wallArray = { wallUp,wallLeft,wallRight };

    m_cannon = new Rectangle(m_renderer);
    m_cannon->SetPosition(640, 765);
    m_cannon->SetSize(100, 180);
    m_cannon->SetTexture(m_textureArray->m_tab[4]);

    m_background = new Rectangle(renderer);
    m_background->SetPosition(0, 0);
    m_background->SetSize(1280, 960);
    m_background->SetTexture(m_textureArray->m_tab[2]);

    bool mouseState = false;
}

void Game::Shoot() {
        m_bulletArray.push_back(new Bullet(m_renderer, m_textureArray->m_tab[3], m_cannon));
}

void Game::LoadLevel(const char* path)
{
    std::string text = FileManager::returnText(path);

    std::vector<sf::Texture*> pigArray;
    pigArray.push_back(this->m_textureArray->m_tab[1]);
    pigArray.push_back(this->m_textureArray->m_tab[0]);

    float x = 0;
    float y = 0;
    

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
            x += 80;
        else if (text[i] == '\n') {
            y += 48;
            x = 0;
        }
        else if (text[i] == 'b') {
            m_brickArray.push_back(new Brick(m_renderer, pigArray, x+4, y+2));
            x += 80;
        }

    }
}

void Game::BulletMove(float dT) {
    for (int i = 0; i < m_bulletArray.size(); i++) {
        m_bulletArray[i]->Move(dT);
    }
}

void Game::BulletWallCol() {
    for (int i = 0; i < m_bulletArray.size(); i++) {
        for (int j = 0; j < m_wallArray.size(); j++) {
            m_bulletArray[i]->Bounce(m_bulletArray[i]->Colision(m_wallArray[j]));
        }
    }
}

void Game::BulletBrickCol() {
    for (int i = 0; i < m_bulletArray.size(); i++) {
        for (int j = 0; j < m_brickArray.size(); j++) {
            m_bulletArray[i]->Bounce(m_bulletArray[i]->Colision(m_brickArray[j]));
            if (m_bulletArray[i]->Colision(m_brickArray[j]) != 0) {
                m_brickArray[j]->Hit();
            }
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

void Game::DrawBullets()
{
    if (!m_bulletArray.empty())
    {
        for (int i = 0; i < m_bulletArray.size(); i++)
        {
            m_bulletArray[i]->Draw();
        }
    }
}

void Game::DeleteBrick() {
    for (int i = 0; i < m_brickArray.size(); i++) {
        if (m_brickArray[i]->m_life < 1) {
            delete m_brickArray[i];
            m_brickArray.erase(m_brickArray.begin() + i);
        }
    }
}


void Game::DeleteBall() {
    for (int i = 0; i < m_bulletArray.size(); i++) {
        if (m_bulletArray[i]->m_positionY >= 980) {
            delete m_bulletArray[i];
            m_bulletArray.erase(m_bulletArray.begin() + i);
        }
    }
}

void Game::CannonRotate(sf::Vector2i localPosition) {
    if (localPosition.y < m_cannon->m_positionY - m_cannon->m_width) {
        m_cannon->Rotate(localPosition.x, localPosition.y);
        m_cannon->ChangeDirection(localPosition.x - m_cannon->m_positionX, localPosition.y - m_cannon->m_positionY);
    }
}

bool Game::WinCondition()
{
    if (m_brickArray.size() == 0) {
        return true;
    }
    return false;
}

void Game::GameLoop() {
    sf::Clock oClock;
    float fDeltaTime = 1;
    float clock = 0;
    while (m_renderer->isOpen())
    {
        sf::Event oEvent;
        while (m_renderer->pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                m_renderer->close();
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(*m_renderer);

        if (oEvent.type == sf::Event::MouseButtonPressed) {
            if (m_mouseState == false) {
                if (oEvent.mouseButton.button == sf::Mouse::Left) {
                    Shoot();
                    m_mouseState = true;
                }
            }
        }
        else if (oEvent.type == sf::Event::MouseButtonReleased) {
            
            m_mouseState = false;
        }
        if (WinCondition() == true) {
            std::cout << std::endl;
            std::cout << "You Won" << std::endl;
            break;
        }
        m_renderer->clear();
        m_background->Draw();
        CannonRotate(localPosition);
        BulletMove(fDeltaTime);
        DeleteBall();
        DeleteBrick();
        BulletBrickCol();
        BulletWallCol();
        DrawBullets();
        DrawBricks();
        
        m_cannon->Draw();
        m_renderer->display();
        clock += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }
    
}
