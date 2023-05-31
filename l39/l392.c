#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include "mq.h"

#define THREAD_POOL_SIZE 50


char client_message[2000];
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread_pool[THREAD_POOL_SIZE];
void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
  recv(newSocket , client_message , 2000 , 0);

  // Отправляем сообщение на сокет клиента
  pthread_mutex_lock(&lock);
  char *message = malloc(sizeof(client_message)+20);
  strcpy(message,"Hello Client : ");
  strcat(message,client_message);
  strcat(message,"\n");
  strcpy(buffer,message);
  free(message);
  pthread_mutex_unlock(&lock);
  sleep(1);
  send(newSocket,buffer,13,0);
  printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}
void *thread_func(void*arg)
{
    while(1)
    {
        int *pclient;
        pthread_mutex_lock(&lock);
        pclient = dequeue();
        pthread_mutex_unlock(&lock);
        if (pclient != NULL)
        {
            
            socketThread(pclient);
           
        }
        else {free(pclient);}
    }
}

int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

    for(int i = 0; i<THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i],NULL,thread_func,NULL);
    }

  //Создание сокета 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);

   // конфигурируем настройки для server address struct
  serverAddr.sin_family = AF_INET;

  //Задаем порт
  serverAddr.sin_port = htons(7799);

  //Задаем IP
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  //Биндим сокет
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  //Слушаем
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");
    while(1)
    {
        
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);


        int *pclient = malloc(sizeof(int));
        *pclient = newSocket;
        pthread_mutex_lock(&lock);
        enqueue(pclient);
        pthread_mutex_unlock(&lock);

    }
  return 0;
}
