#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <filesystem>

namespace  fs = std::filesystem;

constexpr auto WINDOW_TITLE = "Snake Game";
constexpr auto WINDOW_WIDTH = 960;
constexpr auto WINDOW_HEIGHT = 540;
const auto ASSETS_DIRECTORY = fs::path("assets");
const auto FONT_ROBOTO_BOLD = ASSETS_DIRECTORY / fs::path("roboto_bold.ttf");

#endif // !CONSTANTS_HPP
