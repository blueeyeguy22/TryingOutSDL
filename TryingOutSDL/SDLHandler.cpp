#include "SDLHandler.h"

//GETTERS
bool SDLHandler::getRunning()
{
	return running;
}
bool SDLHandler::isKeyPressed()
{
	return keyPressed;
}
bool SDLHandler::isCapitalized()
{
	return capitalize;
}
int SDLHandler::getLine()
{
	return line;
}
int SDLHandler::getRepeatDelay()
{
	return repeatDelay;
}
int SDLHandler::getRepeatRate()
{
	return repeatRate;
}
bool SDLHandler::getAnyKeyPressed()
{
	return anyKeyPressed;
}
std::chrono::steady_clock::time_point SDLHandler::getLastKeyTime()
{
	return lastKeyTime;
}
Window& SDLHandler::getWindow()
{
	return window;
}
KeyboardLang& SDLHandler::getKeyboard()
{
	return keyboard;
}


//SETTERS 
void SDLHandler::setRunning(bool status)
{
	running = status;
}
void SDLHandler::setKeyPressed(bool status)
{
	keyPressed = status;
}
void SDLHandler::setCapitalize(bool status)
{
	capitalize = status;
}
void SDLHandler::setLine(int newLine)
{
	line = newLine;
}
void SDLHandler::setRepeatDelay(int delay)
{
	repeatDelay = delay;
}
void SDLHandler::setRepeatRate(int rate)
{
	repeatRate = rate;
}
void SDLHandler::setAnyKeyPressed(bool status)
{
	anyKeyPressed = status;
}
void SDLHandler::setLastKeyTime(std::chrono::steady_clock::time_point time)
{
	lastKeyTime = time;
}
void SDLHandler::setWindow(const Window& win)
{
	window = win;
}
void SDLHandler::setKeyboard(const KeyboardLang& lang)
{
	keyboard = lang;
}

//OTHER
void SDLHandler::incrementLine()
{
	line++;
}
