#include "game_over.hpp"
#include "game_play.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

GameOver::GameOver(const std::shared_ptr<GameContext> &t_context, int t_score) : m_context(t_context),
    m_font(nullptr, &TTF_CloseFont),
    m_titleSurface(nullptr, &SDL_DestroySurface),
    m_scoreSurface(nullptr, &SDL_DestroySurface),
    m_retryButtonSurface(nullptr, &SDL_DestroySurface),
    m_titleTexture(nullptr, &SDL_DestroyTexture),
    m_scoreTexture(nullptr, &SDL_DestroyTexture),
    m_retryButtonTexture(nullptr, &SDL_DestroyTexture),
    m_titleRect{0, 0, 0, 0},
    m_scoreRect{0, 0, 0, 0},
    m_retryButtonRect{0, 0, 0, 0},
    m_retryButtonSelected(false),
    m_elapsedTime(std::chrono::duration<float>::zero())
{
    m_font.reset(m_context->assets->getFont(TITLE_FONT));

    constexpr SDL_Color white = {255, 255, 255, 255};

    m_titleSurface.reset(TTF_RenderText_Blended(m_font.get(), "Game over!", 60, white));
    m_titleTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_titleSurface.get()));

    TTF_Font *menuFont = m_context->assets->getFont(MENU_FONT);
    const std::string scoreString = fmt::format("Score: {}", t_score);
    m_scoreSurface.reset(TTF_RenderText_Blended(menuFont, scoreString.c_str(), 0, white));
    m_scoreTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_scoreSurface.get()));

    m_retryButtonSurface.reset(TTF_RenderText_Blended(menuFont, "Press [Enter] to retry", 0, white));
    m_retryButtonTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_retryButtonSurface.get()));

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
    SDL_GetTextureSize(m_retryButtonTexture.get(), &buttonWidth, &buttonHeight);
    m_retryButtonRect = {
        (static_cast<float>(windowWidth) - buttonWidth) / 2.0f,
        (static_cast<float>(windowHeight) / 2.0f) + 60.0f,
        buttonWidth,
        buttonHeight
    };
}

void GameOver::listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
                case SDLK_RETURN:
                case SDLK_RETURN2:
                    m_retryButtonSelected = true;
                    break;
                case SDLK_ESCAPE:
                    m_context->running = false;
                    break;
                default:
                    break;
            }
        }
    }
}

void GameOver::update(const std::chrono::duration<float> &t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime < Engine::TICK_TIME)
    {
        return;
    }

    if (m_retryButtonSelected)
    {
        m_context->states->add(std::make_unique<GamePlay>(m_context));
        m_retryButtonSelected = false;
    }

    m_elapsedTime -= Engine::TICK_TIME;
}

void GameOver::draw()
{
    SDL_SetRenderDrawColor(m_context->renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_context->renderer.get());

    SDL_RenderTexture(m_context->renderer.get(), m_titleTexture.get(), nullptr, &m_titleRect);
    SDL_RenderTexture(m_context->renderer.get(), m_scoreTexture.get(), nullptr, &m_scoreRect);
    SDL_RenderTexture(m_context->renderer.get(), m_retryButtonTexture.get(), nullptr, &m_retryButtonRect);

    SDL_RenderPresent(m_context->renderer.get());
}
