//
// Created by szlovimate on 8/2/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>

class Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    //SDL_Texture *texture;
	std::vector<SDL_Texture*> textures;
    SDL_Color textColor;
    std::vector<SDL_FRect> dsts;
public:
    std::vector<std::string> texts;
    Window();
    ~Window();
    SDL_Window* get_window();
    SDL_Renderer* get_renderer();
    SDL_Texture* get_texture(int pos);
    //SDL_FRect& get_dst();
    std::vector<SDL_FRect>& get_dsts();
    TTF_Font* get_font();
    void create_window(int,int);
    void texting(int pos);
    //void update_window();
    void add_texture(SDL_Texture* newTexture);
    void close_window();
    void change_font(std::string, float, SDL_Color);
    void set_dst_x(float x);
	void set_dst_y(float y);
	void set_dst_w(float w);
	void set_dst_h(float h);
    void set_dst(float x, float y, float w, float h);
};



#endif //WINDOW_H
