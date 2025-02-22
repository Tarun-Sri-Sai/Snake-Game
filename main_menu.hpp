#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <array>

enum Options
{
	PLAY = 0, 
	EXIT
};

class MainMenu : public Engine::State
{
public:
	MainMenu(std::shared_ptr<GameContext>& t_context);
	~MainMenu();

	void setup() override;
	void listen() override;
	void update(sf::Time t_deltaTime) override;
	void present() override;
private:
	std::shared_ptr<GameContext> m_context;
	sf::Text m_gameTitle;
	std::array<sf::Text, 2> m_options;
	int m_optionsIndex;
	bool m_optionSelected;
};

#endif  // !MAIN_MENU_HPP
