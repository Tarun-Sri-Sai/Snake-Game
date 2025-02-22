#include "main_menu.hpp"
#include "game_play.hpp"

MainMenu::MainMenu(std::shared_ptr<GameContext>& t_context) :
	m_context(t_context),
	m_gameTitle(t_context->m_assets->getFont(TITLE_FONT), "Snake Game", 60),
	m_optionsIndex(0),
	m_optionSelected(false),
	m_options{
		sf::Text(m_context->m_assets->getFont(MENU_FONT), "Play"),
		sf::Text(m_context->m_assets->getFont(MENU_FONT), "Exit") }
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::setup()
{
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().getCenter());
	m_gameTitle.setPosition({
		m_context->m_window->getSize().x / 2.0f,
		m_context->m_window->getSize().y / 2.0f - 150.0f });

	for (size_t optionsLength = m_options.size(), i = 0; i < optionsLength; i++)
	{
		m_options[i].setOrigin(m_options[i].getLocalBounds().getCenter());
		m_options[i].setPosition({
			m_context->m_window->getSize().x / 2.0f,
			m_context->m_window->getSize().y / 2.0f + ((int)i * 60) });
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
		else if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->code)
			{
			case sf::Keyboard::Key::Up:
			case sf::Keyboard::Key::W:
				m_optionsIndex = std::max(m_optionsIndex - 1, 0);
				break;
			case sf::Keyboard::Key::Down:
			case sf::Keyboard::Key::S:
				m_optionsIndex = std::min(m_optionsIndex + 1, (int)m_options.size() - 1);
				break;
			case sf::Keyboard::Key::Enter:
				m_optionSelected = true;
				break;
			}
		}
	}
}

void MainMenu::update(sf::Time t_deltaTime)
{
	for (size_t optionsLength = m_options.size(), i = 0; i < optionsLength; i++)
	{
		if (i == m_optionsIndex)
		{
			m_options[i].setFillColor(sf::Color::Yellow);
		}
		else
		{
			m_options[i].setFillColor(sf::Color::White);
		}
	}

	if (m_optionSelected)
	{
		switch (m_optionsIndex) {
		case PLAY:
			m_context->m_states->add(std::make_unique<GamePlay>(m_context));
			break;
		case EXIT:
			m_context->m_window->close();
			break;
		}
		m_optionSelected = false;
	}
}

void MainMenu::present()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_gameTitle);
	for (auto& option : m_options)
	{
		m_context->m_window->draw(option);
	}

	m_context->m_window->display();
}
