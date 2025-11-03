#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main()
{

int server_socket, client_socket;
struct sockaddr_in client_addr, server_addr ;
socklen_t addr_size;
float basic, hra, da, pt, epf, net_salary;

server_socket = socket(AF_INET, SOCK_STREAM , 0 ) ; 
if (server_socket < 0 ) 
{ perror("Socket creation failed" ) ;
	exit(1); 
}


server_addr.sin_family = AF_INET;

server_addr.sin_port = htons(8080);
server_addr.sin_addr.s_addr = INADDR_ANY;

if ( bind(server_socket, (struct sockaddr * )&server_addr , sizeof(server_addr)   ) < 0) 
{
    perror("Bind failed"); 
    close(server_socket) ; 
    exit(1);
}	

listen(server_socket , 5 ) ;
printf("Server is listening on PORT 8080\n");
addr_size = sizeof(client_addr);
client_socket = accept(server_socket , (struct sockaddr *)&client_addr , &addr_size);
printf("CLient connected\n" ) ;

recv(client_socket, &basic   , sizeof(float) , 0 ) ;
recv(client_socket, &hra   , sizeof(float) , 0 ) ; 
recv(client_socket, &da   , sizeof(float) , 0 ) ; 
recv(client_socket, &pt   , sizeof(float) , 0 ) ; 
recv(client_socket, &epf   , sizeof(float) , 0 ) ; 


net_salary = basic+hra+da-pt-epf;
send(client_socket, &net_salary, sizeof(float) , 0 )  ;
printf("Net salary is sent to client\n");
close(server_socket);

close(client_socket);

}
