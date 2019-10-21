/*
	Goals is to create a socket connection to gather data from the 
	tank - data will need to be parsed 
	
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <time.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define IP "192.168.220.122"
#define PORT 10001
#define COMMAND2  "I201"
#define TANK  "00"
#define MSG_SIZE 100

int sock;
unsigned int length;
socklen_t fromlen;
struct sockaddr_in server, send_this, receive;
struct sockaddr_in addr, from;
char buffer[MSG_SIZE];

void receive_info(); 

int main ( void ) 
{
 	int boolval = 1; 
	
	sock = socket(AF_INET, SOCK_DGRAM, 0); // Creates socket. Connectionless.
    	if (sock < 0)
        	{
            		herror("socket");
        	}
    
   	 //printf("socked made\n");
   	 length = sizeof(server); // determines lenght of the structure
    	bzero(&server, length); // set all valus = 0
    	server.sin_family = AF_INET; //constant for internet domain
    	server.sin_addr.s_addr= INADDR_ANY; // MY IP address
    	server.sin_port = htons(PORT);
    	
	printf("\nIP Addreess Config: %s", IP );
	printf("\nPort Configured: %d\n", PORT );

	// going to set broadcasting address
    
   	 if (bind(sock, (struct sockaddr *)&server, length) < 0)
        	{
            	printf("binding error dumby\n");
       		}
 
    	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &boolval, sizeof(boolval)) < 0)
        	{
            	printf("error setting socket option\n");
            	exit(-1);
        	}
	receive_info();

return 0;
}

void receive_info() 
{

	int information_error_check; 

	char buffer [MSG_SIZE];
	receive.sin_family = AF_INET;
	receive.sin_addr.s_addr = inet_addr(IP);
	receive.sin_port =htons(PORT);

	while(1)
  	{
        	bzero(buffer, MSG_SIZE);
        	information_error_check = recvfrom(sock, buffer, MSG_SIZE, 0, (struct sockaddr *)&receive, &fromlen);
	   	if( information_error_check < 0)
            	{
               		 printf("that was an error receiving infromation from the sock connection\n");
                	 exit( -1);
            	}
	printf("%s", buffer);
	}
}

