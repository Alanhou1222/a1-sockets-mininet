#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//server functions
int handle_connection(int connectionfd);
int run_server(int port, int queue_size);

//client functions
int send_message(const char *hostname, int port, const char *message);

#endif
