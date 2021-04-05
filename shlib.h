#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>

typedef struct source_s
{
	char *buffer;
	long buffsize;
	long charpo;
} sauce_t;

typedef struct token_s
{
	sauce_t *ptr;
	int tlen;
	char *txt;
} token_t;

extern struct token_s eof_token;

void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
int _putchar(char c);
char *_memcpy(char *dest, char *src, size_t n);
int _strcmp(char *s1, char *s2);
void _puts(char *str);
size_t _strlen(char *s);
char *_realloc(char *ptr, size_t olen, size_t nlen);
char *_strcpy(char *dest, char *src, size_t ptrlen);
char next_char(sauce_t *ptr);
void unget_char(sauce_t *ptr);
char peek_char(sauce_t *ptr);
void skip_white_spaces(sauce_t *ptr);
token_t *tokenize(sauce_t *ptr);
void free_token(token_t *tkn);

#endif
