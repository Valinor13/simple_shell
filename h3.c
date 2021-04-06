#include "shlib.h"
/**
 * _realloc - reallocate memory
 * @ptr: input pointer for new malloc
 * @olen: the old length malloc'd
 * @nlen: the new length required
 * Return: a pointer to new space
 */

char *_realloc(char *ptr, size_t olen, size_t nlen)
{
	char *nptr;

	nptr = malloc(nlen);
	if (nptr == NULL)
		return (NULL);
	if (nptr)
	{
		_memcpy(nptr, ptr, olen);
		free(ptr);
	}
	return (nptr);
}

size_t get_tkncnt(char *str)
{
	size_t tkncnt = 1;
	char *tknptr;

	tknptr = strtok(str, " ");
	while (tknptr != NULL)
	{
		tkncnt++;
		tknptr = strtok(NULL, " ");
	}
free(str);
return (tkncnt);
}

/**
 * _strdup - copies a string into the heap
 * @str: input string
 * Return: returns a pointer or NULL
 */
char *_strdup(char *str)
{
	char *s;
	int i, x;

	if (str == NULL)
	{
		return (NULL);
	}

	x = 1;

	for (i = 0; str[i] != 00; i++)
	{
		x++;
	}

	s = malloc(x * sizeof(char));

	if (s == NULL)
	{
		return (NULL);
	}

	for (i = 0; str[i] != 00; i++)
	{
		s[i] = str[i];
	}
	s[i] = 00;
return (s);
}
