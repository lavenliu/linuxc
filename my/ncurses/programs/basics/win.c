#include <stdio.h>
#include <ncurses.h>

void main()
{
  initscr();
  printw("ROW is: %d\nCOL is: %d\n", LINES, COLS);
  getch();
  endwin();
}
