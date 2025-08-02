#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>



int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        SDL_Log("TTF init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Szovegszerkeszto", 640, 480, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Window init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("LucidaSansRegular.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = { 0, 0, 0, 255 }; //fekete
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Renderer init failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    std::string text = ""; //std::string&, mert ezzel konnyebb dolgozni, de parameterkent text.c_str()-kent adjuk at, mivel az SDL const char*-okkal dolgozik
    size_t length = text.length(); //Azert size_t, mert a legtobb fuggveny ilyen tipusu parameterekkel dolgozik
    int textW = 0;
    size_t measured_length = 0;
    int textH = TTF_GetFontHeight(font);
    TTF_MeasureString(font, text.c_str(), length, 0, &textW, &measured_length); //A szoveg renderelesehez kell, megnezi, hogy hogyan fer el a szoveg a kepernyon, hogyan renderelje
    //A 4. argumentum a limit, 0 vagy MAX_INT eseten nincs limit

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                SDL_DestroyWindow(window);
                SDL_Quit();
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                running = false;
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_DestroyWindow(window);
                SDL_Quit();
                break;
            case SDL_EVENT_TEXT_INPUT:
                text += event.text.text;
                break;
            default:
                break;
            }
        }
        const bool* keyState = SDL_GetKeyboardState(NULL); //Megnezi, hogy le van-e nyomva egy adott gomb (igaz-hamis tombot ad vissza)
        if (keyState[SDL_SCANCODE_BACKSPACE] && !text.empty()) {
            text.pop_back();
            SDL_Delay(100);
        }
        if (keyState[SDL_SCANCODE_BACKSPACE]) {
            text += ' ';
            SDL_Delay(100);
        }
        for (int i = SDL_SCANCODE_A; i <= SDL_SCANCODE_Z; i++) {
            if (keyState[i]) {
                char c = 'a' + (i - SDL_SCANCODE_A);
                text += c;
                SDL_Delay(100);
                break;
            }
        }
        for (int i = SDL_SCANCODE_1; i <= SDL_SCANCODE_0; i++) {
            if (keyState[0]) {
                text += '0';
                SDL_Delay(100);
                break;
            }
            else {
                if (keyState[i]) {
                    char c = '1' + (i - SDL_SCANCODE_1);
                    text += c;
                    SDL_Delay(100);
                    break;
                }
            }
        }
        //..... ide meg hozzaadhatunk mas gombkombinaciokat is, amelyek nem irni fognak, hanem mast csinalnak
        length = text.length(); //Iras utan megvaltozik a text hossza, updateljuk
        TTF_MeasureString(font, text.c_str(), length, 0, &textW, &measured_length); //Elokeszitjuk renderelesre
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), length, textColor);
        if (surface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            if (textTexture) {
                SDL_FRect dst = { 50, 50, (float)textW, (float)textH };
                SDL_RenderTexture(renderer, textTexture, NULL, &dst);
                SDL_DestroyTexture(textTexture);
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Feher, de akar egy SDL_Color tipusu valtozot is kaphat masodik argumentumkent
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); //Ez kb 60 fps. A framek kozott 16 ms-t var
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}