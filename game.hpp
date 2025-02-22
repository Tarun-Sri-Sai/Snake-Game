#ifndef GAME_HPP
#define GAME_HPP

#include "asset_manager.hpp"
#include "state_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

enum GameAssets
{
	TITLE_FONT = 0,
	MENU_FONT
};

struct GameContext
{
	std::unique_ptr<Engine::AssetManager> m_assets;
	std::unique_ptr<Engine::StateManager> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;

	GameContext()
	{
		m_assets = std::make_unique<Engine::AssetManager>();
		m_states = std::make_unique<Engine::StateManager>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

class Game
{
public:
	Game();
	~Game();

	void setup();
	void run();
private:
	std::shared_ptr<GameContext> m_context;
	const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);
};

#endif  // !GAME_HPP
