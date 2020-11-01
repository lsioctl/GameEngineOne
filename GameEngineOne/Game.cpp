#include "Game.h"

void Game::addGameObject(unique_ptr<GameObject> gameObjectPtr) {
	mGameObjects.push_back(std::move(gameObjectPtr));
}

void Game::update() {
	for (const unique_ptr<GameObject>& gameObjectPtr : mGameObjects) {
		// TO IMPLEMENT
		//gameObjectPtr->update();
	}
}
