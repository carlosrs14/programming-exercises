#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("enter size: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        perror("invalid size");
        return 1;
    }

    int* arr = (int*) malloc(n * sizeof(int));

    printf("enter elements separed by space: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            perror("invalid format");
            free(arr);
            return 1;
        }
    }

    bubble_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("[%d]", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
