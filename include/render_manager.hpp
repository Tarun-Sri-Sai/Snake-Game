#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "text.hpp"
#include <SDL3/SDL_render.h>
#include <memory>
#include <unordered_map>

class RenderManager final {
public:
  RenderManager(const std::shared_ptr<SDL_Renderer> &t_renderer);
  ~RenderManager();

  void render(const Text &text);

private:
  struct CacheKey {
    std::string text;
    TTF_Font *font;
    SDL_Color color;

    bool operator==(const CacheKey &other) const {
      return text == other.text && font == other.font &&
             color.r == other.color.r && color.g == other.color.g &&
             color.b == other.color.b && color.a == other.color.a;
    }
  };

  struct CacheKeyHash {
    std::size_t operator()(const CacheKey &key) const {
      std::size_t h1 = std::hash<std::string>{}(key.text);
      std::size_t h2 = std::hash<void *>{}(key.font);
      std::size_t h3 = key.color.r ^ (key.color.g << 8) ^ (key.color.b << 16) ^
                       (key.color.a << 24);
      return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
  };

  std::shared_ptr<SDL_Renderer> m_renderer;
  std::unordered_map<CacheKey, SDL_Texture *, CacheKeyHash> m_textureCache;

  SDL_Texture *getOrCreateTexture(const Text &t_text);

  void clearCache();
};

#endif // !RENDER_MANAGER_HPP
