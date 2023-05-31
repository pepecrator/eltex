#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 5555
#define SERVER_NAME "127.0.0.1"
#define BUFLEN 1024

int writetoserver(int fd)
{
    int nBytes;
    char buf[BUFLEN];

    fprintf(stdout, "send to server > ");
    if(fgets(buf,BUFLEN,stdin)==0)
    {
        printf("error\n");
    }
    buf[strlen(buf)-1]=0;

    nBytes = write(fd,buf,strlen(buf)+1);
    if(nBytes<0){perror("write error");return -1;}
    if(strstr(buf,"stop")) return -1;
}
int readfromserver(int fd)
{
    int nBytes;
    char buf[BUFLEN];

    nBytes = read(fd,buf,BUFLEN);
    if(nBytes<0)
    {
        perror("read error");
        return -1;
    }
    else if(nBytes = 0)
    {
        fprintf(stderr,"Client: no msg!\n");
    }
    else
    {
        fprintf(stdout,"Server's replay: %s\n",buf);
    }
    return 0;
}

int main()
{
    int err;
    int sock;
    struct sockaddr_in serv_addr;
    struct hostent *hostinfo;

    hostinfo = gethostbyname(SERVER_NAME);
    if(hostinfo == NULL)
    {
        fprintf(stderr,"unknown host %s. \n",SERVER_NAME);
        exit(EXIT_FAILURE);
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0)
    {
        perror("sock err");
        exit(EXIT_FAILURE);
    }
    err = connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(err<0)
    {
        perror("connect err");
        exit(EXIT_FAILURE);

    }
    fprintf(stdout,"Connection is ready\n");

    while(1)
    {
        if(writetoserver(sock)<0) break;
        if(readfromserver(sock)<0) break;
    }
    fprintf(stdout,"the end\n");
    close(sock);
    exit(EXIT_SUCCESS);

    return 0;
}