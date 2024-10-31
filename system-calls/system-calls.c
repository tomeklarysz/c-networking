#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// getadrrinfo()
int getaddrinfo(const char *node,    // e.g. "www.example.com" or IP
                const char *service, // e.g. "http" or port number
                const struct addrinfo *hints,
                struct addrinfo **res);

/*
it gives you a pointer to a linked-list, res, of results

The node parameter is the host name to connect to, or an IP address.
Next is the parameter service, which can be a port number

Finally, the hints parameter points to a struct addrinfo that 
you’ve already filled out with relevant information.
*/

// error check (if there's an error getaddrinfo() returns non-zero)
if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
  fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
  exit(1);
}

freeaddrinfo(servinfo);


// simple call if client wants to connect to a particular server:
// it doesn't actually connect, but sets up the structures we'll use later

int status;
struct addrinfo hints;
struct addrinfo *servinfo; // will point to the results

memset(&hints, 0, sizeof hints); // make sure the struct is empty
hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

// get ready to connect
status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

// servinfo now points to a linked list of 1 or more struct addrinfos
// etc.
