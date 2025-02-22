#include "game_play.hpp"
#include <random>
#include <iostream>

GamePlay::GamePlay(std::shared_ptr<GameContext>& t_context) :
	m_context(t_context),
	m_grass(m_context->m_assets->getTexture(GRASS)),
	m_food(m_context->m_assets->getTexture(FOOD)),
	m_walls{
		sf::Sprite(m_context->m_assets->getTexture(WALL)),
		sf::Sprite(m_context->m_assets->getTexture(WALL)),
		sf::Sprite(m_context->m_assets->getTexture(WALL)),
		sf::Sprite(m_context->m_assets->getTexture(WALL)) }
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::setup()
{
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	sf::Vector2u windowSize = m_context->m_window->getSize();

	m_walls[0].setTextureRect({ { 0, 0 }, { (int)windowSize.x, 16 } });
	m_walls[0].setPosition({ 0.0f, 0.0f });

	m_walls[1].setTextureRect({ { 0, 0 }, { (int)windowSize.x, 16 } });
	m_walls[1].setPosition({ 0.0f, (float)windowSize.y - 16.0f });

	m_walls[2].setTextureRect({ { 0, 0 }, { (int)windowSize.y - 32, 16 } });
	m_walls[2].setPosition({ 16.0f, 16.0f });
	m_walls[2].setRotation(sf::degrees(90));

	m_walls[3].setTextureRect({ { 0, 0 }, { (int)windowSize.y - 32, 16 } });
	m_walls[3].setPosition({ (float)windowSize.x, 16.0f });
	m_walls[3].setRotation(sf::degrees(90));

	m_food.setPosition(getFoodPosition());
}

sf::Vector2<float> GamePlay::getFoodPosition()
{
	return {
		(float)getRandom(1, (960 - 32) / 16) * 16,
		(float)getRandom(1, (540 - 32) / 16) * 16 };
}

void GamePlay::listen()
{
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_context->m_window->close();
		}
	}
}

void GamePlay::update(sf::Time t_deltaTime)
{
}

void GamePlay::present()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_grass);
	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}
	m_context->m_window->draw(m_food);

	m_context->m_window->display();
}

void GamePlay::pause()
{
}

void GamePlay::resume()
{
}

int GamePlay::getRandom(int min, int max) {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}
