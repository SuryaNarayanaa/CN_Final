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
server_addr.sin_addr.s_addr =inet_addr("127.0.0.1"); //  --------------

if ( connect(server_socket, (struct sockaddr * )&server_addr , sizeof(server_addr)   ) < 0)  // --------
{
    perror("Bind failed");
    close(server_socket) ;
    exit(1);
}	

printf("Connected to server.\n");

    // Get input from user
    printf("Enter Basic Pay: ");
    scanf("%f", &basic);
    printf("Enter HRA: ");
    scanf("%f", &hra);
    printf("Enter DA: ");
    scanf("%f", &da);
    printf("Enter PT: ");
    scanf("%f", &pt);
    printf("Enter EPF: ");
    scanf("%f", &epf)    ;

// send  and secv are always from server_sock in client side
// and vice versa in server
send(server_socket, &basic   , sizeof(float) , 0 ) ;
send(server_socket, &hra   , sizeof(float) , 0 ) ;
send(server_socket, &da   , sizeof(float) , 0 ) ;
send(server_socket, &pt   , sizeof(float) , 0 ) ;
send(server_socket, &epf   , sizeof(float) , 0 ) ;

recv(server_socket, &net_salary, sizeof(float), 0);

    printf("\nNet Salary calculated by server: ₹%.2f\n", net_salary);

    // Close socket
    close(client_socket);

    return 0;



}
