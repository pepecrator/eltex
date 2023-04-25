#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <signal.h>
#include "bb.h"


int main(int argc, char** argv)
{
         FILE *fd;
    if (argc != 2) {
           fprintf (stderr, "usage: %s file\n", argv [0]);
           exit (1);
         }
 terminal_start();
    hascolors();
    enablecolors();
    get_window_dimensions();
    start_win(); 
         fd = fopen (argv [1], "r");
         if (fd == NULL) {
           perror (argv [1]);
           exit (2);
         }
         /* Читаем файл */
         read1(fd);
         fclose (fd);
    
         
         edit ();
          /* Записываем файл */
         fd = fopen (argv [1], "w");
         write1(fd);
         fclose(fd);

    terminal_stop();
    return 0;
}