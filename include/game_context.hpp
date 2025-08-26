#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

class GameContext {
public:
  GameContext();
  
  ~GameContext() = default;
  
  bool getRunning() const;
  
  void setRunning(bool t_running);

private:
  bool m_running;
};

#endif // !GAME_CONTEXT_HPP
