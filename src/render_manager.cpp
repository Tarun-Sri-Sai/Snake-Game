#include "render_manager.hpp"
#include <SDL3/SDL_rect.h>

RenderManager::RenderManager(const std::shared_ptr<SDL_Renderer> &t_renderer)
    : m_renderer(t_renderer) {}

RenderManager::~RenderManager() {
  clearCache();
}

void RenderManager::clearCache() {
  for (auto& pair : m_textureCache) {
    SDL_DestroyTexture(pair.second);
  }
  m_textureCache.clear();
}

SDL_Texture* RenderManager::getOrCreateTexture(const Text& t_text) {
  CacheKey key{t_text.getText(), t_text.getFont().get(), t_text.getColor()};
  
  auto it = m_textureCache.find(key);
  if (it != m_textureCache.end()) {
    return it->second;
  }
  
  SDL_Surface *surface = TTF_RenderText_Solid(
      t_text.getFont().get(), t_text.getText().c_str(), 0, t_text.getColor());
  if (!surface) {
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer.get(), surface);
  SDL_DestroySurface(surface);

  if (texture) {
    m_textureCache[key] = texture;
  }
  
  return texture;
}

void RenderManager::render(const Text &t_text) {
  SDL_Texture* texture = getOrCreateTexture(t_text);
  if (!texture) {
    return;
  }

  float w, h;
  if (!SDL_GetTextureSize(texture, &w, &h)) {
    return;
  }

  const SDL_FRect dst = {t_text.getX(), t_text.getY(), w, h};
  SDL_RenderTexture(m_renderer.get(), texture, nullptr, &dst);
}
