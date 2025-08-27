#include "text.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

class TextRenderer final {
public:
  TextRenderer(const std::shared_ptr<SDL_Renderer> &t_renderer);

  void render(const Text &text);

private:
  std::shared_ptr<SDL_Renderer> m_renderer;
};
