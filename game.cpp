#include "game.hpp"
#include <thread>
#include <chrono>
#include "main_menu.hpp"
using namespace std::chrono_literals;

Game::Game() : m_context(std::make_shared<GameContext>())
{
}

Game::~Game()
{
}

void Game::setup()
{
	m_context->m_window->create(sf::VideoMode({ 960, 540 }), "Snake Game", sf::Style::Close);

	m_context->m_assets->addFont(TITLE_FONT, "KnightWarrior-w16n8.otf");
	m_context->m_assets->addFont(MENU_FONT, "SupremeSpike-KVO8D.otf");

	m_context->m_assets->addTexture(GRASS, "grass.png", true);
	m_context->m_assets->addTexture(WALL, "wall.png", true);
	m_context->m_assets->addTexture(WALL_90, "wall_90.png", true);
	m_context->m_assets->addTexture(FOOD, "food.png");

	m_context->m_states->add(std::make_unique<MainMenu>(m_context));
}

void Game::run()
{
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

			m_context->m_states->process();
			m_context->m_states->get()->listen();
			m_context->m_states->get()->update(FRAME_TIME);
			m_context->m_states->get()->present();
		}
	}
}
