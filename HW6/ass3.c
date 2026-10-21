#include <stdio.h>

struct NormalStruct {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct PackedStruct {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

int main() {
    struct NormalStruct s1;
    struct PackedStruct s2;

    printf("Normal Struct:\n");
    printf("Size: %zu bytes\n", sizeof(s1));
    printf("Address of a: %p\n", &s1.a);
    printf("Address of b: %p\n", &s1.b);
    printf("Address of c: %p\n\n", &s1.c);

    printf("Packed Struct:\n");
    printf("Size: %zu bytes\n", sizeof(s2));
    printf("Address of a: %p\n", &s2.a);
    printf("Address of b: %p\n", &s2.b);
    printf("Address of c: %p\n", &s2.c);

    return 0;
}
