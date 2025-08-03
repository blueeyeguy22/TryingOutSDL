//
// Created by szlovimate on 8/2/25.
//

#ifndef GUI_H
#define GUI_H


#include "Window.h"

void GUI_run()
{
    const bool* keyState;
    bool running = true;
    Window window;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                window.close_window();
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                running = false;
                window.close_window();
                break;
            case SDL_EVENT_TEXT_INPUT:
                window.text += event.text.text;
                window.texting();
                break;
            default:
                break;
            }
        }

        keyState = SDL_GetKeyboardState(NULL); //Megnezi, hogy le van-e nyomva egy adott gomb (igaz-hamis tombot ad vissza)
        if (keyState[SDL_SCANCODE_BACKSPACE] && !window.text.empty()) {
            window.text.pop_back();
            window.texting();
            SDL_Delay(60);
        }
        if (keyState[SDL_SCANCODE_SPACE]) {
            window.text += ' ';
            window.texting();
            SDL_Delay(60);
        }
        for (int i = SDL_SCANCODE_A; i <= SDL_SCANCODE_Z; i++) {
            if (keyState[i]) {
                char c = 'a' + (i - SDL_SCANCODE_A);
                window.text += c;
                window.texting();
                SDL_Delay(60);
                break;
            }
        }
        for (int i = SDL_SCANCODE_1; i <= SDL_SCANCODE_0; i++) {
            if (keyState[0]) {
                window.text += '0';
                window.texting();
                SDL_Delay(60);
                break;
            }
            else {
                if (keyState[i]) {
                    char c = '1' + (i - SDL_SCANCODE_1);
                    window.text += c;
                    window.texting();
                    SDL_Delay(60);
                    break;
                }
            }
        }
    }
}

#endif //GUI_H
