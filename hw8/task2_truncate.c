/*
 * Homework 8, Task 2: File truncation
 * CS 331A,B Operating Systems
 *
 * Writes A-Z to data.txt, reports size, truncates to 10 bytes,
 * verifies new size, and prints remaining content.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    const char *filename = "data.txt";
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int fd;
    off_t size;
    char buf[64];
    ssize_t n;

    /* Create/overwrite data.txt and write A-Z (26 bytes) */
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error opening '%s' for write: %s\n", filename, strerror(errno));
        return 1;
    }

    n = write(fd, alphabet, 26);
    if (n < 0) {
        fprintf(stderr, "Error writing alphabet: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (n != 26) {
        fprintf(stderr, "Short write: wrote %zd of 26 bytes\n", n);
        close(fd);
        return 1;
    }

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing after write: %s\n", strerror(errno));
        return 1;
    }

    /* Reopen read/write */
    fd = open(filename, O_RDWR);
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
    printf("Current size: %lld bytes\n", (long long)size);

    if (ftruncate(fd, 10) < 0) {
        fprintf(stderr, "Error truncating: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        fprintf(stderr, "Error seeking to end after truncate: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    printf("New size: %lld bytes\n", (long long)size);

    if (lseek(fd, 0, SEEK_SET) < 0) {
        fprintf(stderr, "Error rewinding: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        fprintf(stderr, "Error reading remaining content: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    buf[n] = '\0';
    printf("Remaining content: %s\n", buf);

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
