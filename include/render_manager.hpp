#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "text.hpp"
#include <SDL3/SDL_render.h>
#include <memory>

class RenderManager final {
public:
  RenderManager(const std::shared_ptr<SDL_Renderer> &t_renderer);

  void render(const Text &text);

private:
  std::shared_ptr<SDL_Renderer> m_renderer;
};

#endif // !RENDER_MANAGER_HPP
