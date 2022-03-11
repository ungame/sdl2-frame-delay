#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>

class Object
{
    public:
        SDL_Color Color;
        SDL_FPoint Position;
        SDL_FPoint Direction;
        float Speed;

    private:
        int _width;
        int _height;

    public:
        Object(int w, int h, float x, float y, SDL_Color color = {189, 189, 189, SDL_ALPHA_TRANSPARENT});
        SDL_Rect GetRect();
        void Update(const Uint8* keys);
        void Draw(SDL_Renderer* renderer);

    public:
        inline int GetWidth() { return _width; }
        inline int GetHeight() { return _height; }
};

#endif
