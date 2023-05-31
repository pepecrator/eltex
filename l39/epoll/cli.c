#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 5555
#define SIZE 1024

int main(int argc, char *argv[])
{
   

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int server_socket = connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)); //连接服务器

    printf("Connect result ==> %d\n", server_socket);
    if (server_socket < 0) {
        perror("Connect result");
        exit(1);
    }

    char buf[SIZE] = {0};

    while (1)
    {
        printf("Send to server：");
        scanf("%s", buf);
        write(client_socket, buf, strlen(buf));
        printf("\n");
        if (strncmp(buf, "end", 3) == 0)
        {
            break;
        }
    }
    close(server_socket);

    return 0;
}






