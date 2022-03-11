#include <SDL2/SDL.h>
#include "Object.hpp"

Object::Object(int w, int h, float x, float y, SDL_Color color)
{
    Position = { x, y };
    Direction = { 0, 0 };
    Speed = 1.0;
    Color = color;

    _width = w;
    _height = h;
}

SDL_Rect Object::GetRect()
{
    int x = Position.x;
    int y = Position.y;

    SDL_Rect rect = { x, y, _width, _height };

    return rect;
}

void Object::Update(const Uint8* keys)
{
    Direction = { 0, 0 };

    if(keys[SDL_SCANCODE_RIGHT] == 1)
        Direction.x = 1;

    if(keys[SDL_SCANCODE_LEFT] == 1)
        Direction.x = -1;

    if(keys[SDL_SCANCODE_UP] == 1)
        Direction.y = -1;
    
    if(keys[SDL_SCANCODE_DOWN] == 1)
        Direction.y = 1;

    Position.x += Direction.x * Speed;
    Position.y += Direction.y * Speed;
}


void Object::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_Rect rect = GetRect();
    SDL_RenderFillRect(renderer, &rect);
}

