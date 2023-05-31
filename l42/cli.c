#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/udp.h>	//Provides declarations for udp header

//checksum = 0;

int main() {
	const char* server_name = "192.168.0.34";
	const int server_port = 8877;
    char datagram[1024], source_ip[32] , *data;
    struct udphdr *udph = (struct udphdr *) datagram;
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
    memset (datagram, 0, 1024);

   

	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	// htons: port in network order format
   // server_address.sin_family = AF_INET;
  data = sizeof(struct udphdr) + datagram;
	strcpy(data , "hello!!!!!!!!!");	
    
  //Set port number, using htons function to use proper byte order 
  server_address.sin_port = htons(8877);

  //Set IP address to localhost 
  server_address.sin_addr.s_addr = inet_addr("192.168.0.41");

	// open socket
	int sock;
	if ((sock = socket(PF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
		printf("could not create socket\n");
		return 1;
	} 
    udph->source = htons (6666);
	udph->dest = htons (server_port);
	udph->len = htons(sizeof(struct udphdr)+strlen(data));	
	udph->check = 0;
	// send data
	int len =
	    sendto(sock, datagram, sizeof(struct udphdr)+strlen(data), 0,
	           (struct sockaddr*)&server_address, sizeof(server_address));
   // printf("%ld",strlen(datagram));
	// received echoed data back
    //while(1)
   // {
	char buffer[1024];
    unsigned char recvbuffer[1024] = {0};
    char *recv_string_data = NULL;
    while(1)
    {
    //buffer[0]='\0';
	len = recvfrom(sock, recvbuffer, 1024, 0, NULL, NULL);
    if(len>0)
    {
        printf("%d",len);
    }
    recv_string_data = (char *) (recvbuffer + sizeof (struct udphdr));
   // printf("%ld\n",strlen(buffer));
	printf("recieved: '%s'\n", recv_string_data);
    }
	// close the socket
	close(sock);
	return 0;
}
