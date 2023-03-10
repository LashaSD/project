#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
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

float RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);	
	return (float)mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Rigidbody& p_entity)
{
	SDL_Rect src; //Starting Point of render of the Texture
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dest; //Finishing Point of render of the Texture
	dest.x = p_entity.getPos().x;
	dest.y = p_entity.getPos().y;
	dest.w = p_entity.getCurrentFrame().w;
	dest.h = p_entity.getCurrentFrame().h;	 
	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}

void RenderWindow::addToScene(Rigidbody& p_entity)
{
	scene.push_back(p_entity);
}

void RenderWindow::addToScene(std::vector<Rigidbody> p_entities)
{
	for (Rigidbody& entity : p_entities)
	{
		scene.push_back(entity);
	}
}

std::vector<Rigidbody>& RenderWindow::getScene()
{
	return scene;
}

void RenderWindow::renderScene()
{
	for (Rigidbody& entity : scene)
	{
		render(entity);
	}
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}