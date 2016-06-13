#include <stdio.h>
#include "ncurses.h"

void main()
{
	char ch;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	ch = getch();
	addch(ch | A_BOLD | A_UNDERLINE);
	getch();
	endwin();
}
