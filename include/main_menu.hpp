#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "window.hpp"

class MainMenu : public Window {
public:
  MainMenu();
  ~MainMenu() override;
  void listen() override;
  void update(float t_deltaTime) override;
  void draw() override;
};

#endif // !MAIN_MENU_HPP
