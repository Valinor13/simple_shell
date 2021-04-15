#include "shlib.h"

/**
 * _strcmp - compare two strings
 * @s1: the first
 * @s2: the second
 * Return: the measure
 */
int _strcmp(char *s1, char *s2)
{
	int y, x;

	for (y = 0; s2[y] != 00 && s1[y] != 00; y++)
	{
		if ((s1[y]) == s2[y])
		{
			continue;
		}
		else if (s1[y] != s2[y])
		{
			break;
		}
	}
x = (s1[y] - s2[y]);
return (x);
}

/**
 * _strlen - return the length of the string
 *@s: the length of the string
 *
 * Return: the length(x)
 */
size_t _strlen(char *s)
{
size_t x;

	x = 0;
	while (*(s + x) != '\0')
	{
		x++;
	}
return (x);
}

/**
 * *_strcpy - copy a string
 * @dest: destination
 * @src: source
 * @ptrlen: starting posi of ptr cpy
 * Return: the copy
 */
char *_strcpy(char *dest, char *src, size_t ptrlen)
{
	int y = 0;

	while (src[y] != 00)
	{
		dest[ptrlen] = src[y];
		ptrlen++, y++;
	}
return (dest);
}

/**
 * handler - handles signals
 * @num: input null arg
 * Return: returns void
 */
void handler(int num)
{
	(void)num;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * _tokenize - space saver
 * @cmd: uh huh
 * @av: program name and arg vector
 * Return: tokenized string
 */
char **_tokenize(char *cmd, char *av[])
{
size_t tkncnt, i;
char *cntptr = NULL, **tknptr = NULL;

	cntptr = _strdup(cmd);
	if (cntptr == NULL)
		perror(av[0]), free(cmd), exit(EXIT_FAILURE);

	tkncnt = get_tkncnt(cntptr, " ");
	tknptr = malloc(sizeof(char *) * tkncnt);

	if (tknptr == NULL)
		perror(av[0]), free(cmd), exit(EXIT_FAILURE);
	tknptr[0] = strtok(cmd, " ");
	if (tknptr[0] == NULL)
	{
		free(tknptr);
		return (NULL);
	}

	for (i = 1; i < tkncnt - 1; i++)
		tknptr[i] = strtok(NULL, " ");

	tknptr[i] = NULL;

return (tknptr);
}
