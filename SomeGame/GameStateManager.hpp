#pragma once

#include <memory>

class GameState;

class GameStateManager
{
public:
	void nextState(std::unique_ptr<GameState> next);
	[[nodiscard]] GameState* getState();
private:
	std::unique_ptr<GameState> current_gs;
};