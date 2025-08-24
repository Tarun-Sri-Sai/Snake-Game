#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "window_manager.hpp"

class SnakeGame {
public:
  SnakeGame();
  void run();

private:
  std::unique_ptr<WindowManager> m_windowManager;
};

#endif // !SNAKE_GAME_HPP
