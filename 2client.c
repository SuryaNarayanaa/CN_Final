#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<unistd.h>



int main()
{
	int server_sock , client_sock ;
	struct sockaddr_in server_addr, client_addr ;
	socklen_t addr_len ;
	addr_len = sizeof(client_addr) ;
	char buffer[1024];

	server_sock = socket(AF_INET , SOCK_STREAM , 0 ) ;
	if (server_sock < 0 )
	{
		perror("Cannot create server socket") ;
		 exit(1) ;
	}

	server_addr.sin_family = AF_INET;

	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(server_sock, (struct sockaddr *)&server_addr , sizeof(server_addr) ) < 0 )
	{perror("Bindng failed");
		close(server_sock);
		exit(1);
	}


	printf("Enter a string");
	fgets(buffer , sizeof(buffer) , stdin) ; 
	buffer[strcspn(buffer, "\n")] ='\0';

	send(server_sock , 	&buffer  , strlen(buffer)+1 , 0 ) ;
	printf("STRING SENT TO SERVER " ) ; 
		
recv(server_sock , 	&buffer  , sizeof(buffer) , 0 ) ;


printf("changed case : \n") ; 

printf("%s \n", buffer) ; 

    close(server_sock);

    return 0;
		

}
