#ifndef GAME_HPP
#define GAME_HPP

#include "asset_manager.hpp"
#include "state_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

struct GameContext
{
	std::unique_ptr<Engine::AssetManager> m_assets;
	std::unique_ptr<Engine::StateManager> m_state;
	std::unique_ptr<sf::RenderWindow> m_window;

	GameContext()
	{
		m_assets = std::make_unique<Engine::AssetManager>();
		m_state = std::make_unique<Engine::StateManager>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

class Game
{
public:
	Game();
	~Game();

	void run();
private:
	std::shared_ptr<GameContext> m_context;
	const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);
};

#endif  // !GAME_HPP
