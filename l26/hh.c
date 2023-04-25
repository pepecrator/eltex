#include <stdio.h>                                                          
#include <stdlib.h>                                                         
                                                                            
int main()                                                                  
{                                                                           
    long int m = 6099;                                                      
    long int n = 2166;                                                      
    long int r;                                                             
    while(1)                                                                
    {                                                                       
        r = m%r;                                                            
        if(r == 0)                                                          
        {printf("%ld",n);                                                   
         exit(EXIT_SUCCESS);}                                               
        else                                                                
        {m = n;                                                             
         n = r;}                                                            
    }                                                                       
}                                                                           
                                                                            
