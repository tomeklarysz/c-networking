close(sockfd);
// close the connection on your socket descriptor

int shutdown(int sockfd, int how);

/*
have more control over how the socket closes
how
0   further receives are disallowed
1   further sends are disallowed
2   further sends and receives are disallowed (like close())

shutdown() returns 0 on success, and -1 on error (with errno set accordingly)

shutdown() doesn’t actually close the file descriptor—it just changes its usability.
To free a socket descriptor, you need to use close().

on Windows use closesocket() instead of close()
*/