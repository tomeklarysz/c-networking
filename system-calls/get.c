// who are you?

#include <sys/socket.h>

int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);

/*
sockfd is the descriptor of the connected stream socket, 
addr is a pointer to a struct sockaddr (or a struct sockaddr_in) 
that will hold the information about the other side of the connection, 
and addrlen is a pointer to an int, that should be initialized 
to sizeof *addr or sizeof(struct sockaddr).
*/

// who am i?

#include <unistd.h>

int gethostname(char *hostname, size_t size);

/*
The arguments are simple: hostname is a pointer to an array of chars 
that will contain the hostname upon the function’s return, 
and size is the length in bytes of the hostname array.
*/