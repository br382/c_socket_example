// A simple server using TCP with port passed as an argument
#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//bzero(struct,size) is obsolete, use memset(struct,value,size) instead

void error(char *msg) {
	perror(msg);
	exit(1);
}

#define BUF_SIZE 256
int main(int argc, char *argv[]) {
	int sockfd;
	int newsockfd;
	int portno;
	int clilen;
	int n;

	char buffer[BUF_SIZE];

	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket(domain, type, protocol) => file-descriptor
	if (sockfd < 0) { error("ERROR opening socket"); }
	
	//zero out the struct 'serv_addr'
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	portno = atoi(argv[1]); //assumes input string is int, otherwise causes undefined behaviour.

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno); //host bytes => network bytes
	
	// Attempt bind, and test if return value is less than zero, if true "ERROR".
	if ( bind(sockfd, (struct sockaddr *) *serv_addr, sizeof(serv_addr)) <0) { error("ERROR on accept"); }
	listen(sockfd,5); //listen(file-descriptor, max-queue-wait-len);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_adr, &clilen);
	if (newsockfd < 0) { error("ERROR on accept"); }
	
	memset(buffer, 0, BUF_SIZE);
	n = read(newsockfd, buffer, 255);
	
	if (n < 0) { error("ERROR reading from socket"); }
	printf("Here is the message: %s\n", buffer);
	
	n = write(newsockfd, "I got your message", 18);
	if (n < 0) { error("ERROR writing response to socket"); }
	
	return(0);
}
