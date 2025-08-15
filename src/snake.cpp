#include "Snake.hpp"

Snake::Snake(SDL_Texture *t_texture) : m_body(std::list<SnakePiece>(3, SnakePiece(0.0f, 0.0f, 16.0f, 16.0f))),
                                       m_texture(t_texture)
{
    m_head = --m_body.end();
    m_tail = m_body.begin();

    float x = 16.0f;
    for (auto &piece: m_body)
    {
        piece.rect.x = x;
        piece.rect.y = 16.0f;
        x += 16.0f;
    }
}

void Snake::move(const SDL_FPoint &t_direction)
{
    m_tail->rect.x = m_head->rect.x + t_direction.x;
    m_tail->rect.y = m_head->rect.y + t_direction.y;
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::isHeadOn(const SDL_FRect &t_other) const
{
    return SDL_HasRectIntersectionFloat(&t_other, &m_head->getRect());
}

bool Snake::isOn(const SDL_FRect &t_other) const
{
    for (auto &piece: m_body)
    {
        if (SDL_HasRectIntersectionFloat(&t_other, &piece.getRect()))
        {
            return true;
        }
    }
    return false;
}

bool Snake::isDead() const
{
    for (auto piece = m_body.begin(); piece != std::prev(m_body.end(), 2); ++piece)
    {
        if (piece != m_head && SDL_HasRectIntersectionFloat(&m_head->getRect(), &piece->getRect()))
        {
            return true;
        }
    }
    return false;
}

void Snake::grow(const SDL_FPoint &t_direction)
{
    SnakePiece newPiece(
        m_head->rect.x + t_direction.x,
        m_head->rect.y + t_direction.y,
        16.0f,
        16.0f
    );

    m_head = m_body.insert(++m_head, newPiece);
}

void Snake::render(SDL_Renderer *renderer) const
{
    for (const auto &piece: m_body)
    {
        SDL_RenderTexture(renderer, m_texture, nullptr, &piece.rect);
    }
}
