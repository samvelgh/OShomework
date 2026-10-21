#include <stdio.h>

int main() {
    int a = 42;
    char b = 'S';
    double c = 3.14;
    short d = 5;

    printf("Size of int: %zu bytes\n", sizeof(a));
    printf("Size of char: %zu bytes\n", sizeof(b));
    printf("Size of double: %zu bytes\n", sizeof(c));
    printf("Size of short: %zu bytes\n\n", sizeof(d));

    printf("Address of int: %p\n", &a);
    printf("Address of char: %p\n", &b);
    printf("Address of double: %p\n", &c);
    printf("Address of short: %p\n", &d);

    return 0;
}
