#include "Game.h"
#include "FileManager.h"
#include <SFML/Window/Mouse.hpp>
#include "Brick.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "FontManager.h"
#include <vector>

Game::Game(sf::RenderWindow* renderer) {

    cRed = sf::Color::Red;
    cGreen = sf::Color::Green;
    cBlue = sf::Color::Blue;
    cYellow = sf::Color::Yellow;
    cBlack = sf::Color::Black;

    m_bulletLimit = 20;

    m_textureArray = new TextureManager();
    m_textureArray->addTexture("img/pig.jpg");
    m_textureArray->addTexture("img/pigLow.jpg");
    m_textureArray->addTexture("img/background.jpg");
    m_textureArray->addTexture("img/red.png");
    m_textureArray->addTexture("img/slingShot.png");
    m_textureArray->addTexture("img/crossair.png");
    m_textureArray->addTexture("img/win.png");
    m_textureArray->addTexture("img/loose.jpg");

    m_fontManager = new FontManager();
    m_fontManager->addFont("font/angrybirds-regular.ttf");
    m_fontManager->addText("Gagn� !", 0);
    m_fontManager->settings("Gagn� !", 100, &cBlack, 500, 350);
    m_fontManager->addText("Perdu !", 0);
    m_fontManager->settings("Perdu !", 100, &cBlack, 500, 350);
    m_fontManager->addText("Balles maximum: 20", 0);
    m_fontManager->settings("Balles maximum: 20", 20, &cBlack, 20, 15);


	m_renderer = renderer;
    Rectangle* wallUp = new Rectangle(m_renderer);
    wallUp->SetPosition(0, -1);
    wallUp->SetSize(1280, 10);

    Rectangle* wallLeft = new Rectangle(m_renderer);
    wallLeft->SetPosition(-1, 0);
    wallLeft->SetSize(10, 960);

    Rectangle* wallRight = new Rectangle(m_renderer);
    wallRight->SetPosition(1280, 0);
    wallRight->SetSize(10, 960);

    m_wallArray = { wallUp,wallLeft,wallRight };

    m_cannon = new Rectangle(m_renderer);
    m_cannon->SetPosition(640, 765);
    m_cannon->SetSize(100, 180);
    m_cannon->SetTexture(m_textureArray->m_tab[4]);

    m_background = new Rectangle(renderer);
    m_background->SetPosition(0, 0);
    m_background->SetSize(1280, 960);
    m_background->SetTexture(m_textureArray->m_tab[2]);

    m_backgroundWin = new Rectangle(renderer);
    m_backgroundWin->SetPosition(0, 0);
    m_backgroundWin->SetSize(1280, 960);
    m_backgroundWin->SetTexture(m_textureArray->m_tab[6]);

    m_backgroundLoose = new Rectangle(renderer);
    m_backgroundLoose->SetPosition(0, 0);
    m_backgroundLoose->SetSize(1280, 960);
    m_backgroundLoose->SetTexture(m_textureArray->m_tab[7]);

    m_crossair = new Rectangle(renderer);
    m_crossair->SetPosition(0, 0);
    m_crossair->SetSize(50, 50);
    m_crossair->SetSpeed(10);
    m_crossair->SetTexture(m_textureArray->m_tab[5]);

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

bool Game::LooseCondition() {
    if (m_brickArray.size() > 0 && m_bulletLimit == 0 && m_bulletArray.size() == 0 ) {
        return true;
    }
    return false;
}

void Game::GameLoop() {
    sf::Clock oClock;
    float fDeltaTime = 1;
    float lastTime = 0;
    float clock = 0;

    bool win = false;
    bool loose = false;

    while (m_renderer->isOpen())
    {
        m_renderer->setFramerateLimit(60);
        sf::Event oEvent;
        while (m_renderer->pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                m_renderer->close();
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(*m_renderer);

        if (oEvent.type == sf::Event::MouseButtonPressed) {
            if (m_mouseState == false && m_bulletLimit > 0) {
                if (oEvent.mouseButton.button == sf::Mouse::Left) {
                    Shoot();
                    m_mouseState = true;
                    m_bulletLimit -= 1;
                }
            }
        }
        else if (oEvent.type == sf::Event::MouseButtonReleased) {
            if (m_bulletArray.size() == 0) {
                m_mouseState = false;
            }
        }
        if (WinCondition() == true) {
            win = true;
            while (win)
            {
                if (oEvent.type == sf::Event::KeyPressed) {
                    if (oEvent.key.code == sf::Keyboard::Escape) {
                        win = false;
                    }
                }
                m_renderer->clear();
                m_backgroundWin->Draw();
                m_fontManager->drawText(m_renderer, "Gagn� !");
                m_renderer->display();
            }
        }
        if (LooseCondition() == true) {
            loose = true;
            while (loose)
            {
                if (oEvent.type == sf::Event::KeyPressed) {
                    if (oEvent.key.code == sf::Keyboard::Escape) {
                        loose = false;
                    }
                }
                m_renderer->clear();
                m_backgroundLoose->Draw();
                m_fontManager->drawText(m_renderer, "Perdu !");
                m_renderer->display();
            }
        }
        m_renderer->clear();
        m_background->Draw();
        m_crossair->SetPosition(localPosition.x-25, localPosition.y-25);
        CannonRotate(localPosition);
        BulletMove(fDeltaTime);
        DeleteBall();
        DeleteBrick();
        BulletBrickCol();
        BulletWallCol();
        DrawBullets();
        DrawBricks();
        m_cannon->Draw();
        m_fontManager->drawText(m_renderer, "Balles maximum: 20");
        m_crossair->Draw();
        m_renderer->display();
        clock += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
        float currentTime = fDeltaTime;
        float fps = 1.f / currentTime;
        lastTime = currentTime;
    }
    
}
