#include "game_pause.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

GamePause::GamePause(const std::shared_ptr<GameContext> &t_context, int t_score) : m_context(t_context),
    m_font(nullptr, &TTF_CloseFont),
    m_titleSurface(nullptr, &SDL_DestroySurface),
    m_scoreSurface(nullptr, &SDL_DestroySurface),
    m_playButtonSurface(nullptr, &SDL_DestroySurface),
    m_titleTexture(nullptr, &SDL_DestroyTexture),
    m_scoreTexture(nullptr, &SDL_DestroyTexture),
    m_playButtonTexture(nullptr, &SDL_DestroyTexture),
    m_titleRect{0, 0, 0, 0},
    m_scoreRect{0, 0, 0, 0},
    m_playButtonRect{0, 0, 0, 0},
    m_playButtonSelected(false),
    m_elapsedTime(std::chrono::duration<float>::zero())
{
    m_font.reset(m_context->assets->getFont(TITLE_FONT));

    SDL_Color white = {255, 255, 255, 255};

    m_titleSurface.reset(TTF_RenderText_Blended(m_font.get(), "Paused", 60, white));
    m_titleTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_titleSurface.get()));

    TTF_Font *menuFont = m_context->assets->getFont(MENU_FONT);
    std::string scoreString = fmt::format("Score: {}", t_score);
    m_scoreSurface.reset(TTF_RenderText_Blended(menuFont, scoreString.c_str(), 0, white));
    m_scoreTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_scoreSurface.get()));

    m_playButtonSurface.reset(TTF_RenderText_Blended(menuFont, "Press [Escape] to resume", 0, white));
    m_playButtonTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_playButtonSurface.get()));

    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_context->window.get(), &windowWidth, &windowHeight);

    float titleWidth, titleHeight;
    SDL_GetTextureSize(m_titleTexture.get(), &titleWidth, &titleHeight);
    m_titleRect = {
        (static_cast<float>(windowWidth) - titleWidth) / 2.0f,
        (static_cast<float>(windowHeight) / 2.0f) - 150.0f,
        titleWidth,
        titleHeight
    };

    float scoreWidth, scoreHeight;
    SDL_GetTextureSize(m_scoreTexture.get(), &scoreWidth, &scoreHeight);
    m_scoreRect = {
        (static_cast<float>(windowWidth) - scoreWidth) / 2.0f,
        (static_cast<float>(windowHeight) - scoreHeight) / 2.0f,
        scoreWidth,
        scoreHeight
    };

    float buttonWidth, buttonHeight;
    SDL_GetTextureSize(m_playButtonTexture.get(), &buttonWidth, &buttonHeight);
    m_playButtonRect = {
        (static_cast<float>(windowWidth) - buttonWidth) / 2.0f,
        (static_cast<float>(windowHeight) / 2.0f) + 60.0f,
        buttonWidth,
        buttonHeight
    };
}

void GamePause::listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
                case SDLK_ESCAPE:
                    m_playButtonSelected = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void GamePause::update(const std::chrono::duration<float> &t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime < Engine::TICK_TIME)
    {
        return;
    }

    if (m_playButtonSelected)
    {
        m_context->states->remove();
        m_playButtonSelected = false;
    }

    m_elapsedTime -= std::chrono::duration<float>(Engine::TICK_TIME);
}

void GamePause::draw()
{
    SDL_SetRenderDrawColor(m_context->renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_context->renderer.get());

    SDL_RenderTexture(m_context->renderer.get(), m_titleTexture.get(), nullptr, &m_titleRect);
    SDL_RenderTexture(m_context->renderer.get(), m_scoreTexture.get(), nullptr, &m_scoreRect);
    SDL_RenderTexture(m_context->renderer.get(), m_playButtonTexture.get(), nullptr, &m_playButtonRect);

    SDL_RenderPresent(m_context->renderer.get());
}
