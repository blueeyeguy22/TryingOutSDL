#pragma once

#include "Window.h"
#include "CharacterTable.h"
#include <chrono>
#include <string>
#include <cstring>
#include <algorithm>

class SDLHandler {
private:
    bool running = true;
    bool keyPressed = false;
    bool capitalize = false;
    int line = 1;
    int repeatDelay = 500;
    int repeatRate = 50;
    bool anyKeyPressed = false;
    std::chrono::steady_clock::time_point lastKeyTime;
    Window window;
    KeyboardLang keyboard{ KeyboardLang::HUN };
public:
    bool getRunning();
	bool getKeyPressed();
	bool capitalizeStatus();
	int getLine();
	int getRepeatDelay();
	int getRepeatRate();
	bool getAnyKeyPressed();
	std::chrono::steady_clock::time_point getLastKeyTime();
	Window& getWindow();
	KeyboardLang& getKeyboard();
	void setRunning(bool status);
	void setKeyPressed(bool status);
	void setCapitalize(bool status);
	void setLine(int newLine);
	void setRepeatDelay(int delay);
	void setRepeatRate(int rate);
	void setAnyKeyPressed(bool status);
	void setLastKeyTime(std::chrono::steady_clock::time_point time);
	void setWindow(const Window& win);
	void setKeyboard(const KeyboardLang& lang);
	void incrementLine();
};