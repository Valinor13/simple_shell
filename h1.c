#include "shlib.h"
/**
 * read_line - takes input and reads to the main file
 * @line_cnt: Exactly what it says it is
 * Return:  returns a character string of the command
 */
char *read_line(int *line_cnt)
{
	char *buf = NULL, *cmd = NULL;
	size_t bsz = 1024, ptrlen = 0;
	ssize_t buflen;

	while ((buflen = getline(&buf, &bsz, stdin)) != -1)
	{
	  /*cmd is user input after has checked for slashes, other stuff*/
		if (cmd == NULL)
		{
			cmd = malloc(sizeof(char) * buflen + 1);
			if (cmd == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
		else if (cmd != NULL)
		{
			cmd = _realloc(cmd, ptrlen, buflen + ptrlen);
			if (cmd == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
		/*copy dest to source starting at ptrlen*/
		_strcpy(cmd, buf, ptrlen);
		if (buflen == 1 || buf[buflen - 2] != '\\')
		{
			free(buf);
			cmd[ptrlen + buflen - 1] = 00;
			return (cmd);
		}
		buflen -= 2, cmd[ptrlen + buflen] = 00, _prompt2();
		*line_cnt += 1, ptrlen += buflen;
	}
free(buf);
return (cmd);
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

