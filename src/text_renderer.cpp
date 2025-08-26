#include "text_renderer.hpp"
#include <SDL3/SDL_render.h>
#include <string>

TextRenderer::TextRenderer(const std::shared_ptr<SDL_Renderer> &t_renderer)
    : m_renderer(t_renderer) {}

void TextRenderer::renderText(const std::shared_ptr<TTF_Font> &font,
                              const std::string &text, SDL_Color color,
                              const SDL_FRect &dst) {
  SDL_Surface *surface =
      TTF_RenderText_Solid(font.get(), text.c_str(), 0, color);
  if (!surface) {
    return;
  }

  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(m_renderer.get(), surface);
  SDL_DestroySurface(surface);
  if (!texture) {
    return;
  }

  SDL_RenderTexture(m_renderer.get(), texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}
