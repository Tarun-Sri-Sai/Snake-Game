#ifndef GAME_HPP
#define GAME_HPP

#include "asset_manager.hpp"
#include "state_manager.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <filesystem>

namespace fs = std::filesystem;

enum GameAssets
{
    TITLE_FONT = 0,
    MENU_FONT,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};

struct GameContext
{
    std::unique_ptr<Engine::AssetManager> assets;
    std::unique_ptr<Engine::StateManager> states;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    bool running;

    GameContext();

    ~GameContext();
};

const auto ASSETS_DIR = fs::path("assets");

class Game
{
public:
    Game();

    ~Game() = default;

    void run() const;

private:
    std::shared_ptr<GameContext> m_context;
    const std::chrono::duration<float> FRAME_TIME{1.0f / 60.0f};

    static std::string getAssetFile(const std::string &t_fileName);
};

#endif  // !GAME_HPP
