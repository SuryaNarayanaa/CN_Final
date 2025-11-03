#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    int n ; 

    addr_len = sizeof(client_addr);
char buffer[1024] ;
    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to IP and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }




    while(1)
    {
    n = recvfrom(server_socket, buffer, sizeof(buffer) , 0 , (struct sockaddr *)&client_addr , &addr_len ) ; 
    buffer[n] = '\0' ; 
            printf("Client: %s\n", buffer);

	           if (strcmp(buffer, "exit") == 0) {
            printf("Client exited. Closing server.\n");
            break;
        }
    
   fgets(buffer,sizeof(buffer) , stdin) ; 
  buffer[strcspn(buffer, "\n") ] = '\0';
	sendto(server_socket , buffer  , sizeof(buffer) ,  0 , (struct sockaddr *)&client_addr , addr_len) ;

   


     if (strcmp(buffer, "exit") == 0) {
            printf("Server exiting.\n");
            break;
        }
}

close(server_socket) ; 
}
