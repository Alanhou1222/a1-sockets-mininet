#include "functions.h"

#include <stdio.h>		// printf()
#include <string.h> 	// strlen()
#include <stdlib.h>		// atoi()
#include <sys/socket.h>	// socket(), bind(), listen(), accept(), connect()
#include <unistd.h>		// close()

#include "helpers.h"	// make_server_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

static const char * RESPONSE_OK = "200";

static const char * RESPONSE_ERROR = "400";
/* Server */
/**
 * Receives a string message from the client, prints it to stdout, then
 * sends the integer 42 back to the client as a success code.
 *
 * Parameters:
 * 		connectionfd: File descriptor for a socket connection (e.g. the one
 *			returned by accept())
 * Returns:
 *		0 on success, -1 on failure.
 */
int handle_connection(int connectionfd) {
	// TODO: Implement this function
	char buffer[MAX_MESSAGE_SIZE] = {};
	// (1) Receive message from client.
	int loc = 0;
	bool response_ok = true;
	while(true){
			int received = recv(connectionfd, buffer + loc, MAX_MESSAGE_SIZE, 0);
			printf("Got %d bytes\n", received);
			loc += received;
			if(loc > MAX_MESSAGE_SIZE){
					response_ok = false;
					break;
			}
			if(received == 0){
					break;
			}
	}
	// (2) Print out the message
	if(response_ok){
			printf("%s\n", buffer);
	}
	// (3) Send response code to client
	if(send(connectionfd, response_ok? RESPONSE_OK : RESPONSE_ERROR, strlen(RESPONSE_OK), 0) == -1){
		return -1;
	}
	else{
		printf("Sent response code %s\n", RESPONSE_OK);
	}
	// (4) Close connection
	close(connectionfd);
	return 0;
}

/**
 * Endlessly runs a server that listens for connections and serves
 * them _synchronously_.
 *
 * Parameters:
 *		port: The port on which to listen for incoming connections.
 *		queue_size: Size of the listen() queue
 * Returns:
 *		-1 on failure, does not return on success.
 */
int run_server(int port, int queue_size) {
	// TODO: Implement the rest of this function

	// (1) Create socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);
	// (2) Set the "reuse port" socket option
	int yes = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	// (3) Create a sockaddr_in struct for the proper port and bind() to it.
	bind(sock, (struct sockaddr*) &addr, sizeof(addr));
	if (make_server_sockaddr(&addr, port) == -1) {
		return -1;
	}
	// (4) Begin listening for incoming connections.
	listen(sock, queue_size);
	printf("Listening...\n");
	// (5) Serve incoming connections one by one forever.
	while (true) {
			int connectionfd = accept(sock, 0 , 0);
			printf("Request accepted...\n");
			handle_connection(connectionfd);
			printf("Request finished...\n");
	}
}

/* Client */
/**
 * Sends a string message to the server and waits for an integer response.
 *
 * Parameters:
 *		hostname: Remote hostname of the server.
 *		port: Remote port of the server.
 * 		message: The message to send.
 * Returns:
 *		The server's response code on success, -1 on failure.
 */
int send_message(const char *hostname, int port, const char *message) {
	if (strlen(message) > MAX_MESSAGE_SIZE) {
		printf("Error: Message exceeds maximum length\n");
		return -1;
	}

	// TODO: Implement the rest of this function

	// (1) Create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	// (2) Create a sockaddr_in to specify remote host and port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
	struct hostent *hp;
	hp = gethostbyname(hostname );
	/*
	 * gethostbyname returns a structure including the network address
	 * of the specified host.
	 */
	if (hp == (struct hostent *) 0) {
			fprintf(stderr, "%s: unknown host\n", hostname);
			exit(2);
	}
	memcpy((char *) &addr.sin_addr, (char *) hp->h_addr, hp->h_length);
	if(make_client_sockaddr(&addr, hostname, port) == -1) {
		return -1;
	}

	// (3) Connect to remote server
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		perror("connecting stream socket");
		exit(1);
	}
	// (4) Send message to remote server
	if(send(sock, message, strlen(message), 0) == -1){
		return -1;
	}
	printf("Message sent\n");
	shutdown(sock, SHUT_WR);
	// (5) Wait for integer response
	while(true){
		int loc = 0;
		char buffer[MAX_MESSAGE_SIZE] = {};
		while(true){
				int received = recv(sock, buffer + loc, MAX_MESSAGE_SIZE, 0);
				if(received == -1){
						printf("Something went wrong with receiving...\n");
						return -1;
				}
				printf("Got %d bytes\n", received);
				loc += received;
				if(received == 0){
						break;
				}
		}
		int response = atoi(buffer);
		if(!response){
			return -1;
		}
		else{
			printf("Response: %d\n", response);
			break;
		}
	}
	printf("Request finished...\n");
	// (6) Close connection
	close(sock);
	return 0;
}