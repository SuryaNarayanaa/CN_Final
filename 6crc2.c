#include <stdio.h>
#include <string.h>
 
#define MAX 100
 
void xorOperation(char *dividend, char *divisor, int pos) {
    for (int i = 0; i < strlen(divisor); i++) {
        dividend[pos + i] = (dividend[pos + i] == divisor[i]) ? '0' : '1';
	}
}
 
void divide(char *dividend, char *divisor) {
    int div_len = strlen(divisor);
    int total_len = strlen(dividend);
 
    for (int i = 0; i <= total_len - div_len; i++) {
        if (dividend[i] == '1') {
            xorOperation(dividend, divisor, i);
        }
	}
}
 
int main() {
    char data[MAX], divisor[MAX], dividend[MAX], remainder[MAX];
	
    printf("Enter Data: ");
    scanf("%s", data);
    printf("Enter Generator (Divisor): ");
    scanf("%s", divisor);
 
    int data_len = strlen(data);
    int div_len = strlen(divisor);
    int total_len = data_len + div_len - 1;
 
    strcpy(dividend, data);
 
    for (int i = 0; i < div_len - 1; i++)
        strcat(dividend, "0");
 
    printf("\nDividend (Data + Zeros): %s\n", dividend);
 
    char temp[MAX];
    strcpy(temp, dividend);
    divide(temp, divisor);
 
    strcpy(remainder, temp + data_len);
    printf("Remainder: %s\n", remainder);
 
    strcat(data, remainder);
    printf("Transmitted Frame: %s\n", data);
 
    printf("\nAt Receiver Side:\n");
    char received[MAX];
    printf("Enter Received Frame: ");
    scanf("%s", received);
 
    divide(received, divisor);
 
    int error = 0;
    for (int i = strlen(received) - (div_len - 1); i < strlen(received); i++) {
        if (received[i] != '0') {
            error = 1;
            break;
        }
	}
    if (error)
        printf(" Error detected in received data!\n");
    else
        printf(" No error detected. Data received correctly.\n");
 
    return 0;
}

