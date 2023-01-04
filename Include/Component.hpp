#pragma once 

#include "Entity.hpp"

class Component 
{
public:
	virtual ~Component();
private:
	Entity* entity;
};