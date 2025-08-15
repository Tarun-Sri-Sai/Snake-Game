#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <SDL3_ttf/SDL_ttf.h>

class MainMenu final : public Engine::State
{
public:
    explicit MainMenu(const std::shared_ptr<GameContext> &t_context);

    ~MainMenu() override = default;

    void listen() override;

    void update(const std::chrono::duration<float> &t_deltaTime) override;

    void draw() override;

private:
    std::shared_ptr<GameContext> m_context;

    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_gameTitleSurface;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_playButtonSurface;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_gameTitleTexture;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_playButtonTexture;

    SDL_FRect m_gameTitleRect;
    SDL_FRect m_playButtonRect;

    bool m_playButtonSelected;
    std::chrono::duration<float> m_elapsedTime;
};

#endif  // !MAIN_MENU_HPP
