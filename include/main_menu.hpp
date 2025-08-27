#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "asset_manager.hpp"
#include "button.hpp"
#include "game_context.hpp"
#include "render_manager.hpp"
#include "text.hpp"
#include "window.hpp"
#include <SDL3/SDL_render.h>
#include <memory>

class MainMenu final : public Window {
public:
  MainMenu(const std::shared_ptr<SDL_Renderer> &t_renderer,
           const std::shared_ptr<RenderManager> &t_renderManager,
           const std::shared_ptr<GameContext> &t_gameContext,
           const std::shared_ptr<AssetManager> &t_assetManager);

  ~MainMenu() override;

  void listen() override;

  void update(float t_deltaTime) override;

  void draw() override;

private:
  std::shared_ptr<SDL_Renderer> m_renderer;
  std::shared_ptr<RenderManager> m_renderManager;
  std::shared_ptr<GameContext> m_gameContext;
  std::shared_ptr<AssetManager> m_assetManager;
  Text m_title;
  Button m_play;
  bool m_playPressed;
};

#endif // !MAIN_MENU_HPP
