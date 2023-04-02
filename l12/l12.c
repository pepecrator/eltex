#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>


void zd1()
{
     int n,k = 0;
    printf("enter size of the square matrix");
    scanf("%d",&n);
    int c[n][n];
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            c[i][j] = k;
            k++;
        }
    }
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            printf(" %d ", c[i][j]);
        }
        printf("\n");
    }
}
void zd2()
{
    int n;
    printf("enter size of the square matrix");
    scanf("%d",&n);
    int c[n+1];
    for(int i = 1; i<n+1;i++)
    {
        c[i] = i;
    }
    for(int i = 1; i<n+1; i++)
    {
        printf(" %d ",c[(n+1)-i]);
    }
}
int zd3()
{
    int n,k = 0;
    printf("enter size of the square matrix");
    scanf("%d",&n);
    int c[n][n];
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            if(i<j) c[i][j] = 1;
            else if(i>j) c[i][j] = 0;
            else c[i][j] = 1;
        }
    }
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            printf(" %d ", c[i][j]);
        }
        printf("\n");
    }
}
void zd4()
{
    int n;
    printf("enter size of the square matrix");
    scanf("%d",&n);
    int c[n][n];
    int ib = 0, ifi = 0, jb = 0, jf = 0;//размерность 
    int k = 1;//счетчик
    int i = 0;//строки
    int j = 0;//столбцы

    while (k <= n*n){
        c[i][j] = k;
        if (i == ib && j < n - jf - 1) j++;
        else if (j == n - jf - 1 && i < n - ifi - 1) i++;
        else if (i == n - ifi - 1 && j > jb) j--;
        else i--;

        if ((i == ib + 1) && (j == jb) && (jb != n - jf - 1)){
            ib++;
            ifi++;
            jb++;
            jf++;
        }
        ++k;
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            printf("%d", c[i][j]);
        printf("\n");
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int n;
   
    while(1)
    {
        printf ("\033[0d\033[2J");
        printf("Выберите задание:\n");
        printf("1. Вывести квадратную матрицу размерности N\n");
        printf("2. Вывести заданный массив размером N в обратном порядке\n");
        printf("3. Заполнить верхний треугольник матрицы 1, нижний 0\n");
        printf("4. Заполнить матрицу улиткой\n");
        printf("5. Выход\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
            {
                zd1();
                getchar();
                break;
            }
            case 2:
            {
                zd2();
                getchar();
                break;
            }
            case 3:
            {
                zd3();
                getchar();
                break;
            }
            case 4:
            {
                zd4();
                getchar();
                break;

            }
            case 5:
            {
                exit(1);
            }
        }
    }
    return 0;
}