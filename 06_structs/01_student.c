#include <stdio.h>

struct Student {
    char name[51];
    int age;
    float grades[3];
};

int main() {
    struct Student est;

    printf("enter name: ");
    if (scanf("%50s", est.name) != 1) {
        perror("invalid name");
        return 1;
    }

    printf("enter age: ");
    if (scanf("%d", &est.age) != 1) {
        perror("invalid age");
        return 1;
    }

    printf("enter 3 grades: ");
    if (scanf("%f %f %f", &est.grades[0], &est.grades[1], &est.grades[2]) != 3) {
        perror("invalid format g1 g2 g3");
        return 1;
    }

    float avg = (est.grades[0] + est.grades[1] + est.grades[2]) / 3.0f;

    printf("Name: %s\nAge: %d\nAverage: %.2f\n", est.name, est.age, avg);

    return 0;
}
