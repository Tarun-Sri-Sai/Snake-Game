#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <array>
#include "snake.hpp"
#include <random>

enum SnakeDirections
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class GamePlay final : public Engine::State
{
public:
    explicit GamePlay(const std::shared_ptr<GameContext> &t_context);

    ~GamePlay() override = default;

    void listen() override;

    void update(const std::chrono::duration<float> &t_deltaTime) override;

    void draw() override;

private:
    std::shared_ptr<GameContext> m_context;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_grassTexture;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_foodTexture;
    std::array<std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>, 4> m_wallTextures;
    SDL_FRect m_grassRect;
    SDL_FRect m_foodRect;
    std::array<SDL_FRect, 4> m_wallRects{};
    Snake m_snake;
    int m_snakeDirection;
    std::chrono::duration<float> m_elapsedTime;
    static std::random_device rd;
    std::mt19937 m_generator;
    int m_score;

    int getRandom(int t_max);

    void setFoodPosition();

    [[nodiscard]] SDL_FPoint getSnakeDirection() const;

    [[nodiscard]] bool isSnakeOnWall() const;
};

#endif  // !GAME_PLAY_HPP
