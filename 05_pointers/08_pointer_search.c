#include <stdio.h>
#include <stdlib.h>

int* buscar(int* arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (*(arr + i) == val) {
            return (arr + i);
        }
    }
    return NULL;
}

int main() {
    int n;

    printf("n: ");
    scanf("%d", &n);
    
    int* arr = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("idx%d: ", i);
        scanf("%d", arr + i);
    }
    
    int val;
    printf("val: ");
    scanf("%d", &val);
    
    int *res = buscar(arr, n, val);
    
    if (res != NULL) {
        printf("found: %d\n", (int)(res - arr));
    } else {
        printf("not found\n");
    }
    
    free(arr);

    return 0;
}
