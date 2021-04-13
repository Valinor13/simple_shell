#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>

void _prompt1(void);
void _prompt2(void);
void _prompt3(void);
char *read_line(int *line_cnt);
int _putchar(char c);
char *_memcpy(char *dest, char *src, size_t n);
int _strcmp(char *s1, char *s2);
void _puts(char *str);
size_t _strlen(char *s);
char *_realloc(char *ptr, size_t olen, size_t nlen);
char *_strcpy(char *dest, char *src, size_t ptrlen);
size_t get_tkncnt(char *str, char *delim);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *get_path(char **pthtok, char **tknptr);
char *_gwd(char *tmpth);
void _exec(char **tknptr, char *cmd, char *av[], char *env[], int *line_cnt);
char *_strcpyr(char *dest, char *src, size_t ptrlen);
void _pterror(char **av, char **tknptr, int *line_cnt);
char *printint(int *line_cnt);
size_t _charcmp(char *tknptr, char slash);
char *get_tknptr(char *env[], char *av[], char *tknptr[], char *cmd);
void handler(int num);

#endif
