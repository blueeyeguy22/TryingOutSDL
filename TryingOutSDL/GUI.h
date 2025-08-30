//
// Created by szlovimate on 8/2/25.
//

#ifndef GUI_H
#define GUI_H


#include "Window.h"
#include "CharacterTable.h"
#include <chrono>
#include <string>
#include <cstring>
#include <algorithm>

void GUI_run()
{
    KeyboardLang keyboard(KeyboardLang::HUN);
    int repeatDelay = 500;
    int repeatRate = 50; 
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
                if (keyboard.getChar(event.key.scancode)[0]!=0)
                {
                    if (!keyPressed || timeSinceLastKey > (keyPressed ? repeatRate : repeatDelay)) //De ez miért működik/segít? továbbra is fura
                    {

                        std::string character = keyboard.getChar(event.key.scancode);

                        if (capitalize)
                        {

                            std::transform(character.begin(), character.end(), character.begin(),::toupper);
                            capitalize=false;
                        }
                        window.texts.at(line) += character;
                        window.texting(line);
                        lastKeyTime = currentTime;
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
            case SDL_EVENT_KEY_UP:
                for (uint16_t i=4; i<=512;++i)
                {
                    if (event.key.scancode==i)
                    {
                        std::cout<<"Last button number was: "<<i <<"\n";
                    }
                }
                break;
            default:
				break;
            }
            keyPressed = anyKeyPressed;


            SDL_SetRenderDrawColor(window.get_renderer(), 0, 0, 0, 255); //Fekete, de akar egy SDL_Color tipusu valtozot is kaphat masodik argumentumkent
            SDL_RenderClear(window.get_renderer());
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
