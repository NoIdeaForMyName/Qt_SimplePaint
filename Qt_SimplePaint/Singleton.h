#pragma once

#include <vector>
//#include <type_traits>

#include "SingletonItemContainer.h"
#include "Item.h"

// CREATING NEW SINGLETON, COMES TO MAKING A CLASS TO DERIVE FROM SINGLETON
// AND PASSING ITS ADDRESS IN A CONSTRUCTOR: Singleton(this)

template <typename T> // must be of type extending Item type
class Singleton: public SingletonItemsContainer
{
	//static_assert(std::is_base_of_v<Item, T>, "T must be of type deriving from Item");

public:
	Singleton(T* addr);
	static void setItemsOnScene(std::vector<Item*>& items);

private:
	static T* address;
};

template <typename T>
T* Singleton<T>::address = nullptr;

template <typename T>
Singleton<T>::Singleton(T* addr)
	: SingletonItemsContainer()
{
	if (address != nullptr)
	{
		bool deleted = false;
		//for (int i = 0; i < itemsOnScene->size() && !deleted; i++)
		for (auto i = itemsOnScene->begin();!deleted && i != itemsOnScene->end();) // ++i
			if (*i == address)
			{
				delete* i;
				itemsOnScene->erase(i);
				deleted = true;
			}
			else ++i;
	}
	address = addr;
}

template <typename T>
void Singleton<T>::setItemsOnScene(std::vector<Item*>& items)
{
	itemsOnScene = &items;
}
