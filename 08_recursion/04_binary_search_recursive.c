#include <stdio.h>
#include <stdlib.h>

int binary_search_rec(int* arr, int low, int high, int x) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        if (arr[mid] > x) {
            return binary_search_rec(arr, low, mid - 1, x);
        }
        return binary_search_rec(arr, mid + 1, high, x);
    }
    return -1;
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

    int* arr = (int*)malloc(n * sizeof(int));

    printf("enter sorted elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            perror("invalid format");
            free(arr);
            return 1;
        }
    }

    int x;

    printf("enter value to search: ");
    if (scanf("%d", &x) != 1) {
        perror("invalid format");
        free(arr);
        return 1;
    }

    printf("%d\n", binary_search_rec(arr, 0, n - 1, x));

    free(arr);

    return 0;
}
