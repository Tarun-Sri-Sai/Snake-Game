#include "game_context.hpp"

GameContext::GameContext()
    : m_running(true) {
}

bool GameContext::getRunning() const {
  return m_running;
}

void GameContext::setRunning(bool t_running) {
  m_running = t_running;
}
