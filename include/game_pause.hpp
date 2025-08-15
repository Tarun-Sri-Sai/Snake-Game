#ifndef GAME_PAUSE_HPP
#define GAME_PAUSE_HPP

#include "state.hpp"
#include "game.hpp"
#include <SDL3_ttf/SDL_ttf.h>

class GamePause final : public Engine::State
{
public:
    GamePause(const std::shared_ptr<GameContext> &t_context, int t_score);

    ~GamePause() override = default;

    void listen() override;

    void update(const std::chrono::duration<float> &t_deltaTime) override;

    void draw() override;

private:
    std::shared_ptr<GameContext> m_context;

    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_titleSurface;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_scoreSurface;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_playButtonSurface;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_titleTexture;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_scoreTexture;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_playButtonTexture;

    SDL_FRect m_titleRect;
    SDL_FRect m_scoreRect;
    SDL_FRect m_playButtonRect;

    bool m_playButtonSelected;
    std::chrono::duration<float> m_elapsedTime;
};

#endif  // !GAME_PAUSE_HPP
