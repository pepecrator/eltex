#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <signal.h>
#include "bb.h"

 #define CTRL(c) ((c) & 037)
#define top 1

int termx, termy, centery, centerx,ty,tx;
 int row, col;
 
         int c;
         int line = 0;
WINDOW *start_wind;
//запускаем терминал
void terminal_start()
{
    initscr();
   
    cbreak();
    noecho();
    idlok (stdscr, TRUE);
    keypad (stdscr, TRUE);
    refresh();
}

// Очистка терминала
void terminal_stop()
{
    endwin();
}
//получаем нужные размеры экрана
void get_window_dimensions()
{
    getmaxyx(stdscr, termy, termx); // получение размеров окна
    centery = termy / 2;
    centerx = termx / 2;
    start_wind = newwin(termy-3,termx-3,1,3);
    getmaxyx(start_wind, ty, tx);
}
//проверка на возможность отрисовки цветов
void hascolors()
{
    if(has_colors() == false)
    {
        endwin();
        printf("your terminal does not support colors!");
        exit(1);
    }
}
//включаем цвета
void enablecolors()
{
    start_color();
    init_pair(top,COLOR_BLACK, COLOR_WHITE);
}
//отрисовываем текстовый редактор
void start_win()
{
    refresh();
   wbkgd(stdscr,COLOR_PAIR(top));
   wbkgd(start_wind,COLOR_PAIR(top));
    mvprintw(0,centerx-5,"text editor");
   
    for (int i = 1; i <= termy - 3; i++)
    {
        mvprintw(i, 0, "%d", i);
    }
    mvprintw(termy-1,1,"w:save");
    mvprintw(termy-1,9,"q:quit");
    mvprintw(termy-1,16,"i:enter mode");
    mvprintw(termy-2,1,"x:del ch");
    mvprintw(termy-2,10,"d:del ln");
    mvprintw(termy-2,20,"CTRL+D:exit mode");
}

  int row, col;
       int len (int lineno)
       {
         int linelen = tx - 2;
 
         while (linelen >= 0 && mvwinch (start_wind,lineno, linelen) == ' ')
           linelen--;
         return linelen + 1;
       }
  /* Режим ввода: принимает и вставляет символы
          Выход: CTRL+D*/
      int input ()
       {
         int c;
 
         standout ();
         mvaddstr (LINES - 1, COLS - 25, "enter mode, F1 to back");
         standend ();
         wmove (start_wind,row, col);
          refresh();
         wrefresh(start_wind);
           for (;;) {
             c = getch ();
             if (c == KEY_F(1) || c == KEY_EIC){refresh(); wrefresh(start_wind); break;}
             winsch (start_wind,c);
             wmove (start_wind,row, ++col);
              
         wrefresh(start_wind);
           }
           move (LINES - 1, COLS - 25);
           clrtoeol ();
           wmove (start_wind,row, col);
            refresh();
         wrefresh(start_wind);
       }
    /* управление текстовым редактором */
      
 
       void edit ()
       {
             int c;
 
         for (;;) {
           wmove (start_wind,row, col);
           
           wrefresh (start_wind);
           c = getch ();
 
           /* Команды редактора */
           switch (c) {
 
             /* стрелки: перемещают курсор
                в указанном направлении */
            
             case KEY_LEFT:
               if (col > 0) col--;
               else flash ();
               break;
             case KEY_DOWN:
               if (row < ty - 1) row++;
               else flash ();
               break;
             case KEY_UP:
               if (row > 0) row--;
               else flash ();
               break;
 
             
             case KEY_RIGHT:
               if (col < tx - 1) col++;
               else flash ();
               break;
 
             /* i: переход в режим ввода */
             case KEY_IC:
             case 'i':
               input ();
               break;
 
             /* x: удалить текущий символ */
             case KEY_DC:
             case 'x':
               wdelch (start_wind);
               wrefresh(start_wind);
               break;
 
             /* o: вставить строку и перейти в режим ввода */
             case KEY_IL:
             case 'o':
               wmove (start_wind,++row, col = 0);
               winsdelln (start_wind,1);
               input ();
               break;
 
             /* d: удалить текущую строку */
             case KEY_DL:
             case 'd':
               winsdelln (start_wind,-1);
               wrefresh(start_wind);
               break;
 
             /* CTRL+L: перерисовать экран */
             case KEY_CLEAR:
             case CTRL('L'):
               wrefresh (curscr);
               wrefresh(start_wind);
               break;
 
             /* w: записать и закончить работу */
             case 'w':
               return;
 
             /* q: закончить работу без записи файла */
             case 'q':
               endwin ();
               exit (2);
 
             default:
               flash ();
               break;
           }
         }
       }

       void read1(FILE*fd)
       {
  
        // Читаем файл 
         while ((c = getc(fd)) != EOF) {
            
           if (c == '\n') line++;
         
           if (line > ty - 2)  break;
           waddch(start_wind,c);
         }
         refresh();
         wrefresh(start_wind);
       }
       //функция записи в файл
       void write1(FILE*fd)
       {
        int i, n, l;
        for (l = 0; l < ty - 1; l++) {
           n = len(l);
           for (i = 0; i < n; i++)
             putc (mvwinch (start_wind,l, i) & A_CHARTEXT, fd);
           putc('\n', fd);
         }
       }


 