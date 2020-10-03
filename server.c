#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int clearBuffer(char buff[], int size) {
	for(int i = 0; i < size; i++) {
		buff[i] = '\0';
	}
}


int main(int argc, char* argv[]) {
	int serverSocket, client, valread;
	struct sockaddr_in serverAddress;
	int addrlen = sizeof(serverAddress);
	char buffer[1024] = {0};
	char* serverMessage = "\033[0;33mWelcome to the server!\n\033[0m";
	char* receive = "Message sent successfully!\n";

	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(80);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSocket, (struct sockaddr *) &serverAddress, addrlen) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(listen(serverSocket, 5) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if((client = accept(serverSocket, (struct sockaddr *) &serverAddress, (socklen_t*) &addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	write(client, serverMessage, strlen(serverMessage));

	while(1) {
		valread = read(client, buffer, sizeof(buffer));
		if(buffer[0] != '\n') printf("\033[1;31m%s\033[0m", buffer);
		clearBuffer(buffer, 1024);
		write(client, receive, strlen(receive));
	}


	return 0;
}