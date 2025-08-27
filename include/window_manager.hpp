#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include "window.hpp"
#include "render_manager.hpp"
#include <SDL3/SDL_render.h>
#include <memory>
#include <stack>

class WindowManager final {
public:
  WindowManager();

  ~WindowManager();

  void listen();

  void update(float t_deltaTime);

  void draw();

  template <typename WindowType, typename... Args>
  void open(bool inplace = true, Args &&...args) {
    if (!inplace && !m_stack.empty()) {
      m_stack.pop();
    }

    m_stack.push(
        std::make_unique<WindowType>(m_renderer, m_renderManager, std::forward<Args>(args)...));
  }

private:
  std::stack<std::unique_ptr<Window>> m_stack;
  std::shared_ptr<SDL_Window> m_window;
  std::shared_ptr<SDL_Renderer> m_renderer;
  std::shared_ptr<RenderManager> m_renderManager;
};

#endif // !WINDOW_MANAGER_HPP
