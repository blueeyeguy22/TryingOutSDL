//
// Created by szlovimate on 8/2/25.
//

#ifndef GUI_H
#define GUI_H

#include "SDLHandling.h"

void GUI_run()
{
	SDLHandler state;
	while (state.getRunning())
	{
		SDLHandling(state);
	}
}


#endif //GUI_H
