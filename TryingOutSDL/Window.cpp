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

SDL_Renderer* Window::get_renderer()
{
    return renderer;
}

SDL_Texture* Window::get_texture(int pos)
{
    return textures.at(pos);
}

std::vector<SDL_FRect>& Window::get_dsts()
{
	return dsts;
}


TTF_Font* Window::get_font()
{
	return font;
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
    change_font("DejaVuSerif.ttf", 12, {255,255,255,255});

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        close_window();
        return;
    }
	texts.push_back(""); //Ez arra jo, hogy a sorok szamozasa 1-tol induljon (a 0. sort nem hasznaljuk)
    textures.push_back(nullptr);
    dsts.push_back({ 0, 0, 0, 0 });
	texts.push_back("Hello test");
    textures.push_back(nullptr);
    dsts.push_back({ 0, 0, 0, 0 });
    texting(1);
	
}
void Window::texting(int pos)
{
    size_t length = texts.at(pos).length();
    /*int textH = TTF_GetFontHeight(font);
    int textW;
    size_t measured_length;
    length = texts.at(pos).length(); //Iras utan megvaltozik a text hossza, updateljuk
    TTF_MeasureString(font, texts.at(pos).c_str(), length, 0, &textW, &measured_length); //Elokeszitjuk renderelesre
    */
    //std::cout<<texts.at(pos)<<std::endl;
    SDL_Surface* surface = TTF_RenderText_Solid(font, texts.at(pos).c_str(), length, textColor);
    if (surface) {
		textures.at(pos) = SDL_CreateTextureFromSurface(renderer, surface);
        if (dsts.size() <= pos) {
			dsts.resize(pos + 1, {0,0,0,0});
        }
        dsts.at(pos).w = static_cast<float>(surface->w);
        dsts.at(pos).h = static_cast<float>(surface->h);
        SDL_DestroySurface(surface);
    }
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

void Window::set_dst_x(float x)
{
    auto szam = dsts.end();
	int idx = std::distance(dsts.begin(), szam);
	dsts.at(idx).x = x;
}

void Window::set_dst_y(float y)
{
    auto szam = dsts.end();
    int idx = std::distance(dsts.begin(), szam);
	dsts.at(idx).y = y;
}

void Window::set_dst_w(float w)
{
    auto szam = dsts.end();
    int idx = std::distance(dsts.begin(), szam);
	dsts.at(idx).w = w;
}

void Window::set_dst_h(float h)
{
    auto szam = dsts.end();
    int idx = std::distance(dsts.begin(), szam);
	dsts.at(idx).h = h;
}

void Window::set_dst(float x, float y, float w, float h)
{
    set_dst_x(x);
    set_dst_y(y);
    set_dst_w(w);
    set_dst_h(h);
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

void Window::add_texture(SDL_Texture* newTexture)
{
	textures.push_back(newTexture);
}

/*void Window::update_window()
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
}*/
