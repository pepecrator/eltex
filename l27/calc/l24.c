#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "bb.h"
int a,b,c,gg;

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

void dlll(char* argv,char*bb,int a, int b)
{
    void* vn_l;
    int (*func)(int a, int b);
    char* path = concat("./dll/",argv);
    vn_l = dlopen(path,RTLD_LAZY);
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
    struct dirent **entry;
    int n;
    n = scandir("/home/fedor/eltex/l27/calc/dll", &entry, 0, alphasort);
    if (n<0)
    {
        perror("scandir");
        exit(1);
    }
    while(1)
    {
        printf ("\033[0d\033[2J");
        printf("Выбирите операцию:\n");
        
          for(int i = 0; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"plus.so"))
                {
                    printf("1. СЛОЖЕНИЕ\n");
                }
            }
                
     for(int i = 1; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"minus.so"))
                {
                    printf("2. Вычитание\n");
                }
            }
                 
       for(int i = 1; i<n; i++)
            {
                
                if(!strcmp(entry[i]->d_name,"del.so"))
                {
                    printf("3. Деление\n");
                }
            }
                
      for(int i = 1; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"mul.so"))
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
                for(int i = 0; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"plus.so"))
                {
                    dlll(entry[i]->d_name,"plus",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '2':
            {
            for(int i = 0; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"minus.so"))
                {
                    dlll(entry[i]->d_name,"minus",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '3':
            {
            for(int i = 0; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"del.so"))
                {
                    dlll(entry[i]->d_name,"del",a,b);
                }
            }
            getc(stdin);
            break;
            }
            case '4':
            {
            for(int i = 0; i<n; i++)
            {
                if(!strcmp(entry[i]->d_name,"mul.so"))
                {
                    dlll(entry[i]->d_name,"mul",a,b);
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