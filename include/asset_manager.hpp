#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

class AssetManager final {
public:
  AssetManager();

  ~AssetManager();

  std::shared_ptr<TTF_Font> getFont(const fs::path &file, int size);

private:
  std::unordered_map<std::string, std::shared_ptr<TTF_Font>> m_fonts;

  void loadFont(const fs::path &file, int size);

  std::string getKey(const fs::path &file, int size) const;
};

#endif // !ASSET_MANAGER_HPP
