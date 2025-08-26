#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <memory>

class GameContext {
public:
  GameContext();
  ~GameContext();

  bool getRunning() const;
  void setRunning(bool t_running);
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;

private:
  bool m_running;
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};

#endif // !GAME_CONTEXT_HPP
