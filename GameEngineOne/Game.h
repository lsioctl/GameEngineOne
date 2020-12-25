#pragma once
#include <vector>

#include "GameObject.h"

class Game
{
private:
	std::vector<unique_ptr<GameObject>> mGameObjects;
public:
	void addGameObject(unique_ptr<GameObject> gameObjectPtr);
	void update();
};

