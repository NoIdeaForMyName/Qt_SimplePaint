#pragma once

#include <vector>
#include "Item.h"

// IN SCENE CLASS STATIC FIELD: itemsOnScene MUST BE INITIALIZED

class SingletonItemsContainer
{
public:
	SingletonItemsContainer();
	static std::vector<Item*>* itemsOnScene;
};
