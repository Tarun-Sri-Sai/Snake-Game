#include "Snake.hpp"

Snake::Snake(const sf::Texture& t_texture) :
    m_body(std::list<sf::Sprite>(3, sf::Sprite(t_texture)))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake()
{
}

void Snake::setup()
{
    float x = 16.0f;
    for (auto& piece : m_body)
    {
        piece.setPosition({ x, 16.0f });
        x += 16.0f;
    }
}

void Snake::move(const sf::Vector2f& t_direction)
{
    m_tail->setPosition(m_head->getPosition() + t_direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::isOn(const sf::Sprite& t_other) const
{
    return false;
}

void Snake::grow(const sf::Vector2f& t_direction)
{
}

void Snake::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
    for (auto& piece : m_body)
    {
        t_target.draw(piece);
    }
}
