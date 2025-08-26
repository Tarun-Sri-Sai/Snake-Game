#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

class TextRenderer {
public:
  TextRenderer(const std::shared_ptr<SDL_Renderer> &t_renderer);

  void renderText(const std::shared_ptr<TTF_Font> &font,
                  const std::string &text, SDL_Color color,
                  const SDL_FRect &dst);

private:
  std::shared_ptr<SDL_Renderer> m_renderer;
};
