#include <stdio.h>
#include <stdlib.h> //exit()
#include <string.h> //memset()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h> //read()/write()

//bzero(struct, size) is obsolete, use memset(struct, value, size) instead
//bcopy(src, dest, size) is obsolete, use memcpy(dest, src, size) instead

/*
struct hostent {
	h_name      {     ptr-> "official_hostname" }
	h_aliases   { [   ptr-> "alias #1",
			  ptr-> "alias #2", ...
			  NULL ] }
	h_addrtype  {     (int) AF_INET }
	h_length    {     (int) 4 }
	h_addr_list { [   ptr-> IP_ADDR_1, //sizeof(IP_ADDR_1) == h_length
			  ptr-> IP_ADDR_2, ...
			  NULL ] }
}
*/


void error(char *msg) {
	perror(msg);
	exit(1);
}

#define BUF_SIZE 256
int main(int argc, char *argv[]) {
	int sockfd;
	int portno;
	int n;
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[BUF_SIZE];
	
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	
	portno = atoi(argv[2]); //assumes string contains int, else undefined behavior.
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket(protocol-family, socket-type, socket-protocol-type) => file-descriptor
	if ( server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	
	memset( (char *) &serv_addr, 0, sizeof(serv_addr)); //zero-out struct 'serv_addr'
	serv_addr.sin_family = AF_INET;
	memcpy( (char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length); //see notes above on 'struct hostent'
	serv_addr.sin_port = htons(portno); //host-bytes => network-bytes
	// Attempt connection, if return is negitive, exit with error message.
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { error("ERROR connection to remote"); }
	
	printf("Please enter the message: ");
	memset(buffer, 0, BUF_SIZE); //zero-out buffer.
	fgets(buffer, BUF_SIZE-1, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) { error("ERROR writing to socket"); }

	memset(buffer, 0, BUF_SIZE);
	n = read(sockfd, buffer, BUF_SIZE-1); //read sockfd into buffer, leaving room for NULL terminator.
	if (n < 0) { error("ERROR reading from socket"); }
	printf("%s\n", buffer);
	
	return(0);
}
