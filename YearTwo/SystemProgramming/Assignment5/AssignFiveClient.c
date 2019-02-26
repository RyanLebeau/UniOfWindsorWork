/*
Ryan Lebeau
26/11/2017
System Programming
AssignFiveClient.c
*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
  
int main(int argc, char const *argv[])
{
	int value;
    struct sockaddr_in address;
    struct sockaddr_in servAddrs;
    char *input;
    char buffer[1024] = {0};
    int sock = socket(AF_INET, SOCK_STREAM, 0);
  
    memset(&servAddrs, '0', sizeof(servAddrs));
  
    servAddrs.sin_family = AF_INET;
    servAddrs.sin_port = htons(PORT);
      
    //converting ip connection to binary
	inet_pton(AF_INET, "127.0.0.1", &servAddrs.sin_addr);
	//connecting client to server
    connect(sock, (struct sockaddr *)&servAddrs, sizeof(servAddrs));
	while(1){
		printf("Enter Input: ");
		scanf("%s", input);
		send(sock , input , strlen(input) , 0 );
		printf("C: input sent\n");
		value = read(sock, buffer, 1024);
		printf("%s", buffer);
		memset(buffer, 0, strlen(buffer));
	}

}




