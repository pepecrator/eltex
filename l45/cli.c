#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include <netinet/ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define MAC_ADDR_LEN 6

typedef unsigned char MacAddress[MAC_ADDR_LEN];
//checksum = 0;
unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for(sum=0; nwords>0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}
int main() {
	const char* server_name = "192.168.0.34";
	const int server_port = 8877;
    char datagram[1024], source_ip[32] , *data, *pseudogram;
    struct ethhdr *eth = (struct ethhdr *) datagram;
    //struct ether_header *eh = (struct ether_header *) datagram;
    struct iphdr *iph = (struct iphdr *) (datagram+ sizeof (struct ethhdr));
	
	//UDP header
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct iphdr) + sizeof(struct ethhdr));
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
    memset (datagram, 0, 1024);
    
   
int sock;
	if ((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		printf("could not create socket\n");
		return 1;
	} 
	inet_pton(AF_INET, server_name, &server_address.sin_addr);
    unsigned char localmac[6] = {0x98, 0x48, 0x27, 0x39, 0x1c, 0x74};
    unsigned char destmac[6] = {0xb0,0x10,0x41,0xf6,0x4c,0xbb};
	// htons: port in network order format
   // server_address.sin_family = AF_INET;
  data = datagram + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
  strcpy(data , "hello!!!!!!!!!");	
    strcpy(source_ip , "192.168.0.41");
	int tx_len = 0;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8877);
	server_address.sin_addr.s_addr = inet_addr (server_name);

    eth->h_source[0] = localmac[0];
    eth->h_source[1] = localmac[1];
    eth->h_source[2] = localmac[2];
    eth->h_source[3] = localmac[3];
    eth->h_source[4] = localmac[4];
    eth->h_source[5] = localmac[5];
    eth->h_dest[0] = destmac[0];
    eth->h_dest[1] = destmac[1];
    eth->h_dest[2] = destmac[2];
    eth->h_dest[3] = destmac[3];
    eth->h_dest[4] = destmac[4];
    eth->h_dest[5] = destmac[5];
    eth->h_proto = htons(ETH_P_IP);
    tx_len += sizeof(struct ethhdr);
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
    tx_len += sizeof(struct iphdr);
  //Set IP address to localhost 
	// open socket
    udph->source = htons (6666);
	udph->dest = htons (server_port);
	udph->len = htons(sizeof (struct udphdr) + strlen(data));	
	udph->check = 0;
    tx_len += sizeof(struct udphdr);
     tx_len += strlen(data);
    /* Length of UDP payload and header */
    udph->len = htons(tx_len - sizeof(struct ethhdr) - sizeof(struct iphdr));
    /* Length of IP payload and header */
    iph->tot_len = htons(tx_len - sizeof(struct ethhdr));
    /* Calculate IP checksum on completed header */
    iph->check = csum((unsigned short *)(datagram+sizeof(struct ethhdr)), sizeof(struct iphdr)/2);
    struct ifreq if_idx;
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, "wlx984827391c74", IFNAMSIZ-1);
    if (ioctl(sock, SIOCGIFINDEX, &if_idx) < 0)
    perror("SIOCGIFINDEX");
    struct sockaddr_ll socket_address;
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    socket_address.sll_halen = ETH_ALEN;
    socket_address.sll_addr[0] = eth->h_dest[0];
	socket_address.sll_addr[1] = eth->h_dest[1];
	socket_address.sll_addr[2] = eth->h_dest[2];
	socket_address.sll_addr[3] = eth->h_dest[3];
	socket_address.sll_addr[4] = eth->h_dest[4];
	socket_address.sll_addr[5] = eth->h_dest[5];
    //tx_len += strlen(data);


	int len =
	    sendto(sock, datagram, tx_len, 0,
	           (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll));
   // printf("%ld",strlen(datagram));
	// received echoed data back
    //while(1)
   // {
	char buffer[1024];
    unsigned char recvbuffer[1024] = {0};
    char *recv_string_data = NULL;
    //while(1)
    //{
    //buffer[0]='\0';
	len = recvfrom(sock, recvbuffer, 1024, 0, NULL, NULL);
    if(len>0)
    {
        printf("%d",len);
    }
    recv_string_data = (char *) (recvbuffer + sizeof(struct ethhdr) + sizeof (struct iphdr) + sizeof (struct udphdr));
   // printf("%ld\n",strlen(buffer));
	printf("recieved: '%s'\n", recv_string_data);
    //}
	// close the socket
	close(sock);
	return 0;
}