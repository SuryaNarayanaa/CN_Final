#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];
    socklen_t addr_size;

    // Step 1: Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Step 2: Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    addr_size = sizeof(server_addr);

    // Step 3: Input domain name
    printf("Enter domain name: ");
    scanf("%s", buffer);

    // Step 4: Send domain to server
    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&server_addr, addr_size);

    // Step 5: Receive IP address / error message
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server_addr, &addr_size);

    // Step 6: Display result
    printf("Response from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
