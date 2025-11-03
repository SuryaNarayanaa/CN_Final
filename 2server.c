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
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_sock, (struct sockaddr *)&server_addr , sizeof(server_addr) ) < 0 )
	{perror("Bindng failed");
		close(server_sock);
		exit(1);
	}


	listen(server_sock, 5) ; 
	printf(" SERVER listentin on PORT 8080\n") ;
	client_sock =accept( server_sock ,  (struct sockaddr * )&client_addr, &addr_len);

	
	printf(" CLIENT CONNECTED \n") ;

	recv (client_sock, &buffer , sizeof(buffer) , 0) ; 
       for (int i =0 ; buffer[i]!='\0' ; i++ )
       { if (isupper(buffer[i])){
		       buffer[i] = tolower(buffer[i]);
		       }



	else if (islower(buffer[i])){
		buffer[i] = toupper(buffer[i]);
	
	}
       }
	

       send(client_sock , &buffer, strlen(buffer)+1 , 0  ) ;

        printf("Modified string sent to client.\n");

    close(client_sock);
    close(server_sock);

    return 0;
		

}
