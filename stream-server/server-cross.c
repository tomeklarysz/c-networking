/*
** cross_platform_server.c -- a stream socket server demo
*/

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <process.h>
    // #pragma comment(lib, "Ws2_32.lib") for msv compiler
#else
    #include <pthread.h>
		#include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10   // how many pending connections queue will hold

#ifdef _WIN32
    #define close_socket closesocket
#else
    #define close_socket close
#endif

// Function to handle client connections
void handle_client(void *socket_desc) {
    int new_fd = *(int *)socket_desc; // Get the new socket descriptor
    free(socket_desc); // Free the allocated memory for the socket descriptor

    if (send(new_fd, "Hello, world!", 13, 0) == -1)
        perror("send");

    close_socket(new_fd); // Close the socket after sending the message
    // return NULL; // Return from the thread
}

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            fprintf(stderr, "WSAStartup failed.\n");
            return 1;
        }
    #endif

    int sockfd, new_fd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    int rv;
    int yes=1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        #ifndef _WIN32
            if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                perror("setsockopt");
                return 1;
            }
        #endif

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close_socket(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 1;
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        return 1;
    }

    // #ifndef _WIN32
    //     struct sigaction sa;
    //     sa.sa_handler = sigchld_handler;
    //     sigemptyset(&sa.sa_mask);
    //     sa.sa_flags = SA_RESTART;
    //     if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    //         perror("sigaction");
    //         return 1;
    //     }
    // #endif

    printf("server: waiting for connections...\n");

    while(1) {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);
				
				 // Allocate memory for socket descriptor to pass to the thread
        int *socket_ptr = malloc(sizeof(int)); 
        if (socket_ptr == NULL) {
            perror("malloc");
            close_socket(new_fd);
            continue;
        }
        *socket_ptr = new_fd; // Assign the socket descriptor to the allocated memory
        #ifdef _WIN32
            // Create a thread to handle the client connection
            _beginthread(handle_client, 0, socket_ptr);
        #else
            pthread_t thread;
            // Create a thread to handle the client connection
            if (pthread_create(&thread, NULL, (void *)handle_client, socket_ptr) != 0) {
                perror("pthread_create");
                free(socket_ptr); // Free if thread creation fails
                close_socket(new_fd);
            }
            pthread_detach(thread); // Optional: detach the thread so we don't need to join
        #endif
    }

    close_socket(sockfd);

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
