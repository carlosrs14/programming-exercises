#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[51];
    char phone[21];
    char email[51];
};

int main() {
    int n;

    printf("enter number of contacts: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        perror("invalid count");
        return 1;
    }

    struct Contact* agenda = (struct Contact*)malloc(n * sizeof(struct Contact));

    for (int i = 0; i < n; i++) {
        printf("enter contact %d (name phone email): ", i + 1);
        if (scanf("%50s %20s %50s", agenda[i].name, agenda[i].phone, agenda[i].email) != 3) {
            perror("invalid format");
            free(agenda);
            return 1;
        }
    }

    char target[51];

    printf("enter contact name to search: ");
    if (scanf("%50s", target) != 1) {
        perror("invalid format");
        free(agenda);
        return 1;
    }

    int found_idx = -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(agenda[i].name, target) == 0) {
            found_idx = i;
            break;
        }
    }

    if (found_idx != -1) {
        printf("phone: %s\nemail: %s\n", agenda[found_idx].phone, agenda[found_idx].email);
    } else {
        printf("not found\n");
    }

    free(agenda);

    return 0;
}
