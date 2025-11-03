#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

struct dns_record {
    char domain[50];
    char ip[20];
};

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[100];
    int n, found = 0;

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

    // Step 3: Bind socket to port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    printf("DNS Server running on port 8080...\n");

    // Step 4: DNS lookup table
    struct dns_record table[] = {
        {"www.google.com", "142.250.190.4"},
        {"www.yahoo.com", "98.137.11.163"},
        {"www.youtube.com", "142.250.182.238"},
        {"www.openai.com", "104.18.33.45"},
        {"www.github.com", "140.82.113.4"},
    };
    int table_size = sizeof(table) / sizeof(table[0]);

    addr_size = sizeof(client_addr);

    // Step 5: Receive hostname from client
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client_addr, &addr_size);
    buffer[n] = '\0';
    printf("Received domain name from client: %s\n", buffer);

    // Step 6: Search domain in table
    char response[100];
    found = 0;
    for (int i = 0; i < table_size; i++) {
        if (strcmp(buffer, table[i].domain) == 0) {
            strcpy(response, table[i].ip);
            found = 1;
            break;
        }
    }

    if (!found)
        strcpy(response, "Domain not found");

    // Step 7: Send response to client
    sendto(sockfd, response, strlen(response) + 1, 0,
           (struct sockaddr *)&client_addr, addr_size);

    printf("Response sent to client: %s\n", response);

    close(sockfd);
    return 0;
}
