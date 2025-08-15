#include "game.hpp"
#include <thread>
#include <chrono>
#include "main_menu.hpp"
using namespace std::chrono_literals;

GameContext::GameContext() : window(nullptr, &SDL_DestroyWindow), renderer(nullptr, &SDL_DestroyRenderer),
                             running(false)
{
    assets = std::make_unique<Engine::AssetManager>();
    states = std::make_unique<Engine::StateManager>();

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error("SDL_Init failed");
    }

    window.reset(SDL_CreateWindow("Snake Game", 960, 540, 0));
    if (!window)
    {
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
    if (!renderer)
    {
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer failed");
    }
}

GameContext::~GameContext()
{
    SDL_Quit();
}

Game::Game() : m_context(std::make_shared<GameContext>())
{
    m_context->assets->addFont(TITLE_FONT, getAssetFile("roboto_bold.ttf"), 48);
    m_context->assets->addFont(MENU_FONT, getAssetFile("roboto_regular.ttf"), 36);

    m_context->assets->addTexture(GRASS, getAssetFile("grass.png"), m_context->renderer.get());
    m_context->assets->addTexture(WALL, getAssetFile("wall.png"), m_context->renderer.get());
    m_context->assets->addTexture(FOOD, getAssetFile("food.png"), m_context->renderer.get());
    m_context->assets->addTexture(SNAKE, getAssetFile("snake.png"), m_context->renderer.get());

    m_context->states->add(std::make_unique<MainMenu>(m_context));
}

std::string Game::getAssetFile(const std::string &t_fileName)
{
    return (ASSETS_DIR / fs::path(t_fileName)).string();
}

void Game::run() const
{
    auto lastTime = std::chrono::high_resolution_clock::now();
    auto timeSinceLastFrame = std::chrono::duration<float>::zero();

    while (m_context->running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        const auto deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame < FRAME_TIME)
        {
            std::this_thread::sleep_for(5ms);
            continue;
        }

        while (timeSinceLastFrame >= FRAME_TIME)
        {
            timeSinceLastFrame -= FRAME_TIME;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    m_context->running = false;
                }
            }

            m_context->states->update();
            m_context->states->get()->listen();
            m_context->states->get()->update(FRAME_TIME);
            m_context->states->get()->draw();
        }
    }
}
