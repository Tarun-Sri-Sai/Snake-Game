#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <array>

class GamePlay : public Engine::State
{
public:
	GamePlay(std::shared_ptr<GameContext>& t_context);
	~GamePlay();

	void setup() override;
	void listen() override;
	void update(sf::Time t_deltaTime) override;
	void present() override;

	void pause() override;
	void resume() override;
private:
	std::shared_ptr<GameContext> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;
	std::array<sf::Sprite, 4> m_walls;
	// TODO: Add snake

	int getRandom(int min, int max);
	sf::Vector2<float> getFoodPosition();
};

#endif  // !GAME_PLAY_HPP
