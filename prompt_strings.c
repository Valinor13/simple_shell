#include "shlib.h"

/**
 *
 *
 */
void print_prompt1(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 *
 *
 */
void print_prompt2(void)
{
	write(STDOUT_FILENO, "> ", 2);
}

/**
 *
 *
 */
void print_prompt3(void)
{
	write(STDOUT_FILENO, "# ", 2);
}
