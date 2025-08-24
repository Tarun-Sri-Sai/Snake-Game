#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include "window.hpp"
#include <memory>
#include <stack>

class WindowManager {
public:
  WindowManager();
  void listen();
  void update(const float &t_deltaTime);
  void draw();
  void open(std::unique_ptr<Window> t_window, bool inplace = true);

private:
  std::stack<std::unique_ptr<Window>> m_stack;
};

#endif // !WINDOW_MANAGER_HPP
