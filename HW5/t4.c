#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    char **strings = (char **)malloc(3 * sizeof(char *));

    if (strings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    printf("Enter 3 strings:\n");

    for (i = 0; i < 3; i++) {
        printf("String %d: ", i + 1);
        scanf(" %50[^\n]", strings[i]);
    }

    printf("First 3 strings:\n");

    for (i = 0; i < 3; i++) {
        printf("%s\n", strings[i]);
    }

    char **temp = (char **)realloc(strings, 5 * sizeof(char *));

    if (temp == NULL) {
        printf("Reallocation failed.\n");

        for (i = 0; i < 3; i++) {
            free(strings[i]);
        }

        free(strings);
        return 1;
    }

    strings = temp;

    for (i = 3; i < 5; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    printf("Enter 2 more strings:\n");

    for (i = 3; i < 5; i++) {
        printf("String %d: ", i + 1);
        scanf(" %50[^\n]", strings[i]);
    }

    printf("All 5 strings:\n");

    for (i = 0; i < 5; i++) {
        printf("%s\n", strings[i]);
    }

    for (i = 0; i < 5; i++) {
        free(strings[i]);
    }

    free(strings);

    return 0;
}
