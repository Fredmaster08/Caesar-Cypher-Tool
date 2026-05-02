
#include <stdio.h> 
#include <ctype.h>

int main() {

    char alpha[26];
    int x;

    printf("How much do you want to shift? Number: ");
    scanf("%d", &x);

    for (int i = 0; i < 26; i++) {
        alpha[i] = 'A' + i;
        alpha[i] = alpha[i] + x;
        printf("%c\n", alpha[i]);
    }

       

    return 0;
}
