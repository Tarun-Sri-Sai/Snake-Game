#include "main_menu.hpp"
#include "constants.hpp"

MainMenu::MainMenu(const std::shared_ptr<SDL_Renderer> &t_renderer,
                   const std::shared_ptr<TextRenderer> &t_textRenderer,
                   const std::shared_ptr<GameContext> &t_gameContext,
                   const std::shared_ptr<AssetManager> &t_assetManager)
    : m_renderer(t_renderer), m_textRenderer(t_textRenderer),
      m_gameContext(t_gameContext), m_assetManager(t_assetManager) {}

MainMenu::~MainMenu() {}

void MainMenu::listen() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      m_gameContext->setRunning(false);
      break;
    case SDL_EVENT_KEY_DOWN:
      break;
    default:
      break;
    }
  }
}

void MainMenu::update(float t_deltaTime) {}

void MainMenu::draw() {
  constexpr SDL_Color white = {255, 255, 255, 255};
  constexpr SDL_FRect rect = {50.f, 50.f, 200.f, 50.f};

  const auto titleFont = m_assetManager->getFont(FONT_ROBOTO_BOLD, 36);
  m_textRenderer->renderText(titleFont, "Hello World", white, rect);
  SDL_RenderPresent(m_renderer.get());
}
