#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int server_sock;
	struct sockaddr_in server_addr;
	char buffer[1024];

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
	{
		perror("Cannot create socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Connection failed");
		close(server_sock);
		exit(1);
	}

	printf("Connected to server.\n");

	printf("Enter a string: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';

	send(server_sock, buffer, strlen(buffer) + 1, 0);
	printf("String sent to server.\n");

	recv(server_sock, buffer, sizeof(buffer), 0);

	printf("Reversed string: %s\n", buffer);

	close(server_sock);

	return 0;
}