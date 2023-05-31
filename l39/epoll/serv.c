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
#include <sys/epoll.h>

#define PORT 5555
#define BUFLEN 1024

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
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0)
    {
        perror("sock err");
        exit(EXIT_FAILURE);
    }
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&opt,sizeof(opt));


    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(err < 0)
    {
        perror("bind err");
        exit(EXIT_FAILURE);
    }
    err = listen(sock,50);
    if(err<0)
    {
        perror("listen err");
        exit(EXIT_FAILURE);

    }

   struct epoll_event ev, events[50];
    int conn_sock, nfds, epollfd;
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1");
    }
    ev.events = EPOLLIN;
    ev.data.fd = sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &ev) == -1)
    {
        perror("epoll_ctl: listen_sock");
    }

    int client_sockets[50];
    for (int i = 0; i < 50; i++)
    {
        client_sockets[i] = 0;
    }

    while (1)
    {
        nfds = epoll_wait(epollfd, events, 50, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
        }

        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == sock)
            {
                struct sockaddr_in cliaddr;
                int addrlen = sizeof(cliaddr);
                conn_sock = accept(sock, (struct sockaddr *)&cliaddr, &addrlen);
                if (conn_sock == -1)
                {
                    perror("accept");
                }

                for (int i = 0; i < 50; i++)
                {
                    if (client_sockets[i] == 0)
                    {
                        client_sockets[i] = conn_sock;
                        ev.events = EPOLLIN | EPOLLET;
                        ev.data.fd = client_sockets[i];
                        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_sockets[i], &ev) == -1)
                        {
                            perror("epoll_ctl: conn_sock");
                        }
                        break;
                    }
                }
            }
            for (int i = 0; i < 50; i++)
            {
                if (client_sockets[i] > 0 && events[n].data.fd == client_sockets[i])
                {
                    char buf[BUFLEN];
                    int bufSize = read(client_sockets[i], buf, BUFLEN - 1);
                    printf("bufsize %d\n", bufSize);
                    if (bufSize == -1)
                    {
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, client_sockets[i], NULL);
                    }
                    else if (bufSize == 0)
                    {
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, client_sockets[i], NULL);
                    }
                    else
                    {

                        buf[bufSize] = '\0';
                        printf("From client: %s\n", buf);
                    }
                }
            }
        }
    }

    printf("server end\n");

    close(sock);

    return 0;
}