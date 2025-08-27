#include "button.hpp"

Button::Button(const std::shared_ptr<TTF_Font> &t_font,
               const std::string &t_text, SDL_Color t_color, float t_x,
               float t_y)
    : Text(t_font, t_text, t_color, t_x, t_y), m_w(0), m_h(0) {
  TTF_GetStringSize(getFont().get(), getText().c_str(), 0, &m_w, &m_h);
}

bool Button::isPressed(int t_mouseX, int t_mouseY) const {
  return t_mouseX >= m_x && t_mouseX <= m_x + m_w && t_mouseY >= m_y &&
         t_mouseY <= m_y + m_h;
}
