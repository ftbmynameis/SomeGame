#include "GameStateManager.hpp"

#include "GameState.hpp"

void GameStateManager::nextState(std::unique_ptr<GameState> next)
{
	current_gs = std::move(next);
}

GameState* GameStateManager::getState()
{
	return current_gs.get();
}