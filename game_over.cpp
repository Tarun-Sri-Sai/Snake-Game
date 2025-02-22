#include "game_over.hpp"
#define FMT_HEADER_ONLY
#include <fmt/format.h>

GameOver::GameOver(std::shared_ptr<GameContext>& t_context, int t_score) :
    m_context(t_context),
    m_titleText(t_context->assets->getFont(TITLE_FONT), 
        "Game over!", 60),
    m_scoreText(t_context->assets->getFont(MENU_FONT), 
        fmt::format("Score: {}", t_score))
{
}

void GameOver::setup()
{
    m_titleText.setOrigin(m_titleText.getLocalBounds().getCenter());
    m_titleText.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f - 150.0f });

    m_scoreText.setOrigin(m_scoreText.getLocalBounds().getCenter());
    m_scoreText.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f });
}

void GameOver::listen()
{
    while (const std::optional event = m_context->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_context->window->close();
        }
    }
}

void GameOver::update(const sf::Time& t_deltaTime)
{
}

void GameOver::present()
{
    m_context->window->clear();
    m_context->window->draw(m_titleText);
    m_context->window->draw(m_scoreText);
    m_context->window->display();
}
