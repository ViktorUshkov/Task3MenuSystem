#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

menu_t* Extract()
{
	FILE* file = fopen("menu_structure.txt", "r");
	if (file == NULL) exit(-1);

	menu_t* menu = (menu_t*)malloc(sizeof(menu_t));
	menu->windows = (window_t*)malloc(sizeof(window_t));
	menu->win_count = 0;
	menu->current_but = 0;
	menu->current_win = 0;
	char* buffer;

	while (strcmp(buffer = Word(file), "MenuBegin") != 0);
	while (strcmp(buffer = Word(file), "MenuEnd") != 0)
	{
		if (strcmp(buffer, "WindowBegin") == 0) {
			menu->win_count++;
			if (menu->win_count > 1) 
				menu->windows = realloc(menu->windows, menu->win_count * sizeof(window_t));
			menu->windows[menu->win_count - 1].buttons = (button_t*)malloc(sizeof(button_t));
			menu->windows[menu->win_count - 1].but_count = 0;
			while (strcmp(buffer = Word(file), "WindowEnd") != 0) {
				if (strcmp(buffer, "Level") == 0)
					menu->windows[menu->win_count - 1].level = Number(file);
			}
		}
		if (strcmp(buffer, "ButtonBegin") == 0) {
			menu->windows[menu->win_count - 1].but_count++;
			if (menu->windows[menu->win_count - 1].but_count > 1) 
				menu->windows[menu->win_count - 1].buttons = realloc(menu->windows[menu->win_count - 1].buttons, menu->windows[menu->win_count - 1].but_count * sizeof(button_t));
			while (strcmp(buffer = Word(file), "ButtonEnd") != 0) {
				if (strcmp(buffer, "Position") == 0) {
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].position[0] = (POINT) { Number(file), Number(file) };
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].position[1] = (POINT) { Number(file), Number(file) };
				}
				if (strcmp(buffer, "Color") == 0)
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].color = RGB(Number(file), Number(file), Number(file));
				if (strcmp(buffer, "HighlightedColor") == 0)
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].highlighted_color = RGB(Number(file), Number(file), Number(file));
				if (strcmp(buffer, "Name") == 0)
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].name = Word(file);
				if (strcmp(buffer, "Link") == 0)
					menu->windows[menu->win_count - 1].buttons[menu->windows[menu->win_count - 1].but_count - 1].win_link = Number(file);
			}
		}
	}
	fclose(file);
	return menu;
}

char* Word(FILE* file)
{
	int i = 0;
	char symbol;
	char* word = (char*)malloc(sizeof(char));
	while (!isalpha(symbol = (char)fgetc(file)));
	do
	{
		word[i++] = symbol;
		word = realloc(word, (i + 1) * sizeof(char));
	} while (isalpha(symbol = (char)fgetc(file)));
	word[i] = '\0';
	return word;
}

int Number(FILE* file)
{
	int i = 0;
	char symbol;
	char* number = (char*)malloc(sizeof(char));
	while (!isdigit(symbol = (char)fgetc(file)));
	do
	{
		number[i++] = symbol;
		number = realloc(number, (i + 1) * sizeof(char));
	} while (isdigit(symbol = (char)fgetc(file)));
	number[i] = '\0';
	return atoi(number);
}