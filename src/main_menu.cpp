#include "main_menu.hpp"
#include "constants.hpp"
#include <SDL3/SDL_events.h>

MainMenu::MainMenu(const std::shared_ptr<SDL_Renderer> &t_renderer,
                   const std::shared_ptr<RenderManager> &t_renderManager,
                   const std::shared_ptr<GameContext> &t_gameContext,
                   const std::shared_ptr<AssetManager> &t_assetManager)
    : m_renderer(t_renderer), m_renderManager(t_renderManager),
      m_gameContext(t_gameContext), m_assetManager(t_assetManager),
      m_title(t_assetManager->getFont(FONT_ROBOTO_BOLD, 144), WINDOW_TITLE,
              {255, 255, 255, 255}, 120.f, 90.f),
      m_play(t_assetManager->getFont(FONT_ROBOTO_REGULAR, 48), PLAY_BUTTON,
             {255, 255, 255, 255}, 440.f, 300.f),
      m_playPressed(false) {}

MainMenu::~MainMenu() {}

void MainMenu::listen() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      m_gameContext->setRunning(false);
      break;
    case SDL_EVENT_KEY_DOWN:
      if (event.key.key == SDLK_RETURN) {
        m_playPressed = true;
      }
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (event.button.button == SDL_BUTTON_LEFT &&
          m_play.isPressed(event.button.x, event.button.y)) {
        m_playPressed = true;
      }
      break;
    default:
      break;
    }
  }
}

void MainMenu::update(float t_deltaTime) {
  if (m_playPressed) {
    // TODO: Proceed to GamePlay window
    m_playPressed = false;
  }
}

void MainMenu::draw() {
  SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(m_renderer.get());

  m_renderManager->render(m_title);
  m_renderManager->render(m_play);

  SDL_RenderPresent(m_renderer.get());
}
