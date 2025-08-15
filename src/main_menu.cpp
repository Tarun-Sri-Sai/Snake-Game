#include "main_menu.hpp"
#include "game_play.hpp"

MainMenu::MainMenu(const std::shared_ptr<GameContext> &t_context) : m_context(t_context),
                                                                    m_font(nullptr, &TTF_CloseFont),
                                                                    m_gameTitleSurface(nullptr, &SDL_DestroySurface),
                                                                    m_playButtonSurface(nullptr, &SDL_DestroySurface),
                                                                    m_gameTitleTexture(nullptr, &SDL_DestroyTexture),
                                                                    m_playButtonTexture(nullptr, &SDL_DestroyTexture),
                                                                    m_gameTitleRect{0, 0, 0, 0},
                                                                    m_playButtonRect{0, 0, 0, 0},
                                                                    m_playButtonSelected(false),
                                                                    m_elapsedTime(std::chrono::duration<float>::zero())
{
    m_font.reset(m_context->assets->getFont(TITLE_FONT));

    constexpr SDL_Color white = {255, 255, 255, 255};

    m_gameTitleSurface.reset(TTF_RenderText_Blended(m_font.get(), "Snake Game", 60, white));
    m_gameTitleTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_gameTitleSurface.get()));

    TTF_Font *menuFont = m_context->assets->getFont(MENU_FONT);
    m_playButtonSurface.reset(TTF_RenderText_Blended(menuFont, "Press [Enter] to play", 0, white));
    m_playButtonTexture.reset(SDL_CreateTextureFromSurface(m_context->renderer.get(), m_playButtonSurface.get()));

    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_context->window.get(), &windowWidth, &windowHeight);

    float titleWidth, titleHeight;
    SDL_GetTextureSize(m_gameTitleTexture.get(), &titleWidth, &titleHeight);
    m_gameTitleRect = {
        (static_cast<float>(windowWidth) - titleWidth) / 2.0f,
        (static_cast<float>(windowHeight) / 2.0f) - 150.0f,
        titleWidth,
        titleHeight
    };

    float buttonWidth, buttonHeight;
    SDL_GetTextureSize(m_playButtonTexture.get(), &buttonWidth, &buttonHeight);
    m_playButtonRect = {
        (static_cast<float>(windowWidth) - buttonWidth) / 2.0f,
        (static_cast<float>(windowHeight) - buttonHeight) / 2.0f,
        buttonWidth,
        buttonHeight
    };
}

void MainMenu::listen()
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
                    m_playButtonSelected = true;
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

void MainMenu::update(const std::chrono::duration<float> &t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime < Engine::TICK_TIME)
    {
        return;
    }

    if (m_playButtonSelected)
    {
        m_context->states->add(std::make_unique<GamePlay>(m_context));
        m_playButtonSelected = false;
    }

    m_elapsedTime -= Engine::TICK_TIME;
}

void MainMenu::draw()
{
    SDL_SetRenderDrawColor(m_context->renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_context->renderer.get());

    SDL_RenderTexture(m_context->renderer.get(), m_gameTitleTexture.get(), nullptr, &m_gameTitleRect);
    SDL_RenderTexture(m_context->renderer.get(), m_playButtonTexture.get(), nullptr, &m_playButtonRect);

    SDL_RenderPresent(m_context->renderer.get());
}
