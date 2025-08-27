#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>

class Text {
public:
  Text(const std::shared_ptr<TTF_Font> &t_font, const std::string &t_text,
       SDL_Color t_color, float t_x, float t_y);

  ~Text() = default;

  std::shared_ptr<TTF_Font> getFont() const;

  std::string getText() const;

  SDL_Color getColor() const;

  float getX() const;

  float getY() const;

protected:
  float m_x;
  float m_y;

private:
  std::shared_ptr<TTF_Font> m_font;
  std::string m_text;
  SDL_Color m_color;
};

#endif // !TEXT_HPP
