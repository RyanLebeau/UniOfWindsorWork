/*
Ryan Lebeau
26/11/2017
System Programming
AssignFiveServer.c
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
	int nSocket, value, counter=0;
    struct sockaddr_in address;
    int option = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *input;
	int pipeFileDesc[2];
	
      
    //creating socket file descriptor
    int fileDescServer = socket(AF_INET, SOCK_STREAM, 0);
      
    //attaching socket to defined port 8080
    setsockopt(fileDescServer, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
	printf("Waiting for connection...\n");
	if(counter==0){
		//attching to defined port 8080
		bind(fileDescServer,(struct sockaddr *)&address, sizeof(address));
		listen(fileDescServer, 3);
		nSocket = accept(fileDescServer, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	}
	counter++;
	printf("Connected.\n");
	while(1){
		pipe(pipeFileDesc);
		value = read(nSocket, buffer, 1024);
		printf("Entered Command: %s\n", buffer);
		if(fork()==0){
			close(pipeFileDesc[0]);
			dup2(pipeFileDesc[1], 1);
			dup2(pipeFileDesc[1], 2);
			close(pipeFileDesc[1]);
			execlp(buffer, NULL);
		}
		else{
			if(strcmp(buffer, "")==0)
				break;
			memset(buffer, 0, strlen(buffer));
			close(pipeFileDesc[1]);
			while (read(pipeFileDesc[0], buffer, sizeof(buffer)) != 0)
			{
			}
			send(nSocket, buffer, strlen(buffer), 0);
			memset(buffer, 0, strlen(buffer));
		}
	}

}


