/*
 * Homework 8, Task 1: Copy file contents
 * CS 331A,B Operating Systems
 *
 * Copies the full contents of a source file to a destination file
 * using a read/write loop with POSIX open/read/write/close.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096

int main(void) {
    char src_path[1024];
    char dst_path[1024];
    char buf[BUFSIZE];
    int src_fd, dst_fd;
    ssize_t nread, nwritten;
    size_t total = 0;

    printf("Enter source file path: ");
    fflush(stdout);
    if (fgets(src_path, sizeof(src_path), stdin) == NULL) {
        fprintf(stderr, "Error reading source path\n");
        return 1;
    }
    src_path[strcspn(src_path, "\n")] = '\0';

    printf("Enter destination file path: ");
    fflush(stdout);
    if (fgets(dst_path, sizeof(dst_path), stdin) == NULL) {
        fprintf(stderr, "Error reading destination path\n");
        return 1;
    }
    dst_path[strcspn(dst_path, "\n")] = '\0';

    src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0) {
        fprintf(stderr, "Error opening source '%s': %s\n", src_path, strerror(errno));
        return 1;
    }

    dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        fprintf(stderr, "Error opening destination '%s': %s\n", dst_path, strerror(errno));
        close(src_fd);
        return 1;
    }

    while ((nread = read(src_fd, buf, BUFSIZE)) > 0) {
        ssize_t offset = 0;
        while (offset < nread) {
            nwritten = write(dst_fd, buf + offset, (size_t)(nread - offset));
            if (nwritten < 0) {
                fprintf(stderr, "Error writing to destination: %s\n", strerror(errno));
                close(src_fd);
                close(dst_fd);
                return 1;
            }
            offset += nwritten;
            total += (size_t)nwritten;
        }
    }

    if (nread < 0) {
        fprintf(stderr, "Error reading source: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    if (close(src_fd) < 0) {
        fprintf(stderr, "Error closing source: %s\n", strerror(errno));
        close(dst_fd);
        return 1;
    }
    if (close(dst_fd) < 0) {
        fprintf(stderr, "Error closing destination: %s\n", strerror(errno));
        return 1;
    }

    printf("Copied %zu bytes\n", total);
    return 0;
}
