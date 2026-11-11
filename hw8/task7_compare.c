/*
 * Homework 8, Task 7: Byte-wise file comparator
 * CS 331A,B Operating Systems
 *
 * Compares two files chunk-by-chunk and reports the first differing
 * 0-based byte index, or that they are identical.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096

static int read_path(const char *prompt, char *buf, size_t buflen) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)buflen, stdin) == NULL) {
        return -1;
    }
    buf[strcspn(buf, "\n")] = '\0';
    return 0;
}

int main(void) {
    char path1[1024], path2[1024];
    int fd1, fd2;
    char buf1[BUFSIZE], buf2[BUFSIZE];
    size_t index = 0;

    if (read_path("Enter first file path: ", path1, sizeof(path1)) < 0 ||
        read_path("Enter second file path: ", path2, sizeof(path2)) < 0) {
        fprintf(stderr, "Error reading paths\n");
        return 1;
    }

    fd1 = open(path1, O_RDONLY);
    if (fd1 < 0) {
        fprintf(stderr, "Error opening '%s': %s\n", path1, strerror(errno));
        return 1;
    }
    fd2 = open(path2, O_RDONLY);
    if (fd2 < 0) {
        fprintf(stderr, "Error opening '%s': %s\n", path2, strerror(errno));
        close(fd1);
        return 1;
    }

    for (;;) {
        ssize_t n1 = read(fd1, buf1, BUFSIZE);
        ssize_t n2 = read(fd2, buf2, BUFSIZE);
        if (n1 < 0 || n2 < 0) {
            fprintf(stderr, "Error reading: %s\n", strerror(errno));
            close(fd1);
            close(fd2);
            return 1;
        }

        ssize_t nmin = n1 < n2 ? n1 : n2;
        for (ssize_t i = 0; i < nmin; i++) {
            if (buf1[i] != buf2[i]) {
                printf("Files differ at byte %zu\n", index + (size_t)i);
                close(fd1);
                close(fd2);
                return 1;
            }
        }

        if (n1 != n2) {
            /* shorter file ended; first differing byte is at common prefix length */
            printf("Files differ at byte %zu\n", index + (size_t)nmin);
            close(fd1);
            close(fd2);
            return 1;
        }

        index += (size_t)n1;
        if (n1 == 0) {
            /* both EOF with equal sizes */
            break;
        }
    }

    printf("Files are identical\n");
    close(fd1);
    close(fd2);
    return 0;
}
