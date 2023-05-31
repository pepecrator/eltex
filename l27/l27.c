#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <signal.h>
#include "bb.h"


int main(int argc, char** argv)
{
    terminal_start();
    hascolors();
    enablecolors();
    get_window_dimensions();
    start_win(); 
    getch();
    terminal_stop();
    return 0;
}