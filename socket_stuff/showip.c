#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];
    if(argc != 2) {
        fprintf(stdout, "usage: showip <hostname>\n");
        return 1;
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }
    printf("IP address for %s\n\n", argv[1]);
    for(p=res;p;p=p->ai_next) {
        void *addr;
        char *ipver;
        if(p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("%s: %s\n", ipver, ipstr);
    }
    freeaddrinfo(res);
    return 0;
}
