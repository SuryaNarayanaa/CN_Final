#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct {
    char name[50];
    long card_no;
    int pin;
    float balance;
} Customer;

Customer customers[] = {
    {"Alice", 1234567890123456, 1234, 1000.0},
    {"Bob", 2345678901234567, 5678, 500.0},
    {"Charlie", 3456789012345678, 9012, 2000.0}
};
int num_customers = 3;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    long card_no;
    int pin;
    float amount;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(1);
    }

    listen(server_sock, 5);
    printf("ATM Server is listening on PORT %d\n", port);

    addr_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client connected.\n");

    // Receive card_no and pin
    recv(client_sock, &card_no, sizeof(long), 0);
    recv(client_sock, &pin, sizeof(int), 0);

    // Find customer
    Customer *cust = NULL;
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].card_no == card_no && customers[i].pin == pin) {
            cust = &customers[i];
            break;
        }
    }

    if (cust == NULL) {
        char msg[] = "Invalid card number or PIN.";
        send(client_sock, msg, strlen(msg), 0);
    } else {
        char welcome[100];
        sprintf(welcome, "Welcome %s! Your balance is %.2f", cust->name, cust->balance);
        send(client_sock, welcome, strlen(welcome), 0);

        // Receive withdraw amount
        recv(client_sock, &amount, sizeof(float), 0);

        if (amount > cust->balance) {
            char msg[] = "Insufficient balance.";
            send(client_sock, msg, strlen(msg), 0);
        } else {
            cust->balance -= amount;
            char msg[100];
            sprintf(msg, "Withdrawal successful. New balance: %.2f", cust->balance);
            send(client_sock, msg, strlen(msg), 0);
        }
    }

    close(client_sock);
    close(server_sock);

    return 0;
}