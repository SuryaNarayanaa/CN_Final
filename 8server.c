#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len;
	char buffer[1024];

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
	{
		perror("Cannot create socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Bind failed");
		close(server_sock);
		exit(1);
	}

	listen(server_sock, 5);
	printf("Server is listening on PORT 8080\n");

	addr_len = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
	printf("Client connected.\n");

	recv(client_sock, buffer, sizeof(buffer), 0);

	// Reverse the string
	int len = strlen(buffer);
	for (int i = 0; i < len / 2; i++)
	{
		char temp = buffer[i];
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = temp;
	}

	send(client_sock, buffer, strlen(buffer) + 1, 0);
	printf("Reversed string sent to client.\n");

	close(client_sock);
	close(server_sock);

	return 0;
}