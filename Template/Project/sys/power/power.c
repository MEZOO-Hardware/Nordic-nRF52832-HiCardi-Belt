//
// Created by joey on 2025-03-04.
//

#include "power.h"

volatile bool	flagButtonPressed = false;

void enableFlagButtonState()
{
		flagButtonPressed = true;
}

void disableFlagButtonState()
{
		flagButtonPressed = false;
}

bool isPressedButton()
{
		return flagButtonPressed;
}


static uint16_t count;
	
typedef enum {IDLE, PRESSING, PRESSED, RELEASE} stateButton_t;

void scanButton()
{
	static stateButton_t state = IDLE;

	switch (state)
	{
	case IDLE:
		if(!PORT13_Button1) state = PRESSING;
		break;
	case PRESSING:
		if(PORT13_Button1) state = IDLE;
		else
		{
			state = PRESSED;
			count = 0;
		}
		break;
	case PRESSED:
		if(PORT13_Button1) state = RELEASE;
		else count++;
		if(count == 200)
		{
			enableFlagButtonState();
		}
		break;		
	case RELEASE:
		state = (PORT13_Button1)? IDLE : PRESSED;
		break;
	}
}