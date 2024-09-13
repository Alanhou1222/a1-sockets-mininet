#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//server functions
int handle_connection(int connectionfd);
int run_server(int port);

//client functions
int send_message(const char *hostname, int port, int t);

#endif
