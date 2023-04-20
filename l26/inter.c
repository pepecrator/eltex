#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <signal.h>

int termx, termy,centery,centerx;
WINDOW  * start_wind;
void terminal_start()
{
    initscr();
	curs_set(0);
	cbreak();
	echo();
	keypad(stdscr, TRUE);
	refresh();
}

// Очистка терминала
void terminal_stop() {
	endwin();
}

void get_window_dimensions() {

	getmaxyx(stdscr, termy, termx);//получение размеров окна
    centery = termy/2;
    centerx = termx/2;
    start_wind = newwin(termy-2,termx,1,0);//задание размеров для окна в стартовом фрейме
}

void start_win()
{
    box(start_wind,0,0);
    for(int i = 0; i<= termy-2; i++)
    {
        mvwprintw(start_wind,i,0,"%d",i);
    }
    
}




