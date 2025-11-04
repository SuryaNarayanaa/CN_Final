#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    int server_sock;
    struct sockaddr_in server_addr;
    long card_no;
    int pin;
    float amount;
    char buffer[1024];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(server_sock);
        exit(1);
    }

    printf("Connected to ATM server.\n");

    printf("Enter card number: ");
    scanf("%ld", &card_no);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    send(server_sock, &card_no, sizeof(long), 0);
    send(server_sock, &pin, sizeof(int), 0);

    int n = recv(server_sock, buffer, sizeof(buffer) - 1, 0);
    buffer[n] = '\0';
    printf("Server: %s\n", buffer);

    // If login successful, proceed to withdraw
    if (strstr(buffer, "Welcome") != NULL) {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);
        send(server_sock, &amount, sizeof(float), 0);

        n = recv(server_sock, buffer, sizeof(buffer) - 1, 0);
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(server_sock);

    return 0;
}