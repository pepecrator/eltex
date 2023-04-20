#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dlfcn.h>
#include <string.h>
#include "bb.h"
int a,b,c,gg;

void dlll(char* argv,char*bb,int a, int b)
{
    void* vn_l;
    int (*func)(int a, int b);
    vn_l = dlopen(argv,RTLD_LAZY);
        if(!vn_l)
        {
            fprintf(stderr,"dlopen() err: %s\n", dlerror());
            return 0;
        }
        func = dlsym(vn_l, bb);
        printf("%d %s %d = %d\n",a,bb,b,(*func)(a,b)); 
        dlclose(vn_l);  
}

int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    printf("Введите первое число\n");
    scanf("%d",&a);
    printf("Введите второе число\n");
    scanf("%d",&b);
    while(1)
    {
        printf ("\033[0d\033[2J");
        printf("Выбирите операцию:\n");
        
          for(int i = 0; i<argc; i++)
            {
                if(!strcmp(argv[i],"./plus.so"))
                {
                    printf("1. СЛОЖЕНИЕ\n");
                }
            }
                
     for(int i = 1; i<argc; i++)
            {
                if(!strcmp(argv[i],"./minus.so"))
                {
                    printf("2. Вычитание\n");
                }
            }
                 
       for(int i = 1; i<argc; i++)
            {
                
                if(!strcmp(argv[i],"./del.so"))
                {
                    printf("3. Деление\n");
                }
            }
                
      for(int i = 1; i<argc; i++)
            {
                if(!strcmp(argv[i],"./mul.so"))
                {
                    printf("4. Умножение\n");
                }
            }
        printf("5. Сменить числа\n");
        printf("6. Выход\n");
        c = getchar();
        switch(c)
        {
            case '1':
            {
                for(int i = 0; i<argc; i++)
            {
                if(!strcmp(argv[i],"./plus.so"))
                {
                    dlll(argv[i],"plus",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '2':
            {
            for(int i = 0; i<argc; i++)
            {
                if(!strcmp(argv[i],"./minus.so"))
                {
                    dlll(argv[i],"minus",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '3':
            {
            for(int i = 0; i<argc; i++)
            {
                if(!strcmp(argv[i],"./del.so"))
                {
                    dlll(argv[i],"del",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '4':
            {
            for(int i = 0; i<argc; i++)
            {
                if(!strcmp(argv[i],"./mul.so"))
                {
                    dlll(argv[i],"mul",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '5':
            {
            printf("Введите первое число\n");
            scanf("%d",&a);
            printf("Введите второе число\n");
            scanf("%d",&b);
            getc(stdin);
            break;
            }
            case '6':
            {exit(EXIT_SUCCESS);}
            
        }
        getc(stdin);
    }
}