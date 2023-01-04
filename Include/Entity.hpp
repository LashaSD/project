#pragma once

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Component.hpp"

class Entity
{
public:
	Entity(int p_id) : id(p_id) {};
	~Entity();

	int getId() { return id; }

	template <typename T>
	void addComponent(T* p_component);

	template <typename T>
	void removeComponent();

	template <typename T>
	T* getComponent()
	{
		return static_cast<T*>(components[typeId(typename T)]);
	}
private:
	int id;
	std::unordered_map<std::type_index, Component*> components;
}; 