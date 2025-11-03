#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int tot, win , ack , i =  1 , j ;
	printf("Enter the total number of frames :  " ); 
	scanf("%d", &tot); 

	printf("Enter the window size :  " ); 
	scanf("%d", &win);

	while (i <= tot) 
	{
	printf("Sender sending frames : " ) ;
 	
	for(j = i ; j < i+win  && j <=tot ; j ++ ) 
	{
		printf("%d" ,  j ) ; 
	}

	printf("\n"); 
	printf("Enter last ACK received : (-1 for packet loss ) ") ; 	
	scanf("%d" , &ack);

	if(ack == -1 ) 
	{   printf("Acknowledgement lost. Retransmitting frames from %d again.\n", i);
	 } 
	else 
	{

	if (ack < i -1 ||  ack >= i+win   )
	{
		printf("Invalid ACK. Retransmitting from %d.\n", i);
		printf("\n") ; 
	}
	else
	{
		printf("ACK for frame %d received " , ack ) ; 
		i = ack +1   ; 

	 }
	
	}
	sleep(1) ; 
	}
}
