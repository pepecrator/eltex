#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <signal.h>
#include "bb.h"


#define top 1

int termx, termy, centery, centerx,ty,tx,ry,rx;
 int row, col;
 
WINDOW *win1,*win2;
struct path
{
    char* pth;
    char* ppth;
    char* npth;
};
typedef struct path path;
path p;
struct dirent **namelist;
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
char* concat(char *s1, char *s2) 
{

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);                      

    char *result = malloc(len1 + len2 + 1);

    if (!result) 
    {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);    

    return result;
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
    win1 = newwin(termy-2,centerx-2,1,1);
    win2 = newwin(termy-2,centerx-2,1,centerx + 1);
    getmaxyx(win1, ty, tx);
    getmaxyx(win2,ry,rx);
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
void wr(WINDOW* win,int n)
{
    int j = 0;
    for(int i = 0; i<n;i++)
        {
            if(i<ty)
            {
                mvwprintw(win,i,2,"%s\n",namelist[i]->d_name);
            }
            else if(i>=ty)
            {
                mvwprintw(win2,j,2,"%s\n",namelist[i]->d_name);
                j++;
            }
        
        }
}
void keybo(WINDOW* win,int n)
{
    int choise;
        int h=0;
        int g = 0;
        int j = 0;
        int k = 0;
        int i = 0;
        keypad (win, TRUE);
        keypad (win2, TRUE);
         while(1)
         {
            //int i =0;
            if(h<ty)
                {
                    for(i = 0; i<n;i++)
                    {
                        g=-1;
                                if(i == h)
                                    wattron(win,A_REVERSE);
                                mvwprintw(win,i,2,"%s",namelist[i]->d_name);
                                wattroff(win,A_REVERSE);
                    }
                }
            else if(h>=ty)
                {
                    //g=0;
                    for(int j = 0; j<n;j++)
                    {
                        if(j == g)
                            {wattron(win2,A_REVERSE);
                        mvwprintw(win2,j,2,"%s",namelist[h]->d_name);
                        //wattroff(win2,A_REVERSE);
                            }
                            wattroff(win2,A_REVERSE);
                    }
                }
                mvprintw(termy-1,9,"%d",g);
                if(h<ty)
                {
                    choise = wgetch(win);
                }
                else if(h>=ty)
                {
                   //if(h=ty){ g=0;};
                    choise = wgetch(win2);
                }
                switch(choise)
                {
                    case KEY_UP:
                        h--;
                        if(h>=ty) {g--;}
                        if(h == -1) h = 0;
                        break;
                    case KEY_DOWN:
                        h++;
                        if(h>=ty) {g++;}
                        if(h==n+1) h=n-1;
                        break;
                    default:
                        break;
                }
            if(choise == 10)
                break;
            if(choise == KEY_F(1))
            {
                terminal_stop();
                exit(EXIT_SUCCESS);
            }
         }
        p.ppth = p.pth;
        if(namelist[h]->d_name == "..")
        {
            p.pth = p.ppth;
        }
        else{
            p.pth = concat(p.pth,"/");
            p.pth = concat(p.pth,namelist[h]->d_name);
        }
}
void prav(WINDOW * win)
    {
        while(1)
        {
        int n;
        n = scandir(p.pth, &namelist, 0, alphasort);
        int choise;
        int h=0;
        wr(win,n);
        refresh();
        wrefresh(win);
        wrefresh(win2);
        keybo(win,n);
        wclear(win);
        wclear(win2);
        refresh();
        wrefresh(win);
        wrefresh(win2);
        
        }
        
    }
   
//отрисовываем текстовый редактор
void start_win()
{
    p.pth = "/home";
   wbkgd(stdscr,COLOR_PAIR(top));
   wbkgd(win1,COLOR_PAIR(top));
   wbkgd(win2,COLOR_PAIR(top));
    mvprintw(0,centerx-5,"file manager");
    mvprintw(termy-1,1,"F1:quit");

    prav(win1);
    //lev(win2);
    
    refresh();
    wrefresh(win1);
    wrefresh(win2);
    
   /*
    mvprintw(termy-1,1,"w:save");
    mvprintw(termy-1,9,"q:quit");
    mvprintw(termy-1,16,"i:enter mode");
    mvprintw(termy-2,1,"x:del ch");
    mvprintw(termy-2,10,"d:del ln");
    mvprintw(termy-2,20,"CTRL+D:exit mode");*/
    }
   

