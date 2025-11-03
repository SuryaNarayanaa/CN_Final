#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT1 5000   // sender port
#define PORT2 6000   // receiver port
#define MAX 1024

int main() {
    int sockfd;
    struct sockaddr_in my_addr, peer_addr;
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Bind receiver to its port
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(PORT2);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = INADDR_ANY;
    peer_addr.sin_port = htons(PORT1);

    socklen_t len = sizeof(peer_addr);

    printf("UDP Chat Receiver started. Waiting for messages...\n");

    while (1) {
        recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&peer_addr, &len);
        printf("Friend: %s", buffer);
        if (strncmp(buffer, "exit", 4) == 0)
            break;

        printf("You: ");
        fgets(buffer, MAX, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&peer_addr, len);
        if (strncmp(buffer, "exit", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}
