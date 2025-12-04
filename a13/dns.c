#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <hostname> <port>\n", argv[0]);
        return 1;
    }

    const char *hostname = argv[1];
    const char *port = argv[2];

    struct addrinfo hints, *result, *rp;
    int sockfd;

    // Prepare hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP

    // DNS lookup
    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "DNS lookup failed: %s\n", gai_strerror(status));
        return 1;
    }

    // Try each address returned
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;       // success

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "Could not connect to host.\n");
        freeaddrinfo(result);
        return 1;
    }

    freeaddrinfo(result);

    // Build HTTP GET request
    char request[512];
    snprintf(request, sizeof(request),
             "GET / HTTP/1.0\r\nHost: %s\r\n\r\n",
             hostname);

    // Send request
    write(sockfd, request, strlen(request));

    // Read response
    char buffer[4096];
    int bytes;
    while ((bytes = read(sockfd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    close(sockfd);
    return 0;
}
