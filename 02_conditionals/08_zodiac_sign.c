#include <stdio.h>

int main() {
    int dia, mes;

    printf("day/month: ");
    
    if (scanf("%d/%d", &dia, &mes) != 2) {
        perror("invalid format");
        return 1;
    }

    if ((mes == 3 && dia >= 21) || (mes == 4 && dia <= 19)) printf("Aries\n");
    else if ((mes == 4 && dia >= 20) || (mes == 5 && dia <= 20)) printf("Tauro\n");
    else if ((mes == 5 && dia >= 21) || (mes == 6 && dia <= 20)) printf("Gemini\n");
    else if ((mes == 6 && dia >= 21) || (mes == 7 && dia <= 22)) printf("Cancer\n");
    else if ((mes == 7 && dia >= 23) || (mes == 8 && dia <= 22)) printf("Leo\n");
    else if ((mes == 8 && dia >= 23) || (mes == 9 && dia <= 22)) printf("Virgo\n");
    else if ((mes == 9 && dia >= 23) || (mes == 10 && dia <= 22)) printf("Libra\n");
    else if ((mes == 10 && dia >= 23) || (mes == 11 && dia <= 21)) printf("Scorpio\n");
    else if ((mes == 11 && dia >= 22) || (mes == 12 && dia <= 21)) printf("Sagittarius\n");
    else if ((mes == 12 && dia >= 22) || (mes == 1 && dia <= 19)) printf("Capricorn\n");
    else if ((mes == 1 && dia >= 20) || (mes == 2 && dia <= 18)) printf("Aquarius\n");
    else if ((mes == 2 && dia >= 19) || (mes == 3 && dia <= 20)) printf("Pisces\n");
    else printf("invalid day\n");

    return 0;
}
