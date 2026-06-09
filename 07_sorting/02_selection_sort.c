#include <stdio.h>
#include <stdlib.h>

void selection_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
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

    selection_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("[%d]", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
