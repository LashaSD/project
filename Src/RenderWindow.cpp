#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		printf("Couldn't SDL_CreateWindow, SDL_ERROR: %s\n", SDL_GetError());
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == nullptr)
		printf("Couldn't load the Texture, IMG_ERROR: %s\n", IMG_GetError());	

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src; //Starting Point of render of the Texture
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dest; //Finishing Point of render of the Texture
	dest.x = p_entity.getX();
	dest.y = p_entity.getY();
	dest.w = p_entity.getCurrentFrame().w * 2;
	dest.h = p_entity.getCurrentFrame().h * 2;	 
	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}