#include "shlib.h"
/**
 * read_cmd - takes input and reads to the main file
 * Return:  returns a character string of the command
 */
char *read_cmd(void)
{
	char *buf = NULL, *ptr = NULL;
	size_t buflen, bsz = 1024, ptrlen = 0;

	while (getline(&buf, &bsz, stdin))
	{
		buflen = _strlen(buf);
		if (ptr == NULL)
		{
			ptr = malloc(sizeof(char) * (buflen) + 1);
			if (ptr == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
		else if (ptr != NULL)
		{
			ptr = _realloc(ptr, ptrlen, ptrlen + buflen - 1);
			if (ptr == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
		_strcpy(ptr, buf, ptrlen);
		if (buf[buflen - 1] == '\n')
		{
			if (buflen == 1 || buf[buflen - 2] != '\\')
			{
				free(buf), ptr[ptrlen + buflen - 1] = 00;
				return (ptr);
			}
			buflen -= 2, print_prompt2();
		}
		ptrlen += buflen;
	}
free(buf), ptr[ptrlen + buflen - 1] = 00;
return (ptr);
}

/**
 * _memcpy - copy one file to another
 * @n: the measure of the copy
 * @dest: destination for copy
 * @src: source to copy
 * Return: dest(ination)
 */
char *_memcpy(char *dest, char *src, size_t n)
{
	size_t x;

	for (x = 0; x < n; x++)
	{
		dest[x] = src[x];
	}
	return (dest);
}

/**
 * *_memset - a custome memset function
 * @s: input string
 * @b: input character
 * @n: input integer for length of const application
 * Return: returns the updated string
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
return (s);
}
