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
	char *nptr = NULL;

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

/**
 * get_tkncnt - gets the count of words in string
 * @str: input string
 * @delim: token delimitter
 * Return: returns number of words
 */
size_t get_tkncnt(char *str, char *delim)
{
	size_t tkncnt = 1;
	char *tknptr = NULL;

	tknptr = strtok(str, delim);
	while (tknptr != NULL)
	{
		tkncnt++;
		tknptr = strtok(NULL, delim);
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
	char *s = NULL;
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

/**
 * _strcat - concatenates 2 strings
 * @dest: first string
 * @src: second string
 * Return: returns cat string
 */
char *_strcat(char *dest, char *src)
{
	int i, x, z;
	char *p = NULL;

	x = _strlen(dest) + _strlen(src);
	p = malloc(sizeof(char) * x + 1);
	if (p == NULL)
		return (NULL);
	for (i = 0; dest[i] != '\0'; i++)
	{
		p[i] = dest[i];
	}
	for (z = 0; i <= x; i++, z++)
	{
		p[i] = src[z];
	}
return (p);
}

/**
 * *_strcpyr - copy a string
 * @dest: destination
 * @src: source
 * @ptrlen: starting posi of ptr cpy
 * Return: the copy
 */
char *_strcpyr(char *dest, char *src, size_t ptrlen)
{
	int y = 0;

	while (src[ptrlen] != 00)
	{
		dest[y] = src[ptrlen];
		ptrlen++, y++;
	}
	dest[y] = 00;
return (dest);
}

