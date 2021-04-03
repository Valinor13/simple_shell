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

#endif
