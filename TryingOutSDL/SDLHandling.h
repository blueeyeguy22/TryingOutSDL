#pragma once
#include "SDLHandler.h"

void SDLHandling(SDLHandler& state) {

    const bool* keyState = SDL_GetKeyboardState(nullptr);
    SDL_Event event;

    auto currentTime = std::chrono::steady_clock::now();
    auto timeSinceLastKey = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - state.getLastKeyTime()).count();

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            state.getWindow().close_window();
            state.setRunning(false);
            break;

        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            state.getWindow().close_window();
            state.setRunning(false);
            break;

        case SDL_EVENT_TEXT_INPUT:
            state.getWindow().texts.at(state.getLine()) += event.text.text;
            state.getWindow().texting(state.getLine());
            break;

        case SDL_EVENT_KEY_DOWN:
            if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
                state.setCapitalize(true);
            }
            if (keyState[SDL_SCANCODE_RETURN]) {
                state.getWindow().texting(state.getLine());
                state.setLastKeyTime(currentTime);

                state.getWindow().texts.push_back("");
                state.getWindow().add_texture(nullptr);

                state.incrementLine();
                if (state.getWindow().get_dsts().size() <= state.getLine())
                    state.getWindow().get_dsts().resize(state.getLine() + 1, { 0, 0, 0, 0 });

                state.getWindow().get_dsts().at(state.getLine()).y = 20.0f * (state.getLine() - 1);
                break;
            }
            if (state.getKeyboard().getChar(event.key.scancode)[0] != 0) {
                if (!state.isKeyPressed() || timeSinceLastKey > (state.isKeyPressed() ? state.getRepeatRate() : state.getRepeatDelay())) {
                    std::string character = state.getKeyboard().getChar(event.key.scancode);
                    if (state.isCapitalized()) {
                        std::transform(character.begin(), character.end(), character.begin(), ::toupper);
                        state.setCapitalize(false);
                    }
                    state.getWindow().texts.at(state.getLine()) += character;
                    state.getWindow().texting(state.getLine());
                    state.setLastKeyTime(currentTime);
                }
            }
            if (event.key.scancode == SDL_SCANCODE_BACKSPACE && !state.getWindow().texts.at(state.getLine()).empty()) {
                if (!state.isKeyPressed() || timeSinceLastKey > (state.isKeyPressed() ? state.getRepeatRate() : state.getRepeatDelay())) {
                    state.getWindow().texts.at(state.getLine()).pop_back();
                    state.getWindow().texting(state.getLine());
                    state.setLastKeyTime(currentTime);
                    break;
                }
            }
            if (event.key.scancode == SDL_SCANCODE_SPACE) {
                if (!state.isKeyPressed() || timeSinceLastKey > (state.isKeyPressed() ? state.getRepeatRate() : state.getRepeatDelay())) {
                    state.getWindow().texts.at(state.getLine()) += ' ';
                    state.getWindow().texting(state.getLine());
                    state.setLastKeyTime(currentTime);
                    break;
                }
            }
            break;
        }
    }

    SDL_SetRenderDrawColor(state.getWindow().get_renderer(), 0, 0, 0, 255);
    SDL_RenderClear(state.getWindow().get_renderer());
    for (int i = 1; i <= state.getLine(); ++i) {
        SDL_Texture* tex = state.getWindow().get_texture(i);
        if (!tex) continue;
        SDL_FRect dst = state.getWindow().get_dsts().at(i);
        dst.x = 0.0f;
        dst.y = 20.0f * (i - 1);
        SDL_RenderTexture(state.getWindow().get_renderer(), tex, nullptr, &dst);
    }
    SDL_RenderPresent(state.getWindow().get_renderer());
    SDL_Delay(16);

}