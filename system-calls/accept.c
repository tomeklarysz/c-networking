/*
when someone will try to connect() to your machine on a port
that you are listen()ing on, their connection will be queued up
waiting to be accept()ed. You call accept() and you tell it to get
the pending connection. It'll return to you a BRAND NEW SOCKET FILE DESCRIPTOR
to use for this single connection! Suddenlt, you have two socket file descriptors
for the price of one, the og one is still listening for more new connections,
and the newly created one is finally ready to send() and recv()
*/
#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t addrlen);