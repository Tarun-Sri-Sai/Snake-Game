#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "game_context.hpp"
#include "window_manager.hpp"
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

class SnakeGame final {
public:
  SnakeGame();

  ~SnakeGame() = default;
  
  void run();

private:
  Clock::time_point m_prevTimePoint;
  std::unique_ptr<WindowManager> m_windowManager;
  std::shared_ptr<GameContext> m_gameContext;
};

#endif // !SNAKE_GAME_HPP
