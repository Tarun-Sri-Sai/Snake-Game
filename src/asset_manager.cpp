#include "asset_manager.hpp"
#include <SDL3_image/SDL_image.h>

Engine::AssetManager::AssetManager()
{
    if (!TTF_Init())
    {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        SDL_Quit();
    }
}

Engine::AssetManager::~AssetManager()
{
    TTF_Quit();
}

void Engine::AssetManager::addTexture(const int t_id, const std::string &t_filePath, SDL_Renderer *renderer)
{
    if (SDL_Surface *surface = IMG_Load(t_filePath.c_str()))
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        if (!texture)
        {
            return;
        }
        m_textures[t_id] = std::unique_ptr<SDL_Texture>(texture);
    }
}

void Engine::AssetManager::addFont(const int t_id, const std::string &t_filePath, const int fontSize)
{
    if (TTF_Font *font = TTF_OpenFont(t_filePath.c_str(), static_cast<float>(fontSize)))
    {
        m_fonts[t_id] =  std::unique_ptr<TTF_Font>(font);
    }
}

SDL_Texture *Engine::AssetManager::getTexture(const int t_id) const
{
    const auto it = m_textures.find(t_id);
    return (it != m_textures.end()) ? it->second.get() : nullptr;
}

TTF_Font *Engine::AssetManager::getFont(const int t_id) const
{
    const auto it = m_fonts.find(t_id);
    return (it != m_fonts.end()) ? it->second.get() : nullptr;
}
