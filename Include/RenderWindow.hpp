#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Entity.hpp"
#include "RigidBody.hpp"
#include "Math.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);

	SDL_Texture* loadTexture(const char* p_filePath);

	float getRefreshRate();

	void cleanUp();
	void clear();
	void display();

	void render(Rigidbody& p_entity);

	void addToScene(Rigidbody& p_entity);
	void addToScene(std::vector<Rigidbody> p_entities);
	std::vector<Rigidbody>& getScene();
	void renderScene();
private:
	SDL_Window* window; 
	SDL_Renderer* renderer; 
	SDL_Texture* texture;
	std::vector<Rigidbody> scene;
};
