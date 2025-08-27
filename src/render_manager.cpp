#include "render_manager.hpp"
#include <SDL3/SDL_rect.h>

RenderManager::RenderManager(const std::shared_ptr<SDL_Renderer> &t_renderer)
    : m_renderer(t_renderer) {}

void RenderManager::render(const Text &t_text) {
  SDL_Surface *surface = TTF_RenderText_Solid(
      t_text.getFont().get(), t_text.getText().c_str(), 0, t_text.getColor());
  if (!surface) {
    return;
  }

  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(m_renderer.get(), surface);
  if (!texture) {
    return;
  }

  const SDL_FRect dst = {t_text.getX(), t_text.getY(),
                         static_cast<float>(surface->w),
                         static_cast<float>(surface->h)};

  SDL_DestroySurface(surface);

  SDL_RenderTexture(m_renderer.get(), texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}
