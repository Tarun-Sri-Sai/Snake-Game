#include "main_menu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameContext>& t_context) :
	m_context(t_context),
	m_gameTitle(t_context->m_assets->getFont(TITLE_FONT), "Snake Game", 60)
{
}

MainMenu::~MainMenu()
{
	m_options.clear();
}

void MainMenu::setup()
{
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().getCenter());
	m_gameTitle.setPosition(sf::Vector2f(
		m_context->m_window->getSize().x / 2, 
		m_context->m_window->getSize().y / 2 - 150.0f ));

	m_options.emplace_back(std::make_unique<sf::Text>(m_context->m_assets->getFont(MENU_FONT), "Play"));

	m_options.emplace_back(std::make_unique<sf::Text>(m_context->m_assets->getFont(MENU_FONT), "Exit"));

	for (int optionsLength = m_options.size(), i = 0; i < optionsLength; i++)
	{
		m_options[i]->setOrigin(m_options[i]->getLocalBounds().getCenter());
		m_options[i]->setPosition(sf::Vector2f(
			m_context->m_window->getSize().x / 2,
			m_context->m_window->getSize().y / 2 + (i * 60)));
	}
}

void MainMenu::listen()
{
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_context->m_window->close();
		}
	}
}

void MainMenu::update(sf::Time t_deltaTime)
{
}

void MainMenu::present()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameTitle);
	for (auto& option : m_options)
	{
		m_context->m_window->draw(*option.get());
	}
	m_context->m_window->display();
}
