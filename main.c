
#include <stdio.h> 
#include <ctype.h>
#include <string.h>

int main() {

    char alpha[26];
    char word[64];
    int x;
    
    printf("Enter a word: ");
    fgets(word, sizeof(word), stdin);
    printf("%s\n", word);
    if (word < 65 || word > 90) {
        printf("Invalid input\n");
    }

    printf("How much do you want to shift? Number: ");
    scanf("%d", &x);

    for (int i = 0; i < 26; i++) {
        alpha[i] = 'A' + i;
        alpha[i] = alpha[i] + x;
        if (alpha[i] > 'Z') {
            alpha[i] = 'A' + (alpha[i] - 91);
        }
        else if (alpha[i] < 'A') {
            alpha[i] = 'Z' + (alpha[i] - 64);
        }
        printf("%d: %c\n", i, alpha[i]);
    }

       

    return 0;
}
