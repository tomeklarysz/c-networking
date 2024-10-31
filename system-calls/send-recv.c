/*
send() and recv()
these two functions are for communicating over stream sockets
or connected datagram sockets. (to use regular unconnected datagram
socekts, use sendto() and recvfrom())
*/

int send(int sockfd, const void *msg, int len, int flags);

/*
sockfd is the socket descriptor you want to send data to 
(whether it’s the one returned by socket() or the
one you got with accept()). msg is a pointer to the data you want to send,
and len is the length of that data in bytes. Just set flags to 0. 
(See the send() man page for more information concerning flags.)

send() returns the numbers of bytes actually sent out - might be less
than the number you told it to sent
*/

int recv(int sockfd, void *buf, int len, int flags);

/*
sockfd is the socket descriptor to read from, buf is the buffer 
to read the information into, len is the maximum length of the buffer, 
and flags can again be set to 0. (See the recv() man page for flag information.)
recv() returns the number of bytes actually read into the buffer, 
or -1 on error (with errno set, accordingly).
recv() can return 0 - this means that the remote side has closed the connection on you
*/

int sendto(int sockfd, const void *msg, int len, unsigned int flags,
           const struct sockaddr *to, socklen_t tolen);

/*
to is a pointer to a struct sockaddr (which will probably be another struct sockaddr_in
or struct sockaddr_in6 or struct sockaddr_storage that you cast at the last minute) which contains
the destination IP address and port. tolen, an int deep-down, can simply be set to sizeof *to or
sizeof(struct sockaddr_storage).
*/

int recvfrom(int sockfd, void *buf, int len, unsigned int flags,
             struct sockaddr *from, int *fromlen);
