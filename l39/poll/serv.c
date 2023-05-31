#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/poll.h>

#define PORT 5555
#define BUFLEN 1024
//Функция получения данных от клиента
int readfromcli(int fd,char *buf)
{
    int nBytes;

    nBytes = read(fd,buf, BUFLEN);
    if(nBytes<0)
    {
        perror("read error");
        return -1;
    }
    else if(nBytes = 0)
    {
       return -1;
    }
    else
    {
        fprintf(stdout,"Server got message: %s\n",buf);
        return 0;
    }
}
//Функция отправки данных клиенту
int writetocli(int fd,char *buf)
{
    int nBytes;
    unsigned char *s;

    for(s = (unsigned char *)buf; *s;s++)
    {
        *s = toupper(*s);
    }
    nBytes = write(fd,buf,strlen(buf)+1);
    fprintf(stdout,"Writeback: %s\nnbytes = %d\n",buf,nBytes);
    if(nBytes<0)
    {
        perror("write err");
    }
}

int main()
{
    int i, err, opt=1;
    int sock, new_sock;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    char buf[BUFLEN];
    socklen_t size;
    //Создаем сокет
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0)
    {
        perror("sock err");
        exit(EXIT_FAILURE);
    }
    //Задаем опции для сокета
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&opt,sizeof(opt));

    //Заполнием структуру	
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // биндимся
    err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(err < 0)
    {
        perror("bind err");
        exit(EXIT_FAILURE);
    }
    // Слушаем новые подключения
    err = listen(sock,50);
    if(err<0)
    {
        perror("listen err");
        exit(EXIT_FAILURE);

    }
    	
    struct pollfd act_set[100];//Создаем структуру для poll 
    act_set[0].fd = sock;//Задаем дескриптор сокета
    act_set[0].events = POLLIN;// Задаем событие возможности считывания данных
    act_set[0].revents = 0;//Возвращаемое событие
    int num_set = 1;

    while(1)
    {
        int ret = poll(act_set,num_set,-1);
        if(ret<0)
        {
            perror("poll err");
            exit(EXIT_FAILURE);
        }
        if(ret>0)
        {
            for(i = 0; i<num_set;i++)
            {
                if(act_set[i].revents & POLLIN)
                {
                    printf("get POLLIN at fd %d\n",act_set[i].fd);
                    act_set[i].revents &= -POLLIN;
                    if(i==0)
                    {
                        size = sizeof(client);
                        new_sock = accept(act_set[i].fd,(struct sockaddr*)&client,&size);
                        printf("new client at port %u\n", ntohs(client.sin_port));
                        if(num_set < 100)
                        {
                            act_set[num_set].fd = new_sock;
                            act_set[num_set].events = POLLIN;
                            act_set[num_set].revents = 0;
                            num_set++;
                        }
                        else {
                            printf("no more sockets for clients");
                            close(new_sock);
                        }
                    } else{
                        err = readfromcli(act_set[i].fd, buf);
                        printf("%d [%s] %p\n",err,buf,strstr(buf,"stop"));
                        if(err<0 || strstr(buf, "stop"))
                        {
                            printf("get stop\n");
                            close(act_set[i].fd);

                            if(i<num_set-1)
                            {
                                act_set[i] = act_set[num_set-1];
                                num_set--;
                                i--;
                            }
                        }else{
                            writetocli(act_set[i].fd,buf);
                        }
                    }
                }

            }
        }
    }

    return 0;
}
