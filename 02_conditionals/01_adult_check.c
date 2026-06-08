#include <stdio.h>

int main() {
    int age;

    printf("age: ");

    if (scanf("%d", &age) != 1) {
        perror("wrong argument");
        return 1;    
    }

    if (age >= 18) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }

    return 0;
}
