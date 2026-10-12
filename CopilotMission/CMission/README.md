# Beginner — "wc-lite" (word/line/byte counter) in C
# Goal
    Recreate a minimal version of Unix wc: count lines, words, and bytes for one or more files and stdin.
# Why it’s useful
    Teaches file I/O, string/token parsing, command-line arguments, and careful handling of edge cases in C.
# Requirements (functional)
 ## Program name: wc-lite
 ## Usage: wc-lite [-l] [-w] [-c] [file...]
    -l: print line count
    -w: print word count
    -c: print byte count
    If no flags: print all three counts.
    If no files: read from stdin.
 ## Correctly handle large files (streaming, not loading whole file).
 ## Return non-zero exit code for unreadable files but continue processing others.
# Non-functional
 ## Build with gcc, strict warnings (-Wall -Wextra).
 ## No external libraries beyond C standard library.
# Suggested file layout
 ## src/wc_lite.c, include/wc_lite.h, Makefile, tests/test_wc.sh
# Implementation details / API
 ## Provide functions:
    int process_stream(FILE *f, long *lines, long *words, long *bytes);
    int process_file(const char *path, long *lines, long *words, long *bytes);
 ## Word definition: whitespace-delimited by isspace().
# Milestones (3)
    CLI parsing and single-file processing.
    Multiple files and stdin support.
    Robust error handling and tests.
# Tests / sample checks
 ## Run on empty file → 0 0 0
 ## Run on file with multibyte/Unicode bytes (explain it counts bytes, not characters).
 ## Test combined flags and multiple files.
# Estimated time: 3–6 hours.
# Skills/modules practiced
 ## C: main(), argc/argv, FILE*, fgets/fread, isspace(), errno handling
 ## Tooling: Makefile, gcc warnings, basic shell testing
# Starter prompt for Copilot
    "Write a C program wc_lite.c implementing a minimal wc command: counts lines, words, and bytes from files or stdin.Provide functions process_stream(FILE *f, long *lines, long *words, long *bytes) and process_file(const char *path, long *lines, long *words, long *bytes). Use isspace() for word splitting, stream files (no full-file buffering), and print counts in the format 'lines words bytes filename'. Add error handling and comments. Target C11 and compile with -Wall -Wextra."
# What Copilot needs (context)
    The workspace with src/ and existing Makefile (optional) or the file content to edit.
# Expected outcome
    A working command-line C program and shell tests.