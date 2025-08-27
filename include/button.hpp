#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "text.hpp"

class Button : public Text {
public:
  Button(const std::shared_ptr<TTF_Font> &t_font, const std::string &t_text,
         SDL_Color t_color, float t_x, float t_y);

  ~Button() = default;

  bool isPressed(int t_mouseX, int t_mouseY) const;

private:
  int m_w;
  int m_h;
};

#endif // !BUTTON_HPP
