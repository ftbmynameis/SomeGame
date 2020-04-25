#pragma once

#include "GameStateManager.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

class GameState : public sf::Drawable
{
public:
	explicit GameState(GameStateManager& gsm_)
		: gsm(gsm_)
	{
	}

	// todo: why is the override required here (by clang tidy)
	~GameState() override = default;

	virtual void update(double global_t, double dt) = 0;
	virtual void processEvent(const sf::Event& event) = 0;
	
	GameState(const GameState&) = delete;
	GameState(GameState&&) = delete;
	GameState& operator= (const GameState&) = delete;
	GameState& operator= (GameState&&) = delete;
protected:
	
private:
	GameStateManager& gsm;
};