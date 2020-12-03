#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


/*receive is a void function that takes in a pointer to socketID as a parameter
it while take in a message from the corresponding socket and print that message*/
void* receive(void* socketID){

	int clientSocket = *((int *) socketID);
	
	//while true, this loop will print the message it receives.
	while(1){

		char msg[1024]; //char array for the message
		int reader = recv(clientSocket,data,1024,0); /*creates a reader that contains the length of the 
message sent to the buffer @ data in bytes*/
		msg[reader] = '\0'; //adds the terminating character to the end of message.
		printf("%s\n", msg);

	}

}
/*main method:
	creates a clientSocket that holds a FD that refers to that endpoint.*/
int main(){

	int clientSocket = socket(PF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET; //
	serverAddr.sin_port = htons(8080); //converts value between host and network byte code
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //converts value between host and network byte code
	
	///conditional that guarantees the connection is established
	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) 			return 0;

	printf("Connection established ...\n");

	pthread_t thread; //thread variable declaration
	pthread_create(&thread, NULL, receive, (void *) &clientSocket ); //creates a thread that starts a routine to receive a message

	//while true that sends input across the socketchannel.
	while(1){

		char input[1024];
		scanf("%s",input);

		if(strcmp(input,"LIST") == 0){

			send(clientSocket,input,1024,0);

		}
		if(strcmp(input,"SEND") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);
			
			scanf("%[^\n]s",input);
			send(clientSocket,input,1024,0);

		}

	}


}
