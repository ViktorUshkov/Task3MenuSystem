#include <windows.h>
#include "header.h"

void Draw(HDC hdc, menu_t* menu, key_condition key)
{
	HBRUSH Brush;
	Check(menu, key);
	for (int i = 0; i < menu->win_count; i++)
	{
		if ((menu->windows[i].show == 1) || (menu->windows[i].level == 0))
		{
			for (int j = 0; j < menu->windows[i].but_count; j++)
			{
				if ((j == menu->current_but) && (i == menu->current_win))
					Brush = CreateSolidBrush(menu->windows[i].buttons[j].highlighted_color);
				else Brush = CreateSolidBrush(menu->windows[i].buttons[j].color);
				SelectObject(hdc, Brush);
				Rectangle(hdc, menu->windows[i].buttons[j].position[0].x, menu->windows[i].buttons[j].position[0].y, menu->windows[i].buttons[j].position[1].x, menu->windows[i].buttons[j].position[1].y);
				DeleteObject(Brush);
				DrawText(hdc, menu->windows[i].buttons[j].name, strlen(menu->windows[i].buttons[j].name), menu->windows[i].buttons[j].position, DT_CENTER);
			}
		}
	}
}

void Check(menu_t* menu, key_condition key)
{
	switch (key)
	{
	case down:
	{
		if (menu->current_but < menu->windows[menu->current_win].but_count - 1)
		{
			menu->current_but++;
			for (int i = 0; i < menu->win_count; i++)
			{
				if (menu->windows[i].level == menu->windows[menu->current_win].buttons[menu->current_but].win_link)
					menu->windows[i].show = 1;
				if (menu->windows[i].level == menu->windows[menu->current_win].buttons[menu->current_but - 1].win_link)
					menu->windows[i].show = 0;
			}
		}
		break;
	}
	case up:
	{
		if (menu->current_but > 0)
		{
			menu->current_but--;
			for (int i = 0; i < menu->win_count; i++)
			{
				if (menu->windows[i].level == menu->windows[menu->current_win].buttons[menu->current_but].win_link)
					menu->windows[i].show = 1;
				if (menu->windows[i].level == menu->windows[menu->current_win].buttons[menu->current_but + 1].win_link)
					menu->windows[i].show = 0;
			}
		}
		break;
	}
	case right:
	{
		if ((menu->windows[menu->current_win].buttons[menu->current_but].win_link != 0) && (menu->current_win < menu->win_count - 1))
		{
			menu->current_win++;
			menu->current_but = 0;
		}
		break;
	}
	case left:
	{
		if (menu->current_win > 0)
		{
			for (int i = 0; i < menu->windows[menu->current_win - 1].but_count; i++)
				if (menu->windows[menu->current_win].level == menu->windows[menu->current_win - 1].buttons[i].win_link)
					menu->current_but = i;
			menu->current_win--;
			if (menu->current_win < menu->win_count - 1)
				menu->windows[menu->current_win + 2].show = 0;
		}
		break;
	}
	case def:
		break;
	}
}
