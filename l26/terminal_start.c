#include <ncurses.h>

void terminal_start()
{
	initscr();
	curs_set(0);
	cbreak();
	echo();
	keypad(stdscr, TRUE);
	refresh();
}
