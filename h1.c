#include "shlib.h"
/**
 * read_cmd - takes input and reads to the main file
 * Return:  returns a character string of the command
 */
char *read_cmd(void)
{
	char *buf = NULL, *ptr = NULL, ptrlen = 0, *ptr2 = NULL;
	size_t buflen, bsz = 1024;

	while (getline(&buf, &bsz, stdin))
	{
		buflen = _strlen(buf);
		if (ptr == NULL)
		{
			ptr = malloc(sizeof(char) * (buflen + 1));
			if (ptr == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
		else if (ptr != NULL)
		{
			ptr2 = _realloc(ptr, buflen, ptrlen + buflen);
			if (ptr2 == NULL)
			{
				free(ptr), free(buf);
				return (NULL);
			}
			ptr = ptr2;
		}
		_strcpy(ptr + ptrlen, buf);
		if (buf[buflen - 1] == '\n')
		{
			if (buflen == 1 || buf[buflen - 2] != '\\')
			{
				free(buf), ptr[buflen] = 00;
				return (ptr);
			}
			ptr[ptrlen + buflen - 2] = 00, buflen -= 2, print_prompt2();
		}
		ptrlen += buflen;
	}
free(ptr2), free(buf);
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
