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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1") ;




    while(1)
    {printf("Client : " ) ;

   fgets(buffer,sizeof(buffer) , stdin) ;
  buffer[strcspn(buffer, "\n") ] = '\0';
	sendto(server_socket , buffer  , sizeof(buffer) ,  0 , (struct sockaddr *)&server_addr , addr_len) ;




     if (strcmp(buffer, "exit") == 0) {
            printf("client exiting.\n");
            break;
        }



     
         n = recvfrom(server_socket, buffer, sizeof(buffer) , 0 ,NULL , NULL ) ;
    buffer[n] = '\0' ;
            printf("Server: %s\n", buffer);

	           if (strcmp(buffer, "exit") == 0) {
            printf("server  exited. Closing server.\n");
            break;
        }
}

close(server_socket) ;
}
