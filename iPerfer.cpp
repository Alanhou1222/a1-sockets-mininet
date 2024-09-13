#include <stdio.h>		// printf()
#include <string.h> 	// strlen()
#include <stdlib.h>		// atoi()
#include <sys/socket.h>	// socket(), bind(), listen(), accept()
#include <unistd.h>		// close()

#include "functions.h"

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 2) {
		printf("Usage: ./server port_num\n");
		return 1;
	}
	int port = atoi(argv[1]);
	printf("Starting server on port %d\n", port);

	if (run_server(port, 10) == -1) {
		return 1;
	}
	return 0;
}
