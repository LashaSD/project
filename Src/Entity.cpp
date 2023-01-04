#include <SDL.h>
#include <SDL_image.h>
#include <typeinfo>
#include <typeindex>

#include "Entity.hpp"
#include "Math.hpp"

template <typename T>
void Entity::addComponent(T* p_component)
{
	components[typeid(typename T)] = p_component;
}

template <typename T>
void Entity::removeComponent()
{
	components.erase(typeid(typename T));
}
