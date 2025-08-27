#include "text_renderer.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

TextRenderer::TextRenderer(const std::shared_ptr<SDL_Renderer> &t_renderer)
    : m_renderer(t_renderer) {}

void TextRenderer::render(const Text &t_text) {
  SDL_Surface *surface = TTF_RenderText_Solid(
      t_text.getFont().get(), t_text.getText().c_str(), 0, t_text.getColor());
  if (!surface) {
    return;
  }

  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(m_renderer.get(), surface);
  SDL_DestroySurface(surface);
  if (!texture) {
    return;
  }

  int w, h;
  TTF_GetStringSize(t_text.getFont().get(), t_text.getText().c_str(), 0, &w,
                    &h);

  const SDL_FRect dst = {t_text.getX(), t_text.getY(), static_cast<float>(w),
                         static_cast<float>(h)};
  SDL_RenderTexture(m_renderer.get(), texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}
