#include <stdio.h>

struct Original {
    char a;
    int b;
    double c;
};

struct Reordered {
    double c;
    int b;
    char a;
};

int main() {
    struct Original s1;
    struct Reordered s2;

    printf("Original struct:\n");
    printf("Size: %zu bytes\n", sizeof(s1));
    printf("Address of a: %p\n", &s1.a);
    printf("Address of b: %p\n", &s1.b);
    printf("Address of c: %p\n\n", &s1.c);

    printf("Reordered struct:\n");
    printf("Size: %zu bytes\n", sizeof(s2));
    printf("Address of c: %p\n", &s2.c);
    printf("Address of b: %p\n", &s2.b);
    printf("Address of a: %p\n", &s2.a);

    return 0;
}
