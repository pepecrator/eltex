#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <signal.h>
#include "bb.h"

int main(int argc, char* argv[])
{
    terminal_start();
    get_window_dimensions();
    start_win();
    terminal_stop();
    getc(stdin);

    return 0;
}