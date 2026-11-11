# CS 331 Operating Systems — Homework 8: Files

Seven C programs using low-level file I/O syscalls (`open`, `read`, `write`, `lseek`, `ftruncate`).
Compiled with `gcc -Wall -Wextra` on Ubuntu 24.04 (gcc 13.3.0); all built with no warnings.

| Task | File | Purpose |
|------|------|---------|
| 1 | task1_copy.c | Copy file contents via read/write loop |
| 2 | task2_truncate.c | ftruncate + lseek size reporting |
| 3 | task3_reverse.c | Reverse-order byte reader |
| 4 | task4_append.c | O_APPEND logging with PID prefix |
| 5 | task5_sparse.c | Sparse file with a 1 MiB hole |
| 6 | task6_overwrite.c | In-place line overwrite |
| 7 | task7_compare.c | Byte-wise file comparator |

See `README_explanation.md` for the detailed per-task explanation and `screenshots/` for run output.
