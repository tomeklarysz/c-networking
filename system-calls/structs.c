// socket descriptor is int

struct addrinfo {
  int ai_flags;             // AI_PASSIVE, AI_CANONNAME, etc.
  int ai_family;            // AF_INET, AF_INET6, AF_UNSPEC
  int ai_socktype;          // SOCK_STREAM, SOCK_DGRAM
  int ai_protocol;          // use 0 for "any"
  size_t ai_addrlen;        // size of ai_addr in bytes
  struct sockaddr *ai_addr; // struct sockaddr_in or _in6
  char *ai_canonname;       // full canonical hostname
  
  struct addrinfo *ai_next; // linked list, next node
};

// getaddrinfo() to fill out struct addrinfo ^

struct sockaddr {
  unsigned short sa_family; // address family, AF_xxx
  char sa_data[14];         // 14 bytes of protocol address
};

// parallel structure: struct sockaddr_in
// (IPv4 only--see struct sockaddr_in6 for IPv6)

// important bit: a pointer to a struct sockaddr_in can be
//  cast to a pointer to a struct sockaddr and vice-versa

struct sockaddr_in {
  short int sin_family;         // Address family, AF_INET
  unsigned short int sin_port;  // Port number
  struct in_addr sin_addr;      // Internet address
  unsigned char sin_zero[8];    // Same size as struct sockaddr
};

struct in_addr {
  uint32_t s_addr;              // 32-bit int (4 bytes)
}

// sockaddr_in6 for ipv6

// to hold both ipv4 and ipv6 struct sockaddr_storage
struct sockaddr_storage {
  sa_family_t ss_family; // address family
  // all this is padding, implementation specific, ignore it:
  char __ss_pad1[_SS_PAD1SIZE];
  int64_t __ss_align;
  char __ss_pad2[_SS_PAD2SIZE];
};
// then cast it to the needed type- e.g. sockaddr_in 