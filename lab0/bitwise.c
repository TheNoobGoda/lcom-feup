#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[])
{
	char a;	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n; // value to convert must be smaller than 256
	int bit; // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
 
	// Validate command line arguments
    if (argc != 4){
        print_usage("bitwise");
        return 0;
    }
    
    if (strcmp(argv[1],"h")!=0 && strcmp(argv[1],"l")!=0 && strcmp(argv[1],"r")!=0 && strcmp(argv[1],"s")!=0 && strcmp(argv[1],"t")!=0){
        print_usage("bitwise");
        return 0;
    }

    n = strtol(argv[2],NULL,10);
    if (n>=256){
        print_usage("bitwise");
        return 0;
    }

    bit = strtol(argv[3],NULL,10);
    if (bit<0 || bit>7){
        print_usage("bitwise");
        return 0;
    }
	// Print to stdout the binary representation of n
    
    strcpy(binary,byte2bin(n,binary));
    printf("%s\n",binary);
	
	// Do what the user asked and print the result

    if (strcmp(argv[1],"h")==0){
        char mask = BIT(bit);
        if (n & mask) printf("Yes\n");
        else printf("No\n");
    }
    else if(strcmp(argv[1],"l")==0){
        char mask = BIT(bit);
        if (n & mask) printf("No\n");
        else printf("Yes\n");
    }
    else if (strcmp(argv[1],"s")==0){
        char mask = BIT(bit);
        n = n | mask;
        strcpy(binary,byte2bin(n,binary));
        printf("%s\n",binary);
    }
    else if (strcmp(argv[1],"r")==0){
        char mask = BIT(bit);
        if (n & mask) n = n^mask;
        strcpy(binary,byte2bin(n,binary));
        printf("%s\n",binary);
    }
    else if (strcmp(argv[1],"t")==0){
        char mask = BIT(bit);
        n = n ^mask;
        strcpy(binary,byte2bin(n,binary));
        printf("%s\n",binary);
    }

    return 0;
}
