#include <stdio.h>

enum Day {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

const char *day_names[] = {
    "Invalid",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

int main() {
    int day;
    printf("enter a number (1-7): ");
    if (scanf("%d", &day) != 1) {
        perror("invalid input");
    }

    if (day > 7 || day < 1) {
        perror("invalid number");
    }
    printf("%s\n", day_names[day]);
    return 0;
}
