#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

template<>
struct std::default_delete<SDL_Texture>
{
    void operator()(SDL_Texture *ptr) const
    {
        SDL_DestroyTexture(ptr);
    }
};

template<>
struct std::default_delete<TTF_Font>
{
    void operator()(TTF_Font *ptr) const
    {
        TTF_CloseFont(ptr);
    }
};

namespace Engine
{
    class AssetManager
    {
    public:
        AssetManager();

        ~AssetManager();

        void addTexture(int t_id, const std::string &t_filePath, SDL_Renderer *renderer);

        void addFont(int t_id, const std::string &t_filePath, int fontSize);

        [[nodiscard]] SDL_Texture *getTexture(int t_id) const;

        [[nodiscard]] TTF_Font *getFont(int t_id) const;

    private:
        std::map<int, std::unique_ptr<SDL_Texture> > m_textures;
        std::map<int, std::unique_ptr<TTF_Font> > m_fonts;
    };
}

#endif  // !ASSET_MANAGER_HPP
