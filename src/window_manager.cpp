#include "window_manager.hpp"
#include "constants.hpp"
#include <SDL3/SDL_init.h>
#include <fmt/format.h>
#include <stdexcept>

WindowManager::WindowManager() : m_stack() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        fmt::format("Failed to initialize SDL: {}", SDL_GetError()));
  }

  SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, 960, 540, 0);
  if (!window) {
    SDL_Quit();
    throw std::runtime_error(
        fmt::format("Failed to create window: {}", SDL_GetError()));
  }
  m_window = std::shared_ptr<SDL_Window>(window, SDL_DestroyWindow);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    m_window.reset();
    SDL_Quit();
    throw std::runtime_error(
        fmt::format("Failed to create renderer: {}", SDL_GetError()));
  }
  m_renderer = std::shared_ptr<SDL_Renderer>(renderer, SDL_DestroyRenderer);

  m_textRenderer = std::make_shared<TextRenderer>(m_renderer);
}

WindowManager::~WindowManager() {
  m_renderer.reset();
  m_window.reset();
  SDL_Quit();
}

void WindowManager::listen() {
  if (m_stack.empty()) {
    return;
  }

  m_stack.top().get()->listen();
}

void WindowManager::update(float t_deltaTime) {
  if (m_stack.empty()) {
    return;
  }

  m_stack.top().get()->update(t_deltaTime);
}

void WindowManager::draw() {
  if (m_stack.empty()) {
    return;
  }

  m_stack.top().get()->draw();
}
