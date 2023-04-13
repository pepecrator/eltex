#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main()
{
    char b;
    
        while(1)
        {
            printf("Выберите:\n");
        printf("1. Вывести список абонентов\n");
        printf("2. Добавить абонента\n");
        printf("3. Найти абонентв\n");
        printf("4. Удалить абонента\n");
        printf("5. Выход\n");
        scanf("%c",&b);
            switch(b)
            {
                case '1':
                    printf("1");
                    getc(stdin);
                    break;
                case '2':
                    printf("2");
                    break;
                    
            }
            getc(stdin);
        }
    return 0;
}