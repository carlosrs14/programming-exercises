#include <stdio.h>

float area_square(float l) { return l * l; }
float area_rectangle(float b, float h) { return b * h; }
float area_triangle(float b, float h) { return 0.5f * b * h; }

int main() {
    int op;
    float l, b, h;

    printf("1. square\n");
    printf("2. rectangle\n");
    printf("3. triangle\n");
    printf("enter your option: ");

    if (scanf("%d", &op) != 1) {
        perror("invalid format");
        return 1;
    }
    

    switch (op) {
        case  1:
            printf("enter l: ");
            scanf("%f", &l);
            printf("%.2f\n", area_square(l));
            break;

        case  2:
            printf("enter b: ");
            scanf("%f", &b);
            printf("enter h: ");
            scanf("%f", &h);
            printf("%.2f\n", area_rectangle(b, h));
            break;

        case  3:
            printf("enter b: ");
            scanf("%f", &b);
            printf("enter h: ");
            scanf("%f", &h);
            printf("%.2f\n", area_triangle(b, h));

            break;

        default:
            perror("invalid option");
            break;
    }

    return 0;
}
