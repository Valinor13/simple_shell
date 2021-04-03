#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>

void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
int _putchar(char c);
char *_memcpy(char *dest, char *src, size_t n);
int _strcmp(char *s1, char *s2);
void _puts(char *str);
size_t _strlen(char *s);
char *_realloc(char *ptr, size_t olen, size_t nlen);
char *_strcpy(char *dest, char *src);

#endif
