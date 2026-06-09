#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

int is_leap_year(int y) {
    return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}

int main() {
    struct Date d;

    printf("enter date (day month year): ");
    if (scanf("%d %d %d", &d.day, &d.month, &d.year) != 3) {
        perror("invalid format");
        return 1;
    }

    int valid = 1;

    if (d.year < 1 || d.month < 1 || d.month > 12 || d.day < 1) {
        valid = 0;
    } else {
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (is_leap_year(d.year)) {
            days_in_month[2] = 29;
        }
        if (d.day > days_in_month[d.month]) {
            valid = 0;
        }
    }

    if (valid) {
        printf("valid date\n");
    } else {
        printf("invalid date\n");
    }

    return 0;
}
