#pragma once

#include <typeinfo>
#include <typeindex>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>


#include "Entity.hpp"
#include "Component.hpp"

class EntityHandler 
{
public:
	EntityHandler();
	~EntityHandler();

	Entity* createEntity();
	void destroyEntity(Entity* p_entity);
	
	template <typename T>
	void addComponent(Entity* p_entity, T* p_component);

	template <typename T>
	void removeComponent(Entity* p_entity);

	template <typename T>
	std::vector<T*> getComponents();
private:
	int nextEntityId = 0;
	std::unordered_map<int, Entity*> entities;
	std::unordered_map<std::type_index, std::vector<Component*>> components;	
};