#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "window.hpp"
#include <SDL3/SDL_render.h>
#include <memory>

class MainMenu final : public Window {
public:
  MainMenu(std::shared_ptr<SDL_Renderer> t_renderer);

  ~MainMenu() override;

  void listen() override;

  void update(float t_deltaTime) override;

  void draw() override;

private:
  std::shared_ptr<SDL_Renderer> m_renderer;
};

#endif // !MAIN_MENU_HPP
