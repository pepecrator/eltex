#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h>
#include <pthread.h>
#define PORT 5000
#define MAXLINE 1024
char client_message[2000];
char b[MAXLINE];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int max(int x, int y)
{
    if(x>y) return x;
    else return y;
}

int main()
{
    int listenfd, connfd, udpfd, nready, maxfdp1;
    char b[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on =1;
    struct sockaddr_in cliaddr, servaddr;
    char* message = "Hello client";
    void sig_chld(int);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(listen(listenfd,50)==0)
    printf("Listening\n");

    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(udpfd, (struct sockaddr*)&servaddr,sizeof(servaddr));

    FD_ZERO(&rset);

    maxfdp1 = max(listenfd, udpfd) + 1;
    pthread_t tid[60];
    int i = 0;
    while(1)
    {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        nready = select(maxfdp1, &rset, NULL,NULL,NULL);

        if (FD_ISSET(listenfd, &rset)) {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
            if ((childpid = fork()) == 0) {
                close(listenfd);
                bzero(b, sizeof(b));
                printf("Message From TCP client: ");
                read(connfd, b, sizeof(b));
                puts(b);
                write(connfd, (const char*)message, sizeof(b));
                close(connfd);
                exit(0);
            }
            close(connfd);
        }
        if (FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr);
            bzero(b, sizeof(b));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udpfd, b, sizeof(b), 0,
                        (struct sockaddr*)&cliaddr, &len);
            puts(b);
            sendto(udpfd, (const char*)message, sizeof(b), 0,
                (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        }
    }

    return 0;
}