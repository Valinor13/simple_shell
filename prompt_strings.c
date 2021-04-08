#include "shlib.h"

/**
 * print_prompt1 - prints $
 * Return: returns void
 */
void print_prompt1(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * print_prompt2 - prints >
 * Return: returns void
 */
void print_prompt2(void)
{
	write(STDOUT_FILENO, "> ", 2);
}

/**
 * print_prompt3 - prints #
 * Return: returns void
 */
void print_prompt3(void)
{
	write(STDOUT_FILENO, "# ", 2);
}
