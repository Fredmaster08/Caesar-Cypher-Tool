
#include <stdio.h> 
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 256

int main () {

    char input[MAX_WORD_LEN];
    char output[MAX_WORD_LEN];
    int shift;

    printf("Enter an Encryption: ");
    fgets(input, sizeof(input), stdin);
    fflush(stdin);

    printf("Encryption: %s\n", input);

    printf("Shift: ");
    scanf("%d", &shift);

    for (int i = 0; i < strlen(input); i++) {
        char c = toupper(input[i]);
        c += shift;
        
        if (c > 'Z') {
            c = 'Z' + (c - 91);
        }
        else if (c < 'A') {
            c = 'Z' + (c - 64);
        }
        output[i] = c;
    }
    printf("Encryption: %s\n", output);

    return 0;
}
