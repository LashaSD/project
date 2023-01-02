#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Entity.hpp"
#include "Math.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	int getRefreshRate();
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void addToQueue(Entity& p_entity);
	void addToQueue(std::vector<Entity> p_entities);
	std::vector<Entity>& getQueue();
	void renderQueue();
	void display();
private:
	SDL_Window* window; 
	SDL_Renderer* renderer; 
	SDL_Texture* texture;
	std::vector<Entity> queue;
};
