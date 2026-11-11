# CS 331A,B Homework 8: Files — plain-language explanation

**Course:** Operating Systems (Sec. A, B) - Fall 2026  
**Due:** Wednesday, 11 November 2026, 11:59 PM Asia/Yerevan  
**Moodle:** https://elearning.aua.am/mod/assign/view.php?id=93515  
**Status checked:** no submission yet (do not upload until you say so)

**Submission-ready files** (on the bot computer under `/workspace/hw8-files/`):
- `task1_copy.c` … `task7_compare.c`
- `hw8_files.zip` (all seven `.c` files)

Compile any task with: `gcc -Wall -Wextra -o prog file.c`

## Task 1 — Copy file contents
Asks for source and destination paths. Opens source `O_RDONLY`, destination `O_WRONLY|O_CREAT|O_TRUNC` mode `0644`, then loops read→write until EOF. Prints total bytes copied; errors go to stderr.

## Task 2 — File truncation
Creates `data.txt`, writes A–Z (26 bytes), reopens `O_RDWR`, prints size via `lseek(SEEK_END)`, `ftruncate`s to 10 bytes, prints new size, rewinds, reads and prints `ABCDEFGHIJ`.

## Task 3 — Reverse file reader
Opens a path read-only, finds size with `lseek(SEEK_END)`, then from the last byte backward seeks, reads 1 byte, writes it to stdout. Ends with an extra newline.

## Task 4 — Append to log (`O_APPEND`)
Opens fixed `log.txt` with `O_WRONLY|O_CREAT|O_APPEND` (0644). Reads one line from stdin with `read(0, …)` (not `fgets`). Prepends `PID=<pid>: `, ensures a trailing newline, writes it, then prints `lseek(fd, 0, SEEK_CUR)`.

Comment in the source: with `O_APPEND` every write is forced to EOF by the kernel and the offset advances there, so `SEEK_CUR` still shows a growing end-of-file position.

## Task 5 — Sparse file
Creates `sparse.bin`, writes `START`, `lseek`s forward 1 MiB (`SEEK_CUR`) without writing zeros, writes `END`, reopens and prints apparent size (`5 + 1048576 + 3 = 1048584`).

Comment in the source: the hole is not allocated on disk, so `du` stays small while the logical size is large.

## Task 6 — In-place overwrite
Writes lines `1`…`10` into `numbers.txt`. Finds the byte offset of line 4 by scanning newlines, skips the old `"4\n"`, reads the remainder into memory, seeks back, writes `"100\n"`, writes the remainder, truncates to the new end, then prints the whole file. Result: `1,2,3,100,5,…,10`.

## Task 7 — Byte-wise comparator
Asks for two paths, opens both read-only, compares fixed-size chunks. On first mismatch prints `Files differ at byte N` (0-based) and exits nonzero. If one file ends first with a matching prefix, that end index is the difference. If both end together with no mismatch: `Files are identical` (exit 0).

## Checks already run
- Task 1: multi-line copy; `cmp` matched.
- Task 2: size 26 → 10; content `ABCDEFGHIJ`.
- Task 3: reverse of `hi\n` correct.
- Task 4: two appends with PID prefixes; offset grew.
- Task 5: apparent size 1048584; disk blocks much smaller.
- Task 6: line 4 became `100`.
- Task 7: differ at 2; identical; shorter file differ at 4.

Nothing was submitted or uploaded on Moodle.
