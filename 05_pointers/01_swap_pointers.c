#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    printf("x: ");
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y);

    swap(&x, &y);

    printf("x: %d\ny: %d\n", x, y);

    return 0;
}
