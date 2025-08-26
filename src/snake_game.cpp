#include "snake_game.hpp"
#include "main_menu.hpp"

SnakeGame::SnakeGame()
    : m_gameContext(std::make_shared<GameContext>()), m_prevTimePoint(),
      m_windowManager(std::make_unique<WindowManager>()),
      m_assetManager(std::make_shared<AssetManager>()) {}

void SnakeGame::run() {
  m_windowManager->open<MainMenu>(true, m_gameContext, m_assetManager);

  m_prevTimePoint = Clock::now();
  while (m_gameContext->getRunning()) {
    auto currTimePoint = Clock::now();
    std::chrono::duration<float> delta = currTimePoint - m_prevTimePoint;
    auto deltaTime = delta.count();

    m_windowManager->listen();
    m_windowManager->update(deltaTime);
    m_windowManager->draw();
  }
}
