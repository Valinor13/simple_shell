#include "shlib.h"
/**
 * read_cmd - takes input and reads to the main file
 * Return:  returns a character string of the command
 */
char *read_cmd(void)
{
	char *buf, *ptr = NULL, *ptr2, ptrlen = 0;
	size_t buflen, bsz = 1024;

	while (getline(&buf, &bsz, stdin))
	{
		printf("before buflen assignment\n");
		buflen = _strlen(buf);
		printf("Were in the loop\n");
		if (!ptr)
		{
			ptr = malloc(sizeof(char) * (buflen + 1));
			printf("pointer malloced\n");
		}
		else
		{
			ptr2 = _realloc(ptr, buflen, ptrlen + buflen + 1);
			printf("pointer realloced\n");
			if (ptr2)
				ptr = ptr2;
			else
			{
				free(ptr);
				ptr = NULL;
				return (ptr);
			}
		}
		_strcpy(ptr + ptrlen, buf);
		printf("pointer copied\n");
		if (buf[buflen - 1] == '\n')
		{
			if (buflen == 1 || buf[buflen - 2] != '\\')
				return (ptr);
			ptr[ptrlen + buflen - 2] = '\0';
			buflen -= 2;
			print_prompt2();
		}
		printf("after new line check, start of new loop\n");
		ptrlen += buflen;
	}
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
