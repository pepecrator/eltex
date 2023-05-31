#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/ip.h>	//Provides declarations for ip header

//checksum = 0;

int main() {
	const char* server_name = "127.0.0.1";
	const int server_port = 8877;
    char datagram[1024], source_ip[32] , *data;
    struct iphdr *iph = (struct iphdr *) datagram;
	
	//UDP header
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct iphdr));
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
    memset (datagram, 0, 1024);

   
int sock;
	if ((sock = socket(PF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
		printf("could not create socket\n");
		return 1;
	} 
	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	// htons: port in network order format
   // server_address.sin_family = AF_INET;
  data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
  strcpy(data , "hello!!!!!!!!!");	
    strcpy(source_ip , "198.168.0.41");
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8877);
	server_address.sin_addr.s_addr = inet_addr ("192.168.0.34");
  //Set port number, using htons function to use proper byte order 
  //Fill in the IP Header
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
	iph->id = htonl (0);	//Id of this packet
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_UDP;
	iph->check = 0;		//Set to 0 before calculating checksum
	iph->saddr = inet_addr ( source_ip );	//Spoof the source ip address
	iph->daddr = server_address.sin_addr.s_addr;
  //Set IP address to localhost 
	// open socket
	
    udph->source = htons (6666);
	udph->dest = htons (server_port);
	udph->len = htons(sizeof (struct udphdr) + strlen(data));	
	udph->check = 0;
    int tmp = 1;
    const int *val = &tmp;
     if(setsockopt(sock,IPPROTO_IP, IP_HDRINCL, val, sizeof(tmp)) < 0) {
      perror("setsockopt");
      return -1;
    }
    else
      printf("Using your own header\n");
	// send data
	int len =
	    sendto(sock, datagram, iph->tot_len, 0,
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
    recv_string_data = (char *) (recvbuffer + sizeof (struct iphdr) + sizeof (struct udphdr));
   // printf("%ld\n",strlen(buffer));
	printf("recieved: '%s'\n", recv_string_data);
    }
	// close the socket
	close(sock);
	return 0;
}
