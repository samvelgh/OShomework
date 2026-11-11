/*
 * Homework 8, Task 6: In-place overwrite using lseek
 * CS 331A,B Operating Systems
 *
 * Writes 1..10 one per line into numbers.txt, then replaces line 4 ("4\n")
 * with "100\n" by finding the offset of line 4, reading the remainder,
 * seeking back, writing "100\n", then writing the remainder.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    const char *filename = "numbers.txt";
    int fd;
    char buf[256];
    char *rest = NULL;
    size_t rest_cap = 0, rest_len = 0;
    off_t line4_off = -1;
    int newlines = 0;
    ssize_t n;
    char c;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error creating '%s': %s\n", filename, strerror(errno));
        return 1;
    }
    for (int i = 1; i <= 10; i++) {
        int m = snprintf(buf, sizeof(buf), "%d\n", i);
        if (write(fd, buf, (size_t)m) != m) {
            fprintf(stderr, "Error writing numbers: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
    }
    if (close(fd) < 0) {
        fprintf(stderr, "Error closing after create: %s\n", strerror(errno));
        return 1;
    }

    fd = open(filename, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error reopening '%s': %s\n", filename, strerror(errno));
        return 1;
    }

    /* Scan for start of line 4 (after 3 newlines). */
    off_t pos = 0;
    newlines = 0;
    while ((n = read(fd, &c, 1)) == 1) {
        if (newlines == 3) {
            line4_off = pos;
            break;
        }
        if (c == '\n') {
            newlines++;
        }
        pos++;
    }
    if (line4_off < 0) {
        /* consumed the byte at line4 start already? handle if we broke after reading */
        if (newlines == 3) {
            /* we read the first byte of line 4 into c; offset is pos */
            line4_off = pos;
            /* put that byte into remainder start by seeking back one */
            if (lseek(fd, line4_off, SEEK_SET) < 0) {
                fprintf(stderr, "Error rewinding to line 4: %s\n", strerror(errno));
                close(fd);
                return 1;
            }
        } else {
            fprintf(stderr, "Could not find start of line 4\n");
            close(fd);
            return 1;
        }
    } else {
        /* We broke after reading first byte of line 4; seek back to its start */
        if (lseek(fd, line4_off, SEEK_SET) < 0) {
            fprintf(stderr, "Error seeking to line 4: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
    }

    /* Skip old line 4 (read until newline) */
    while ((n = read(fd, &c, 1)) == 1) {
        if (c == '\n') {
            break;
        }
    }
    if (n < 0) {
        fprintf(stderr, "Error skipping old line 4: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    /* Read remainder into memory */
    rest_cap = 256;
    rest = malloc(rest_cap);
    if (!rest) {
        fprintf(stderr, "Out of memory\n");
        close(fd);
        return 1;
    }
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if (rest_len + (size_t)n > rest_cap) {
            rest_cap *= 2;
            char *tmp = realloc(rest, rest_cap);
            if (!tmp) {
                fprintf(stderr, "Out of memory\n");
                free(rest);
                close(fd);
                return 1;
            }
            rest = tmp;
        }
        memcpy(rest + rest_len, buf, (size_t)n);
        rest_len += (size_t)n;
    }
    if (n < 0) {
        fprintf(stderr, "Error reading remainder: %s\n", strerror(errno));
        free(rest);
        close(fd);
        return 1;
    }

    if (lseek(fd, line4_off, SEEK_SET) < 0) {
        fprintf(stderr, "Error seeking back to line 4: %s\n", strerror(errno));
        free(rest);
        close(fd);
        return 1;
    }

    if (write(fd, "100\n", 4) != 4) {
        fprintf(stderr, "Error writing 100: %s\n", strerror(errno));
        free(rest);
        close(fd);
        return 1;
    }
    if (rest_len > 0) {
        ssize_t off = 0;
        while ((size_t)off < rest_len) {
            ssize_t w = write(fd, rest + off, rest_len - (size_t)off);
            if (w < 0) {
                fprintf(stderr, "Error writing remainder: %s\n", strerror(errno));
                free(rest);
                close(fd);
                return 1;
            }
            off += w;
        }
    }
    /* Truncate in case new content is shorter than old (here 100\n is longer than 4\n, so grow) */
    {
        off_t end = lseek(fd, 0, SEEK_CUR);
        if (end < 0 || ftruncate(fd, end) < 0) {
            fprintf(stderr, "Error truncating to new end: %s\n", strerror(errno));
            free(rest);
            close(fd);
            return 1;
        }
    }
    free(rest);

    if (lseek(fd, 0, SEEK_SET) < 0) {
        fprintf(stderr, "Error rewinding for print: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    printf("Final file content:\n");
    fflush(stdout);
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, (size_t)n) < 0) {
            fprintf(stderr, "Error writing to stdout: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
    }
    if (n < 0) {
        fprintf(stderr, "Error reading for print: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
