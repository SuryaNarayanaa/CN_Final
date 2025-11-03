#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


void xor(char *dividend, char * divisor) 
{
	for(int i =0 ; i < strlen(divisor) ; i++ ) 
	{
		dividend[i] = (dividend[i] == divisor[i]  )? '0' : '1';
	}
}

void crc ( char data[] , char   key[] , char remainder[] ) 
{

	int data_len = strlen(data) ; 
	int key_len = strlen(key) ; 
	char temp[50] ; 
	char div[50] ; 
	strcpy(temp, data) ; 
	
	for (int i = 0; i < key_len - 1; i++)
    		temp[data_len + i] = '0';
	temp[data_len + key_len - 1] = '\0';


	strncpy(div , temp , key_len) ; 
	div[key_len] =  '\0' ; 

	for (int  i= 0 ;  i < data_len ; i++ ) 
	{
	
		if (div[0] == '1' ) {
		
		xor(div, key);
		}
            if (i + key_len < strlen(temp))
                 div[key_len - 1] = temp[i + key_len];
           else
                 div[key_len - 1] = '\0';
		
	   memmove(div, div+1 , key_len-1) ; 
		
	
	}

strncpy(remainder, div, key_len - 1);
remainder[key_len - 1] = '\0';



}


int main()
{
    char data[50], key[50], remainder[50], transmitted[50] , check_rem[50] ; 



    printf("Enter Data: ");
    scanf("%s", data);
    printf("Enter Key (Generator Polynomial): ");
    scanf("%s", key);


    crc(data, key, remainder ) ; 
    strcpy(transmitted , data ) ; 
    strcat(transmitted ,remainder ) ;
        printf("Transmitted Frame: %s\n", transmitted);

	    crc(transmitted, key, check_rem);

  
    int error = 0;
    for (int i = 0; i < strlen(check_rem); i++) {
        if (check_rem[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected in received frame!\n");
    else
        printf("No error detected. Transmission successful.\n");

    return 0;
}
