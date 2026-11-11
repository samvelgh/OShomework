/*
 * Homework 8, Task 5: Sparse file creator
 * CS 331A,B Operating Systems
 *
 * Creates sparse.bin: writes "START", seeks forward 1 MiB without writing
 * zeros, writes "END". Reopens and prints apparent size.
 *
 * Why du is much smaller than the apparent size: the 1 MiB hole created by
 * lseek past EOF is not allocated on disk. The filesystem stores a hole
 * (logical gap) instead of physical zero blocks, so st_size / lseek end
 * is large while actual disk blocks used stay small.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define SKIP (1024 * 1024)

int main(void) {
    const char *filename = "sparse.bin";
    int fd;
    off_t size;
    ssize_t n;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error opening '%s': %s\n", filename, strerror(errno));
        return 1;
    }

    n = write(fd, "START", 5);
    if (n != 5) {
        fprintf(stderr, "Error writing START: %s\n", n < 0 ? strerror(errno) : "short write");
        close(fd);
        return 1;
    }

    if (lseek(fd, SKIP, SEEK_CUR) < 0) {
        fprintf(stderr, "Error seeking forward 1 MiB: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    n = write(fd, "END", 3);
    if (n != 3) {
        fprintf(stderr, "Error writing END: %s\n", n < 0 ? strerror(errno) : "short write");
        close(fd);
        return 1;
    }

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing after write: %s\n", strerror(errno));
        return 1;
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error reopening '%s': %s\n", filename, strerror(errno));
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        fprintf(stderr, "Error seeking to end: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    printf("Apparent file size: %lld bytes\n", (long long)size);

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
