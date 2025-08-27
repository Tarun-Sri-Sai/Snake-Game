#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <filesystem>

namespace fs = std::filesystem;

const std::string WINDOW_TITLE("Snake Game");
const std::string PLAY_BUTTON("Play");
constexpr auto WINDOW_WIDTH = 960;
constexpr auto WINDOW_HEIGHT = 540;
const auto ASSETS_DIRECTORY = fs::path("assets");
const auto FONT_ROBOTO_BOLD = ASSETS_DIRECTORY / fs::path("roboto_bold.ttf");
const auto FONT_ROBOTO_REGULAR =
    ASSETS_DIRECTORY / fs::path("roboto_regular.ttf");

#endif // !CONSTANTS_HPP
