#include "game_context.hpp"
#include "SDL3/SDL_init.h"
#include <fmt/format.h>
#include <stdexcept>

GameContext::GameContext()
    : m_running(true), m_window(nullptr, SDL_DestroyWindow),
      m_renderer(nullptr, SDL_DestroyRenderer) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        fmt::format("Failed to initialize SDL: %s", SDL_GetError()));
  }

  m_window.reset(SDL_CreateWindow("Snake Game", 960, 540, 0));
  if (!m_window) {
    SDL_Quit();
    throw std::runtime_error(
        fmt::format("Failed to create window: %s", SDL_GetError()));
  }

  m_renderer.reset(SDL_CreateRenderer(m_window.get(), nullptr));
  if (!m_renderer) {
    m_window.reset();
    SDL_Quit();
    throw std::runtime_error(
        fmt::format("Failed to create renderer: %s", SDL_GetError()));
  }
}

GameContext::~GameContext() {
  m_renderer.reset();
  m_window.reset();
  SDL_Quit();
}

bool GameContext::getRunning() const {
  return m_running;
}

void GameContext::setRunning(bool t_running) {
  m_running = t_running;
}

SDL_Window *GameContext::getWindow() const {
  return m_window.get();
}

SDL_Renderer *GameContext::getRenderer() const {
  return m_renderer.get();
}
