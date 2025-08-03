//
// Created by szlovimate on 8/2/25.
//

#include "Window.h"

Window::Window()
{
    create_window(800,600);
}

Window::~Window()
{
    close_window();
    //delete(text);
}

//GETTERS

SDL_Window* Window::get_window()
{
    return window;
}

//SETTERS



void Window::create_window(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        close_window();
        return;
    }

    window = SDL_CreateWindow("Szovegszerkeszto", width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Window init failed: %s", SDL_GetError());
        close_window();
        return;
    }
    change_font("LucidaSansRegular.ttf", 12, {255,255,255,255});

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        close_window();
        return;
    }
    text = "Hello test\nHello again";
    texting();
}
void Window::texting()
{
    size_t length = text.length();
    int textH = TTF_GetFontHeight(font);
    int textW;
    size_t measured_length;
    //TTF_MeasureString(font, text.c_str(), length, 0, &textW, &measured_length);
    length = text.length(); //Iras utan megvaltozik a text hossza, updateljuk
    TTF_MeasureString(font, text.c_str(), length, 0, &textW, &measured_length); //Elokeszitjuk renderelesre
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), length, textColor);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        //if (texture) {
        //    SDL_FRect dst = { 50, 50, (float)textW, (float)textH };
        //    SDL_RenderTexture(renderer, texture, NULL, &dst);
        //    SDL_DestroyTexture(texture);
        //}
    }
    //SDL_Delay(100);
    update_window();
}

void Window::update_window()
{
    if (!renderer || !texture) return;
    SDL_GetTextureSize(texture, &dst.w, &dst.h);
    dst.x=50;
    dst.y=50;
    //dst.w = 200;

    //dst.h = 50;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Fekete, de akar egy SDL_Color tipusu valtozot is kaphat masodik argumentumkent
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);
    SDL_Delay(16); //Ez kb 60 fps. A framek kozott 16 ms-t var
}

void Window::change_font(std::string font_name, float font_size, SDL_Color font_color)
{
    if (TTF_Init() < 0) {
        SDL_Log("TTF init failed: %s", SDL_GetError());
        close_window();
        return;
    }

    font = TTF_OpenFont(font_name.c_str(), font_size);
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        close_window();
        return;
    }

    this->textColor = font_color;
}

void Window::close_window()
{
    //if (font)
    //{
    //    TTF_CloseFont(font);
    //}
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}


