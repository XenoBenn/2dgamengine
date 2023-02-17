#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <glm/glm.hpp> ///home/xenoben/repos/pikuma/2dgamengine/libs/glm/glm.hpp

Game::Game(){
    isRunning = false;
    registry = std::make_unique<Registry>();
    Logger::Log("Game constructor called!");
}

Game::~Game(){
    Logger::Log("Game destructor called!");
}

void Game::Initialize(){
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
        Logger::Err("Error initializing SDL.");
        return; //Give an error if it couldn't initialize
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800;//displayMode.w;
    windowHeight = 600;//displayMode.h;
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS    
    );
    if (!window){
        Logger::Err("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        Logger::Err("Error creating SDL renderer");
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::ProcessInput(){
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            break;
        }
    }
}



void Game::Setup(){
    Entity tank = registry->CreateEntity();
    Entity truck = registry->CreateEntity();
}

void Game::Update(){
    //Update game objects...
    //If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME){
        SDL_Delay(timeToWait);
    }

    //The difference in ticks since the last frame, converted to seconds.
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    //Store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    //TODO:
    //MovementSystem.Update();
    //CollisionSystem();
    //DamageSystem();
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //TODO: Render game objects;

    SDL_RenderPresent(renderer);
}

void Game::Run(){
    Setup();
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
