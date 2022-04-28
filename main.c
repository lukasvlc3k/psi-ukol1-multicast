#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *multicast_group = "239.255.255.250";
    int port = 1900;

    // UDP socket creating
    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_descriptor < 0) {
        perror("Socket creating failed");
        exit(EXIT_FAILURE);
    }

    // Prepare address
    struct sockaddr_in address;
    // memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    // Listen on any IP of all interfaces (0.0.0.0)
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    // Bind
    if (bind(socket_descriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Joining multicast group
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(multicast_group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    // Request to join the multicast group
    if (setsockopt(socket_descriptor, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mreq, sizeof(mreq)) < 0) {
        perror("Error setting multicast group");
        exit(EXIT_FAILURE);
    }

    puts("Listening to multicasts...");

    // loop of received SSDP
    char buffer[BUFFER_SIZE];
    u_int address_length = sizeof(address);

    while (1) {
        size_t bytes_received = recvfrom(
                socket_descriptor,
                buffer,
                BUFFER_SIZE,
                0,
                (struct sockaddr *) &address,
                &address_length
        );
        if (bytes_received < 0) {
            perror("Error reading data from socket");
            return 1;
        }

        // adding \0 to the end of the buffer (null-terminating the string)
        buffer[bytes_received] = '\0';
        puts(buffer);
    }
}