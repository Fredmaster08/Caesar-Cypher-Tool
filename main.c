
#include <stdio.h> 
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 256

int main(int argc, char** argv) {

    printf("%d\n%s\n", argc, argv[0]);

    char alpha[26];
    char word[64];
    char output[MAX_WORD_LEN];
    int shift;
   

    // validation:
    printf("Enter a word (lowercase): ");
    fgets(word, sizeof(word), stdin);

    printf("Plaintext: %s\n", word);

    printf("How much do you want to shift? Number: ");
    scanf("%d", &shift);

    if (argc == true) {
        for (int i = 0; i < strlen(word) - 1; i++) {
            char c = toupper(word[i]);
            c += shift;

            if (c > 'Z') {
                c = 'A' + (c - 91);
            }
            else if (c < 'A') {
                c = 'Z' + (c - 64);
            }
            output[i] = c;
        }
        printf("Encryption: %s\n", output);
    }
           return 0;
}

