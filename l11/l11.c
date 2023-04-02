#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 0x00CCAABB;//задаем изначальное значение в 16 системе 
    int b = a;
    unsigned char c;
    // выводим каждый байт в цикле
    for(int i=0;i<3;i++)
    {
        c = (a & (0x000000FF)<<8*i)>>8*i;
        printf("%x\n",c);
    }
    // изменяем только 3 байт, единственное я не особо уверен, что сделал это правильно
    a = (a & 0x00AAFFFF);
    printf("%x\n",a);
    return 0;
}