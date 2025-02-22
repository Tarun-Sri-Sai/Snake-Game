#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System.hpp>

namespace Engine
{
	class State
	{
	public:
		State() {};
		virtual ~State() {};

		virtual void setup() = 0;
		virtual void listen() = 0;
		virtual void update(sf::Time t_deltaTime) = 0;
		virtual void present() = 0;

		virtual void pause() {};
		virtual void resume() {};
	};
}

#endif  // !STATE_HPP
