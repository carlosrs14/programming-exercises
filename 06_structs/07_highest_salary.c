#include <stdio.h>
#include <stdlib.h>

struct Employee {
    char name[51];
    int id;
    float salary;
};

int main() {
    int n;

    printf("enter number of employees: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        perror("invalid count");
        return 1;
    }

    struct Employee* emp = (struct Employee*) malloc(n * sizeof(struct Employee));
    int max_idx = 0;

    for (int i = 0; i < n; i++) {
        printf("enter employee %d (name id salary): ", i + 1);

        if (scanf("%50s %d %f", emp[i].name, &emp[i].id, &emp[i].salary) != 3) {
            perror("invalid format");
            free(emp);
            return 1;
        }

        if (emp[i].salary > emp[max_idx].salary) {
            max_idx = i;
        }
    }

    printf("Name: %s\nSalary: %.2f\n", emp[max_idx].name, emp[max_idx].salary);

    free(emp);

    return 0;
}
