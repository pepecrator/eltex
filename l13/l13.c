#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
void zd1()
{
    int a = 270533154;
    char *ptr;
    printf(" a = %d\n", a);
    ptr = &a;
    printf("first byte of a = %d\n", *ptr);
    ptr++;
    printf("second byte of a = %d\n", *ptr);
    ptr++;
    printf("third byte of a = %d\n", *ptr);

    ptr = &a;
    ptr++;
    ptr++;
    ptr++;
    *ptr = 5;
    printf(" a = %d\n", *ptr);

}

void zd2()
{
    char a = 'A';
    char b = 'B';
    char *ptr1;
    char **ptr2;


    ptr1 = &a;


    ptr2 = &ptr1;
    *ptr2 = &b;
    printf("%p\n",ptr2);
    printf("%c\n",*ptr1);
    printf("%c\n",**ptr2);
    printf("%p\n",&ptr2);
}

int main()
{
    int b;
    printf ("\033[0d\033[2J");
    printf("1. zd1\n");
    printf("2. zd2\n");
    printf("3. exit\n");
    scanf("%d",&b);
  
        switch(b)
        {
            case 1:
            {
                zd1();
                //getchar();
                break;
            }
            case 2:
            {
                zd2();
                //getchar();
                break;
            }
            case 3:
            {
                exit(0);
            }
        }
   
    getchar();
    return 0;
}