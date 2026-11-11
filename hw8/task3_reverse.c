/*
 * Homework 8, Task 3: Reverse file reader
 * CS 331A,B Operating Systems
 *
 * Prints a file's bytes in reverse order by seeking backward one byte at a time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    char path[1024];
    int fd;
    off_t size;
    off_t pos;
    char c;
    ssize_t n;

    printf("Enter path to an existing text file: ");
    fflush(stdout);
    if (fgets(path, sizeof(path), stdin) == NULL) {
        fprintf(stderr, "Error reading path\n");
        return 1;
    }
    path[strcspn(path, "\n")] = '\0';

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening '%s': %s\n", path, strerror(errno));
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        fprintf(stderr, "Error seeking to end: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    for (pos = size - 1; pos >= 0; pos--) {
        if (lseek(fd, pos, SEEK_SET) < 0) {
            fprintf(stderr, "Error seeking to %lld: %s\n", (long long)pos, strerror(errno));
            close(fd);
            return 1;
        }
        n = read(fd, &c, 1);
        if (n < 0) {
            fprintf(stderr, "Error reading byte at %lld: %s\n", (long long)pos, strerror(errno));
            close(fd);
            return 1;
        }
        if (n == 0) {
            break;
        }
        if (write(STDOUT_FILENO, &c, 1) < 0) {
            fprintf(stderr, "Error writing to stdout: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
