#ifndef STATE_HPP
#define STATE_HPP

#include <chrono>

namespace Engine
{
    const std::chrono::duration<float> TICK_TIME{0.12f};

    class State
    {
    public:
        State() = default;

        virtual ~State() = default;

        virtual void listen() = 0;

        virtual void update(const std::chrono::duration<float> &t_deltaTime) = 0;

        virtual void draw() = 0;
    };
}

#endif  // !STATE_HPP
