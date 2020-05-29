#pragma once
#include <Windows.h>
#include <stdio.h>

typedef enum
{
	down, up, right, left, def
}key_condition;

typedef struct
{
	char* name;
	POINT position[2];
	COLORREF color, highlighted_color;
	int win_link;
}button_t;

typedef struct
{
	int but_count, level, show;
	button_t* buttons;
}window_t;

typedef struct 
{
	int win_count, current_win, current_but;
	window_t* windows;
}menu_t;

char* Word(FILE* file);
int Number(FILE* file);
menu_t* Extract();

void Check(menu_t* menu, key_condition key);
void Draw(HDC hdc, menu_t* menu, key_condition key);
