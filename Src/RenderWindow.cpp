#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "PositionComponent.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		printf("Couldn't SDL_CreateWindow, SDL_ERROR: %s\n", SDL_GetError());
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == nullptr)
		printf("Couldn't load the Texture, IMG_ERROR: %s\n", IMG_GetError());	

	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);	
	return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity* p_entity)
{
	PositionComponent* position = p_entity->getComponent<PositionComponent*>();
	SDL_Rect src; //Starting Point of render of the Texture
	src.x = 0;
	src.y = 0;
	src.w = 32; //Implement Appearance Component Later to give Scale and Texture
	src.h = 32; 

	SDL_Rect dest; //Finishing Point of render of the Texture
	dest.x = position->x;
	dest.y = position->y;
	dest.w = 32;
	dest.h = 32;	 

	// remove later when TextureComponent is implemented
	SDL_Texture* texture = loadTexture("res/gfx/ground_grass.png");


	SDL_RenderCopy(renderer, texture, &src, &dest);
}

void RenderWindow::addToQueue(Entity& p_entity)
{
	queue.push_back(p_entity);
}

void RenderWindow::addToQueue(std::vector<Entity> p_entities)
{
	for (Entity& entity : p_entities)
	{
		queue.push_back(entity);
	}
}

std::vector<Entity>& RenderWindow::getQueue()
{
	return queue;
}

void RenderWindow::renderQueue()
{
	for (Entity& entity : queue)
	{
		render(entity);
	}
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}