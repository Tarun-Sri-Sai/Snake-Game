#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <SDL3/SDL.h>

struct SnakePiece
{
    SDL_FRect rect;

    SnakePiece(const float x, const float y, const float w, const float h)
        : rect{x, y, w, h}
    {
    }

    [[nodiscard]] const SDL_FRect &getRect() const { return rect; }
    SDL_FRect &getRect() { return rect; }
};

class Snake
{
public:
    explicit Snake(SDL_Texture *t_texture);

    ~Snake() = default;

    void move(const SDL_FPoint &t_direction);

    [[nodiscard]] bool isOn(const SDL_FRect &t_other) const;

    [[nodiscard]] bool isHeadOn(const SDL_FRect &t_other) const;

    void grow(const SDL_FPoint &t_direction);

    void render(SDL_Renderer *renderer) const;

    [[nodiscard]] bool isDead() const;

private:
    std::list<SnakePiece> m_body;
    std::list<SnakePiece>::iterator m_head;
    std::list<SnakePiece>::iterator m_tail;
    SDL_Texture *m_texture;
};

#endif  // !SNAKE_HPP
