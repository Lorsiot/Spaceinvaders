#ifndef GAME_H
#define GAME_H

#include <resource_manager.h>
#include <sprite_renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <game_object.h>
#include <cmath>

enum class GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;

	Game(unsigned int width, unsigned int height);

	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

#endif