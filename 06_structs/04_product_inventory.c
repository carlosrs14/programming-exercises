#include <stdio.h>
#include <stdlib.h>

struct Product {
    int id;
    char name[51];
    float price;
    int quantity;
};

int main() {
    int n;

    printf("enter number of products: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        perror("invalid count");
        return 1;
    }

    struct Product* prods = (struct Product*)malloc(n * sizeof(struct Product));
    float total = 0.0f;

    for (int i = 0; i < n; i++) {
        printf("enter product %d details (id name price quantity): ", i + 1);
        
        if (scanf("%d %50s %f %d", &prods[i].id, prods[i].name, &prods[i].price, &prods[i].quantity) != 4) {
            perror("invalid format");
            free(prods);
            return 1;
        }
        total += prods[i].price * prods[i].quantity;
    }

    printf("total price: %.2f\n", total);

    free(prods);

    return 0;
}
