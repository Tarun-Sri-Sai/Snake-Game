#include "game_play.hpp"
#include "game_over.hpp"
#include "game_pause.hpp"
#include <algorithm>

GamePlay::GamePlay(const std::shared_ptr<GameContext> &t_context) : m_context(t_context),
                                                                    m_grassTexture(nullptr, &SDL_DestroyTexture),
                                                                    m_foodTexture(nullptr, &SDL_DestroyTexture),
                                                                    m_wallTextures{
                                                                        std::unique_ptr<SDL_Texture, decltype(&
                                                                            SDL_DestroyTexture)>(
                                                                            nullptr, &SDL_DestroyTexture),
                                                                        std::unique_ptr<SDL_Texture, decltype(&
                                                                            SDL_DestroyTexture)>(
                                                                            nullptr, &SDL_DestroyTexture),
                                                                        std::unique_ptr<SDL_Texture, decltype(&
                                                                            SDL_DestroyTexture)>(
                                                                            nullptr, &SDL_DestroyTexture),
                                                                        std::unique_ptr<SDL_Texture, decltype(&
                                                                            SDL_DestroyTexture)>(
                                                                            nullptr, &SDL_DestroyTexture)
                                                                    },
                                                                    m_grassRect{0, 0, 0, 0},
                                                                    m_foodRect{0, 0, 0, 0},
                                                                    m_snake(m_context->assets->getTexture(SNAKE)),
                                                                    m_snakeDirection(RIGHT),
                                                                    m_elapsedTime(std::chrono::duration<float>::zero()),
                                                                    m_generator{std::random_device{}()},
                                                                    m_score(0)
{
    m_grassTexture.reset(m_context->assets->getTexture(GRASS));
    m_foodTexture.reset(m_context->assets->getTexture(FOOD));

    for (int i = 0; i < 4; ++i)
    {
        m_wallTextures[i].reset(m_context->assets->getTexture(WALL));
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_context->window.get(), &windowWidth, &windowHeight);

    m_grassRect = {0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight)};

    m_wallRects[0] = {0.0f, 0.0f, static_cast<float>(windowWidth), 16.0f};
    m_wallRects[1] = {0.0f, static_cast<float>(windowHeight) - 16.0f, static_cast<float>(windowWidth), 16.0f};
    m_wallRects[2] = {0.0f, 16.0f, 16.0f, static_cast<float>(windowHeight) - 32.0f};
    m_wallRects[3] = {static_cast<float>(windowWidth) - 16.0f, 16.0f, 16.0f, static_cast<float>(windowHeight) - 32.0f};

    setFoodPosition();
}

SDL_FPoint GamePlay::getSnakeDirection() const
{
    switch (m_snakeDirection)
    {
        case UP:
            return {0.0f, -16.0f};
        case DOWN:
            return {0.0f, 16.0f};
        case LEFT:
            return {-16.0f, 0.0f};
        case RIGHT:
            return {16.0f, 0.0f};
        default:
            return {0.0f, 0.0f};
    }
}

void GamePlay::setFoodPosition()
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_context->window.get(), &windowWidth, &windowHeight);

    SDL_FPoint result = {
        static_cast<float>(getRandom((windowWidth - 32) / 16)) * 16,
        static_cast<float>(getRandom((windowHeight - 32) / 16)) * 16
    };

    m_foodRect.x = result.x;
    m_foodRect.y = result.y;

    float foodWidth, foodHeight;
    SDL_GetTextureSize(m_foodTexture.get(), &foodWidth, &foodHeight);
    m_foodRect.w = foodWidth;
    m_foodRect.h = foodHeight;

    while (m_snake.isOn(m_foodRect))
    {
        result = {
            static_cast<float>(getRandom((windowWidth - 32) / 16)) * 16,
            static_cast<float>(getRandom((windowHeight - 32) / 16)) * 16
        };

        m_foodRect.x = result.x;
        m_foodRect.y = result.y;
    }
}

void GamePlay::listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_context->running = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
                case SDLK_UP:
                    if (m_snakeDirection != DOWN)
                    {
                        m_snakeDirection = UP;
                    }
                    break;
                case SDLK_DOWN:
                    if (m_snakeDirection != UP)
                    {
                        m_snakeDirection = DOWN;
                    }
                    break;
                case SDLK_LEFT:
                    if (m_snakeDirection != RIGHT)
                    {
                        m_snakeDirection = LEFT;
                    }
                    break;
                case SDLK_RIGHT:
                    if (m_snakeDirection != LEFT)
                    {
                        m_snakeDirection = RIGHT;
                    }
                    break;
                case SDLK_ESCAPE:
                    m_context->states->add(std::make_unique<GamePause>(m_context, m_score), false);
                    break;
                default:
                    break;
            }
        }
    }
}

void GamePlay::update(const std::chrono::duration<float> &t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime < Engine::TICK_TIME)
    {
        return;
    }

    if (isSnakeOnWall() || m_snake.isDead() || m_score > 1392)
    {
        m_context->states->add(std::make_unique<GameOver>(m_context, m_score));
        return;
    }

    if (m_snake.isHeadOn(m_foodRect))
    {
        m_score++;
        m_snake.grow(getSnakeDirection());
        setFoodPosition();
    } else
    {
        m_snake.move(getSnakeDirection());
    }

    m_elapsedTime -= Engine::TICK_TIME;
}

bool GamePlay::isSnakeOnWall() const
{
    return std::any_of(m_wallRects.begin(), m_wallRects.end(),
                       [this](const SDL_FRect &wall)
                       {
                           return m_snake.isHeadOn(wall);
                       });
}

void GamePlay::draw()
{
    SDL_SetRenderDrawColor(m_context->renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_context->renderer.get());

    SDL_RenderTexture(m_context->renderer.get(), m_grassTexture.get(), nullptr, &m_grassRect);

    for (size_t i = 0; i < m_wallTextures.size(); ++i)
    {
        SDL_RenderTexture(m_context->renderer.get(), m_wallTextures[i].get(), nullptr, &m_wallRects[i]);
    }

    SDL_RenderTexture(m_context->renderer.get(), m_foodTexture.get(), nullptr, &m_foodRect);
    m_snake.render(m_context->renderer.get());

    SDL_RenderPresent(m_context->renderer.get());
}

int GamePlay::getRandom(const int t_max)
{
    std::uniform_int_distribution<int> distribution(1, t_max);

    return distribution(m_generator);
}
