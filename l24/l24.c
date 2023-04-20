#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "bb.h"
int a,b,c,gg;
int main()
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
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Деление\n");
        printf("4. Умножение\n");
        printf("5. Сменить числа\n");
        printf("6. Выход\n");
        c = getchar();
        switch(c)
        {
            case '1':
            {
            gg = plus(a,b);
            printf("Ответ: %d\n",gg);
            getc(stdin);
            break;
            }
            case '2':
            {
            gg = minus(a,b);
            printf("Ответ: %d\n",gg);
            getc(stdin);
            break;
            }
            case '3':
            {
            gg = del(a,b);
            printf("Ответ: %d\n",gg);
            getc(stdin);
            break;
            }
            case '4':
            {
            gg = mul(a,b);
            printf("Ответ: %d\n",gg);
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