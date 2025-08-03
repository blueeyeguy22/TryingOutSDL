//
// Created by szlovimate on 8/2/25.
//

#ifndef GUI_H
#define GUI_H


#include "Window.h"
#include <chrono>

void GUI_run()
{
    int repeatDelay = 500; // Initial delay in ms
    int repeatRate = 50;   // Repeat rate in ms
    const bool* keyState;
    bool anyKeyPressed;
    bool keyPressed = false;

    bool running = true;
    Window window;
    SDL_Event event;
    bool capitalize = false;
    while (running)
    {
        const bool* keyState = SDL_GetKeyboardState(nullptr);
        std::chrono::steady_clock::time_point lastKeyTime;
        auto currentTime = std::chrono::steady_clock::now();
        auto timeSinceLastKey = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastKeyTime).count();
        anyKeyPressed = false;
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
            case SDL_EVENT_KEY_DOWN:

                if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
                {
                    capitalize=true;
                }
                //event.key.scancode == SDL_SCANCODE_LSHIFT ? capitalize=true : capitalize=false;
                for (uint16_t keychar=4; keychar<30; keychar++)
                {
                    if (!capitalize && event.key.scancode==keychar)
                    {
                        if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                        {
                            window.text+='a'+keychar-4;
                            window.texting();
                            //SDL_Delay(70);
                            lastKeyTime = currentTime;
                        }
                        break;
                    }
                    else if (capitalize && event.key.scancode==keychar)
                    {
                        if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                        {
                            window.text+='A'+keychar-4;
                            window.texting();
                            //SDL_Delay(70);
                            lastKeyTime = currentTime;
                            capitalize=false;
                        }
                        break;
                    }
                }
                for (uint16_t keychar=30; keychar<39; keychar++)
                {
                    if (event.key.scancode==keychar)
                    {
                        if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                        {
                            window.text+='1'+keychar-30;
                            window.texting();
                            //SDL_Delay(70);
                            lastKeyTime = currentTime;
                            break;
                        }
                    }
                }
                if (event.key.scancode==SDL_SCANCODE_0)
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.text+='0';
                        window.texting();
                        //SDL_Delay(70);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
                if (event.key.scancode==SDL_SCANCODE_BACKSPACE && !window.text.empty())
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.text.pop_back();
                        window.texting();
                        //SDL_Delay(70);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
                if (event.key.scancode ==SDL_SCANCODE_SPACE)
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.text += ' ';
                        window.texting();
                        //SDL_Delay(70);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
            default:
                break;
            }
            keyPressed = anyKeyPressed;
        }


        /*keyState = SDL_GetKeyboardState(NULL); //Megnezi, hogy le van-e nyomva egy adott gomb (igaz-hamis tombot ad vissza)
        if (keyState[SDL_SCANCODE_BACKSPACE] && !window.text.empty()) {
            window.text.pop_back();
            window.texting();
            SDL_Delay(100);
        }
        if (keyState[SDL_SCANCODE_SPACE]) {
            window.text += ' ';
            window.texting();
            SDL_Delay(100);
        }
        for (int i = SDL_SCANCODE_A; i <= SDL_SCANCODE_Z; i++) {
            if (keyState[i]) {
                char c = 'a' + (i - SDL_SCANCODE_A);
                window.text += c;
                window.texting();
                SDL_Delay(100);
                break;
            }
        }
        for (int i = SDL_SCANCODE_1; i <= SDL_SCANCODE_0; i++) {
            if (keyState[0]) {
                window.text += '0';
                window.texting();
                SDL_Delay(100);
                break;
            }
            else {
                if (keyState[i]) {
                    char c = '1' + (i - SDL_SCANCODE_1);
                    window.text += c;
                    window.texting();
                    SDL_Delay(100);
                    break;
                }
            }
        }*/
    }
}

#endif //GUI_H
