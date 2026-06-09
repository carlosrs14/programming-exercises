#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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

    printf("enter elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            perror("invalid format");
            free(arr);
            return 1;
        }
    }

    insertion_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("[%d]", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
