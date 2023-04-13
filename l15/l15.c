//#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
//#include <unistd.h>

int main()
{
    setlocale(LC_ALL, "");
    struct sprav
    {
        char phone[11];
        char name[15];

    };
    typedef struct sprav sprav;
    sprav a[10];
    char b;
    int index = 0;
    FILE *fp;
    while(1)
    {
        printf ("\033[0d\033[2J");
        printf("Выберите:\n");
        printf("1. Вывести список абонентов\n");
        printf("2. Добавить абонента\n");
        printf("3. Найти абонентв\n");
        printf("4. Удалить абонента\n");
        printf("5. Выход\n");
        b = getchar();
        switch(b)
        {
            case '1':
                for(int i = 0; i<index; i++)
                {
                    printf(" %d. Name: %s  Phone: %s\n", i, a[i].name, a[i].phone);
                }
                getc(stdin);
                break;
            case '2':
                printf("Введите имя абонента");
                scanf("%s",a[index].name);
                
                printf("Введите телефон абонента");
                scanf("%s",a[index].phone);
               
                index++;
                
                break;
            case '3':
            {
                char n[15];
                int h;
                char* tmp1;
                char* tmp2;
                printf("Введите имя абонента:\n");
                scanf("%s",n);
                tmp2 = &n;
                for(int i = 0; i<=10; i++)
                {
                    tmp1 = &a[i].name;
                    if(*tmp1 == *tmp2)
                        {
                            printf("%d. Name:%s  Phone:%s", i, a[i].name, a[i].phone);
                             getc(stdin);
                            break;
                        }
                    
                }
                getc(stdin);
               
            }
             break;
            case '4':
            {
                char n[15];
                int h;
                char* tmp1;
                char* tmp2;
                printf("Введите имя абонента, которого вы хотите удалить:\n");
                scanf("%s",n);
                tmp2 = &n;
                for(int i = 0; i<=10; i++)
                {
                    tmp1 = &a[i].name;
                    if(*tmp1 == *tmp2)
                        {
                           strcpy(a[i].name,"");
                           strcpy(a[i].phone,"");
                           for(int j =i;j<=index;j++)
                           {
                           strcpy(a[j].name,a[j+1].name);
                           strcpy(a[j].phone,a[j+1].phone);
                            strcpy(a[j+1].name,"");
                           strcpy(a[j+1].phone,"");
                           }
                           index--;
                            printf("абонент удален"); 
                            getc(stdin);
                            break;
                        }
                    
                    
                }
               getc(stdin);
            }
             break;
             case '5':
             {
                exit(1);
             }
             break;
            
        }
    getc(stdin);
    }
    return 0;
}