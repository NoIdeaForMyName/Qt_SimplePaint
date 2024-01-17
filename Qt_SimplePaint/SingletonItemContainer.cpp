#include "SingletonItemContainer.h"

SingletonItemsContainer::SingletonItemsContainer()
{}

std::vector<Item*>* SingletonItemsContainer::itemsOnScene = nullptr;
