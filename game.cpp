#include "game.hpp"
#include <thread>
#include <chrono>
#include "main_menu.hpp"
using namespace std::chrono_literals;

Game::Game() : m_context(std::make_shared<GameContext>())
{
    m_context->window->create(sf::VideoMode({ 960, 544 }), "Snake Game", sf::Style::Close);

    m_context->assets->addFont(TITLE_FONT, "knight_warrior.otf");
    m_context->assets->addFont(MENU_FONT, "supreme_spike.otf");

    m_context->assets->addTexture(GRASS, "grass.png", true);
    m_context->assets->addTexture(WALL, "wall.png", true);
    m_context->assets->addTexture(FOOD, "food.png");
    m_context->assets->addTexture(SNAKE, "snake.png");

    m_context->states->add(std::make_unique<MainMenu>(m_context));
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame{ sf::Time::Zero };

    while (m_context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        if (timeSinceLastFrame < FRAME_TIME)
        {
            std::this_thread::sleep_for(5ms);
            continue;
        }

        while (timeSinceLastFrame >= FRAME_TIME)
        {
            timeSinceLastFrame -= FRAME_TIME;

            m_context->states->update();
            m_context->states->get()->listen();
            m_context->states->get()->update(FRAME_TIME);
            m_context->states->get()->present();
        }
    }
}
