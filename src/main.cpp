#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "Object.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720

#define WINDOW_TITLE "SDL2 FRAME DELAY"

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    bool running = true;
    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    Object* player = new Object(64, 64, 100, 100);
    player->Color = SDL_Color{255, 0, 0, SDL_ALPHA_TRANSPARENT};
    player->Speed = 8;
   
    float frameTime = 0;
    const float frameDelay = 1000/60; // 60 FPS

    while(running)
    {
        float startFrame = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    keys = SDL_GetKeyboardState(nullptr);
                    break;
            }
        }

        if(keys[SDL_SCANCODE_ESCAPE] == 1)
            running = false;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(renderer);

        std::string title = WINDOW_TITLE;
        title += " | ";
        title += "FrameTime=" + std::to_string(frameTime);

        SDL_SetWindowTitle(window, title.c_str());

        player->Update(keys);
        player->Draw(renderer);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - startFrame;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    
    delete player;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
