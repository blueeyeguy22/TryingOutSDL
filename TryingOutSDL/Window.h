//
// Created by szlovimate on 8/2/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture *texture;
    SDL_Color textColor;
    SDL_FRect dst;
public:
    std::string text;
    Window();
    ~Window();
    SDL_Window* get_window();
    void create_window(int,int);
    void texting();
    void update_window();
    void close_window();
    void change_font(std::string, float, SDL_Color);
};



#endif //WINDOW_H
