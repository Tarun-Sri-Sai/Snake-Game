#include "asset_manager.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <fmt/format.h>
#include <memory>

AssetManager::AssetManager() : m_fonts() {
  if (!TTF_Init()) {
    throw std::runtime_error(fmt::format("Failed to initialize TTF: {}: ") +
                             SDL_GetError());
  }
}

AssetManager::~AssetManager() {
  m_fonts.clear();
  TTF_Quit();
}

std::shared_ptr<TTF_Font> AssetManager::getFont(const fs::path &file,
                                                int size) {
  const std::string key = getKey(file, size);

  if (m_fonts.find(key) != m_fonts.end()) {
    return m_fonts.at(key);
  }

  loadFont(file, size);
  return m_fonts.at(key);
}

void AssetManager::loadFont(const fs::path &file, int size) {
  TTF_Font *raw = TTF_OpenFont(file.string().c_str(), size);
  if (!raw) {
    throw std::runtime_error(fmt::format("Failed to open font [{}]: {}",
                                         file.string(), SDL_GetError()));
  }

  m_fonts[getKey(file, size)] = std::shared_ptr<TTF_Font>(raw, [](TTF_Font *f) {
    if (f)
      TTF_CloseFont(f);
  });
}

std::string AssetManager::getKey(const fs::path &file, int size) const {
  return fmt::format("{}_{}", file.string(), size);
}
