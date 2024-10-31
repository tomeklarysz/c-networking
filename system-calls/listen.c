int listen(int sockfd, int backlog);
// backlog is the number of connections allowed on the incoming queue
// listen() returns -1 and sets errno on error

// to listening for incoming connections the sequence of calls is:
getaddrinfo();
socket();
bind();
listen();
/* accept() goes here */