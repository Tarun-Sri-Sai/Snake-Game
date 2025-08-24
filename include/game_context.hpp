#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

struct GameContext {
public:
  static GameContext &getInstance() {
    static GameContext instance;
    return instance;
  }

  bool m_running;

private:
  GameContext() : m_running(true) {}
  ~GameContext() = default;
  GameContext(const GameContext &) = delete;
  GameContext &operator=(const GameContext &) = delete;
  GameContext(GameContext &&) = delete;
  GameContext &operator=(GameContext &&) = delete;
};

#endif // !GAME_CONTEXT_HPP
