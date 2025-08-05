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
    int line = 1;
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
                window.texts.at(line) += event.text.text;
                window.texting(line);
                break;
            case SDL_EVENT_KEY_DOWN:

                if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
                {
                    capitalize=true;
                }
				if (keyState[SDL_SCANCODE_RETURN])
                {
                    window.texts.at(line) += '\n';
					window.texting(line);
					lastKeyTime = currentTime;
                    window.texts.push_back(""); //Hozzaadunk egy uj sort, amit majd modositunk kesobb, hozzaadunk-torlunk belole
					window.add_texture(nullptr); //Hozzaadunk egy ures texturat, amit majd feltoltunk a texting() fuggvenyben
					line++; 
                    if (window.get_dsts().size() <= line)
                        window.get_dsts().resize(line + 1, {0, 0, 0, 0});

                    window.get_dsts().at(line).y = 20.0f * (line - 1); // Set Y position explicitly

                    break;
				}
                for (uint16_t keychar=4; keychar<30; keychar++)
                {
                    if (!capitalize && event.key.scancode==keychar)
                    {
                        if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                        {
                            window.texts.at(line) += 'a' + keychar - 4;
                            window.texting(line);
                            lastKeyTime = currentTime;
                        }
                        break;
                    }
                    else if (capitalize && event.key.scancode==keychar)
                    {
                        if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                        {
                            window.texts.at(line) += 'A' + keychar - 4;
                            window.texting(line);
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
                            window.texts.at(line) += '1' + keychar - 30;
                            window.texting(line);
                            lastKeyTime = currentTime;
                            break;
                        }
                    }
                }
                if (event.key.scancode==SDL_SCANCODE_0)
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.texts.at(line) += '0';
                        window.texting(line);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
                if (event.key.scancode==SDL_SCANCODE_BACKSPACE && !window.texts.at(line).empty())
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.texts.at(line).pop_back();
                        window.texting(line);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
                if (event.key.scancode ==SDL_SCANCODE_SPACE)
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay))
                    {
                        window.texts.at(line) += ' ';
                        window.texting(line);
                        lastKeyTime = currentTime;
                        break;
                    }
                }
                break;
            default:
				break;
            }
            keyPressed = anyKeyPressed;
            /*
            if (!window.get_renderer()) return;
            if (line >= window.texts.size()|| !window.get_texture(line)) return;*/
            //SDL_GetTextureSize(window.get_texture(), &window.get_dst().w, &window.get_dst().h);

            //dst.w = 200;

            //dst.h = 50;


            SDL_SetRenderDrawColor(window.get_renderer(), 0, 0, 0, 255); //Fekete, de akar egy SDL_Color tipusu valtozot is kaphat masodik argumentumkent
            SDL_RenderClear(window.get_renderer());
            //SDL_RenderTexture(window.get_renderer(), window.get_texture(line), NULL, &window.get_dst());
            for (int i = 1; i <= line; ++i)
            {
                SDL_Texture* tex = window.get_texture(i);
                if (!tex) continue;

                SDL_FRect dst = window.get_dsts().at(i);
                dst.x = 0.0f;
                dst.y = 20.0f * (i - 1);

                SDL_RenderTexture(window.get_renderer(), tex, nullptr, &dst);
            }



            
            SDL_RenderPresent(window.get_renderer());
            SDL_Delay(16); //Ez kb 60 fps. A framek kozott 16 ms-t var

        }
    }
}

#endif //GUI_H
