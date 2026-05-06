
#include <stdio.h> 
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 256

int main () {

    char input[MAX_WORD_LEN];
    char output[MAX_WORD_LEN];
    int shift;

    printf("\n---SECRET DATA---\n\n");

    printf("Enter an Encryption: ");
    fgets(input, sizeof(input), stdin);
    fflush(stdin);
   
    for (int i = 0; i < strlen(input); i++) {
        char c = toupper(input[i]);
        output[i] = c;
    }
    printf("Encryption: %s\n", output);

    printf("Magic Number (that your secret friend told ya): ");
    scanf("%d", &shift);   

    for (int i = 0; i < strlen(input); i++) {
        char c = toupper(input[i]);
        c += (-shift);
        
        if (c > 'Z') {
            c = 'Z' + (c - 91);
        }
        else if (c < 'A') {
            c = 'Z' + (c - 64);
        }
        output[i] = c;
    }
    printf("Decryption: %s\n", output);

    return 0;
}
