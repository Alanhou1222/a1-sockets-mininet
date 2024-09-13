#include <stdio.h>		// printf()
#include <string.h> 	// strlen()
#include <string>
#include <stdlib.h>		// atoi()
#include <sys/socket.h>	// socket(), bind(), listen(), accept()
#include <unistd.h>		// close()

#include "functions.h"

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc == 4 && std::string(argv[1]) == "-s" && std::string(argv[2]) == "-p") {

		int port = atoi(argv[3]);
        if(port < 1024 || port > 65535) {
            printf("Error: port number must be in the range of [1024, 65535]\n");
		    return 1;
        }

        if (run_server(port) == -1) {
            return 1;
        }

	}
    else if(argc == 8 && std::string(argv[1]) == "-c" && std::string(argv[2]) == "-h" && std::string(argv[4]) == "-p" && std::string(argv[6]) == "-t") {
        
        const char * hostname = argv[3];
        int port = atoi(argv[5]);
        int t = atoi(argv[7]);

        if(port < 1024 || port > 65535) {
            printf("Error: port number must be in the range of [1024, 65535]\n");
		    return 1;
        }
        if(t <= 0) {
            printf("Error: time argument must be greater than 0\n");
		    return 1;
        }

        send_message(hostname, port, t);
    }
    else {
        printf("Error: missing or extra arguments\n");
		return 1;
    }
	return 0;
}
