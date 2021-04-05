#include "shlib.h"

/**
 *
 *
 *
 */
void unget_char(sauce_t *ptr)
{
	if (ptr->charpo < 0)
		return;
	ptr->charpo -= 1;
}

/**
 *
 *
 */
char next_char(sauce_t *ptr)
{
	char c1 = 0;

	if (ptr == NULL || ptr->buffer == NULL)
	{
		perror("OOPS");
		return (00);
	}

	if (ptr->charpo == -2)
		ptr->charpo += 1;
	else
		c1 = ptr->buffer[ptr->charpo];
	if (++ptr->charpo >= ptr->buffsize)
	{
		ptr->charpo = ptr->buffsize;
		return (-1);
	}
	return (ptr->buffer[ptr->charpo]);
}

/**
 *
 *
 */
char peek_char(sauce_t *ptr)
{
	long pos;

	if (ptr == NULL || ptr->buffer == NULL)
	{
		perror("OOPS");
		return (00);
	}
	pos = ptr->charpo;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= ptr->buffsize)
		return (-1);
	return (ptr->buffer[pos]);
}

/**
 *
 *
 */
void skip_white_spaces(sauce_t *ptr)
{
	char c;

	if (ptr == NULL || ptr->buffer == NULL)
		return;
	while (((c = peek_char(ptr)) != -1) && (c == 32 || c == 9))
		next_char(ptr);
}



















