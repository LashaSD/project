#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"
#include "EntityHandler.hpp"

Entity* EntityHandler::createEntity()
{
	Entity* e = Entity(nextEntityId);
	entities[nextEntityId] = e;
	nextEntityId++;
	return e;
}

void EntityHandler::destroyEntity(Entity* p_entity)
{
	int id = p_entity->getId();
	entities.erase(id);
	delete p_entity;
	for (auto& kv : components)
	{
		std::vector<Component*>& v = kv.second;
		v.erase(std::remove(v.begin(), v.end(), entity->getComponent<typename kv.first>()));
	}
}

template <typename T>
void EntityHandler::addComponent(Entity* p_entity, T* p_component)
{
	p_entity->addComponent(p_component);
	components[typeid(T)].push_back(p_component);
}

template <typename T>
void EntityHandler::removeComponent(Entity* p_entity)
{
	p_entity->removeComponent<typename T>();
	std::vector<Component*>& v = components[typeid(T)];
	v.erase(std::remove(v.begin(), v.end(), p_entity->getComponent<typename T>()), v.end());
}	

template <typename T>
std::vector<T*> EntityHandler::getComponents()
{
	std::vector<T*> result;
	for (Component* c : components[typeid(T)])
	{
		//T* is a derived Class to Component
		//static_cast converts Type:Component(Pointer) into Type:T*
		result.push_back(static_cast<T*>(c));
	}
	return result;
}


