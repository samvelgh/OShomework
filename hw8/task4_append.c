/*
 * Homework 8, Task 4: Append a line to log.txt (O_APPEND)
 * CS 331A,B Operating Systems
 *
 * Opens log.txt with O_APPEND, reads one line from stdin via read(0,...),
 * prepends "PID=<pid>: ", writes it, then prints the file offset via
 * lseek(fd, 0, SEEK_CUR).
 *
 * Why SEEK_CUR still grows with O_APPEND: each write is forced to the
 * current end of file by the kernel, and the file offset is updated to
 * that new end. SEEK_CUR therefore reports the growing EOF position even
 * though we never seeked ourselves before the write.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSZ 4096

int main(void) {
    const char *filename = "log.txt";
    int fd;
    char inbuf[BUFSZ];
    char outbuf[BUFSZ + 64];
    ssize_t nread, nwritten;
    size_t len;
    off_t pos;
    pid_t pid = getpid();

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error opening '%s': %s\n", filename, strerror(errno));
        return 1;
    }

    printf("Enter a line to append: ");
    fflush(stdout);

    nread = read(0, inbuf, BUFSZ);
    if (nread < 0) {
        fprintf(stderr, "Error reading stdin: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (nread == 0) {
        /* empty input: still write PID prefix + newline */
        inbuf[0] = '\0';
        len = 0;
    } else {
        len = (size_t)nread;
        /* drop trailing newline for rebuild; we add our own below */
        if (len > 0 && inbuf[len - 1] == '\n') {
            len--;
        }
    }

    nwritten = snprintf(outbuf, sizeof(outbuf), "PID=%d: ", (int)pid);
    if (nwritten < 0 || (size_t)nwritten >= sizeof(outbuf)) {
        fprintf(stderr, "Error formatting PID prefix\n");
        close(fd);
        return 1;
    }
    if (len > sizeof(outbuf) - (size_t)nwritten - 2) {
        fprintf(stderr, "Input too long\n");
        close(fd);
        return 1;
    }
    memcpy(outbuf + nwritten, inbuf, len);
    nwritten += (ssize_t)len;
    outbuf[nwritten++] = '\n';

    {
        ssize_t off = 0;
        while (off < nwritten) {
            ssize_t w = write(fd, outbuf + off, (size_t)(nwritten - off));
            if (w < 0) {
                fprintf(stderr, "Error writing log: %s\n", strerror(errno));
                close(fd);
                return 1;
            }
            off += w;
        }
    }

    pos = lseek(fd, 0, SEEK_CUR);
    if (pos < 0) {
        fprintf(stderr, "Error seeking: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    printf("File offset after write (SEEK_CUR): %lld\n", (long long)pos);

    if (close(fd) < 0) {
        fprintf(stderr, "Error closing: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
