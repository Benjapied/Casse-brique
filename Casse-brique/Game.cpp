#include "Game.h"
#include "FileManager.h"
#include <SFML/Window/Mouse.hpp>
#include "Brick.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include "TextureManager.h"

Game::Game(sf::RenderWindow* renderer) {

    cRed = sf::Color::Red;
    cGreen = sf::Color::Green;
    cBlue = sf::Color::Blue;
    cYellow = sf::Color::Yellow;

    m_ColorArray.push_back(&cRed);
    m_ColorArray.push_back(&cBlue);
    m_ColorArray.push_back(&cGreen);

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
    m_cannon->SetPosition(640, 700);
    m_cannon->SetSize(50, 100);
    m_cannon->SetColor(&cGreen);


    bool mouseState = false;
}

void Game::Shoot() {
        m_bulletArray.push_back(new Bullet(m_renderer, &cYellow, m_cannon));
}

void Game::LoadLevel(const char* path)
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
            y += 58;
            x = 0;
        }
        else if (text[i] == 'b') {
            m_brickArray.push_back(new Brick(m_renderer, m_ColorArray, x, y));
            x += 128;
        }

    }

    SetTextureBrick();
}

void Game::SetTextureBrick()
{
    TextureManager texturePig("img/pig.jpg");

    for (int i = 0; i < m_brickArray.size(); i++)
    {
        texturePig.SetTexture(m_brickArray[i]);
        
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
        if (m_brickArray[i]->m_life == 0) {
            delete m_brickArray[i];
            m_brickArray.erase(m_brickArray.begin() + i);
        }
    }
}


void Game::DeleteBall() {
    for (int i = 0; i < m_bulletArray.size(); i++) {
        if (m_bulletArray[i]->m_positionX >= 980) {
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
        m_renderer->clear();
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
