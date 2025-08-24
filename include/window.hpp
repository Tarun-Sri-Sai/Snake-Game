#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
public:
  Window() {};
  virtual ~Window() = default;
  virtual void listen() = 0;
  virtual void update(float t_deltaTime) = 0;
  virtual void draw() = 0;
};

#endif // !WINDOW_HPP
