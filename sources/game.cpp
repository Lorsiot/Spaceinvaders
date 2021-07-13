#include "game.h"

Game::Game(unsigned int width, unsigned int height)
    : State(GameState::GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

SpriteRenderer* Renderer;
GameObject* Player;

const glm::vec2 PLAYER_SIZE(66.0f, 37.5f);

const float PLAYER_VELOCITY(300.0f);


void Game::Init()
{

    ResourceManager::LoadShader("resources/shaders/shader.vert", "resources/shaders/shader.frag", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("resources/textures/playerShip.png", true, "playerShip");

    ResourceManager::LoadTexture("resources/textures/background.png", false, "background");
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);

    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("playerShip"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->State == GameState::GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;

        if (this->Keys[GLFW_KEY_UP])
        {
            if (Player->Position.y >= 0.0f)
                Player->Position.y -= velocity;
            
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (Player->Position.y <= this->Height - Player->Size.y)
                Player->Position.y += velocity;
        }
        if (this->Keys[GLFW_KEY_LEFT])
        {
            if (Player->Position.x >= 0.0f)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }

    }
}


void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("background"),
        glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    Player->Draw(*Renderer);
}