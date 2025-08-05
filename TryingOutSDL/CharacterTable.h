//
// Created by szlovimate on 8/5/25.
//

#ifndef TRYINGOUTSDL_CHARACTERTABLE_H
#define TRYINGOUTSDL_CHARACTERTABLE_H
#include <SDL3/SDL_scancode.h>
#include <map>



class KeyboardLang
{
private:
    std::map<SDL_Scancode, wchar_t> currentMapping;

    std::map<SDL_Scancode, wchar_t> hungarian_keymap
    {
        {SDL_SCANCODE_0, L'ö'},
        {SDL_SCANCODE_GRAVE, '0'},
        {SDL_SCANCODE_Z, 'y'},
        {SDL_SCANCODE_Y, 'z'},
        {SDL_SCANCODE_NONUSBACKSLASH, L'í'},
        {SDL_SCANCODE_BACKSLASH, L'ű'},
        {SDL_SCANCODE_APOSTROPHE, L'á'},
        {SDL_SCANCODE_SEMICOLON,L'é'},
        {SDL_SCANCODE_RIGHTBRACKET, L'ú'},
        {SDL_SCANCODE_LEFTBRACKET, L'ő'},
        {SDL_SCANCODE_EQUALS, L'ó'},
        {SDL_SCANCODE_MINUS, L'ü'},
        {SDL_SCANCODE_COMMA, ','},
        {SDL_SCANCODE_PERIOD, '.'},
        {SDL_SCANCODE_SLASH, '-'},
    };

    std::map<SDL_Scancode, wchar_t> english_keymap
    {
        {SDL_SCANCODE_0, '0'},
        {SDL_SCANCODE_GRAVE, '`'},
        {SDL_SCANCODE_NONUSBACKSLASH, L'<'},
        {SDL_SCANCODE_BACKSLASH, L'\\'},
        {SDL_SCANCODE_APOSTROPHE, L'\''},
        {SDL_SCANCODE_SEMICOLON,L';'},
        {SDL_SCANCODE_RIGHTBRACKET, L'['},
        {SDL_SCANCODE_LEFTBRACKET, L']'},
        {SDL_SCANCODE_EQUALS, L'='},
        {SDL_SCANCODE_MINUS, L'-'},
        {SDL_SCANCODE_COMMA, ','},
        {SDL_SCANCODE_PERIOD, '.'},
        {SDL_SCANCODE_SLASH, '/'},
    };

public:

    typedef enum e_lang
    {
        HUN,
        ENG
    }e_lang;

    KeyboardLang(e_lang select)
    {
        switch (select)
        {
        case HUN:
            currentMapping = hungarian_keymap;

            break;
        case ENG:
            currentMapping = english_keymap;
            break;
        default:
            currentMapping = english_keymap;
            break;
        }
        for (int16_t keychar=SDL_SCANCODE_A; keychar<=SDL_SCANCODE_X; keychar++)
        {
            currentMapping[(SDL_Scancode)keychar] = 'a' +keychar-SDL_SCANCODE_A;
        }
        for (int16_t numchar=SDL_SCANCODE_1; numchar<=SDL_SCANCODE_9; numchar++)
        {
            currentMapping[(SDL_Scancode)numchar] = '1' +numchar-SDL_SCANCODE_1;
        }
    }

    //Monsieur ChatGPT dobta, nekem pár rész magas még: miért működik csak autoval. Mit ad a const kulcsszó
    wchar_t getChar(SDL_Scancode scancode) const
    {
        auto it = currentMapping.find(scancode);
        return it != currentMapping.end() ? it->second : 0;
    }

};
#endif //TRYINGOUTSDL_CHARACTERTABLE_H