#include "text.hpp"

Text::Text(const std::shared_ptr<TTF_Font> &t_font, const std::string &t_text,
           SDL_Color t_color, float t_x, float t_y)
    : m_font(t_font), m_text(t_text), m_color(t_color), m_x(t_x), m_y(t_y) {}

std::shared_ptr<TTF_Font> Text::getFont() const { return m_font; }

std::string Text::getText() const { return m_text; }

SDL_Color Text::getColor() const { return m_color; }

float Text::getX() const { return m_x; }

float Text::getY() const { return m_y; }
