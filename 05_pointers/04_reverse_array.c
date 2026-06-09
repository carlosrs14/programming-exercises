#include <stdio.h>
#include <stdlib.h>

void reverse(int* arr, int n) {
    int *start = arr;
    int *end = arr + n - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    int n;
    
    printf("n: ");
    scanf("%d", &n);

    if (n < 0) {
        perror("invalid number");
        return 1;
    }

    int *arr = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("idx%d: ", i);
        scanf("%d", arr + i);
    }

    reverse(arr, n);

    for (int i = 0; i < n; i++) {
        printf("[%d]", *(arr + i));
    }
    printf("\n");

    free(arr);

    return 0;
}
