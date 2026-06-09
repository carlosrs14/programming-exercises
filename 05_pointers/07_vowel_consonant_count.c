#include <stdio.h>
#include <ctype.h>

void count(char* str, int* voc, int* cons) {
    *voc = 0;
    *cons = 0;
    char* p = str;
    while (*p != '\0') {
        char c = tolower(*p);
        if (c >= 'a' && c <= 'z') {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                (*voc)++;
            } else {
                (*cons)++;
            }
        }
        p++;
    }
}

int main() {
    char str[101];

    printf("str: ");
    scanf("%100s", str);

    int voc, cons;

    count(str, &voc, &cons);
    
    printf("vowels: %d\nconsonants: %d\n", voc, cons);
    
    return 0;
}
