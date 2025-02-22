#include "game.hpp"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

Game::Game() : m_context(std::make_shared<GameContext>())
{
	m_context->m_window->create(sf::VideoMode({ 960, 540 }), "Snake Game", sf::Style::Close);
}

Game::~Game()
{
}

void Game::run()
{
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;
	sf::Time timeSinceLastFrame{ sf::Time::Zero };

	while (m_context->m_window->isOpen())
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

			while (const std::optional event = m_context->m_window->pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					m_context->m_window->close();
				}
			}

			m_context->m_window->clear();
			m_context->m_window->draw(shape);
			m_context->m_window->display();
		}
	}
}
