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
		printf("tknptr: %s\n", tknptr);
	}
return (tkncnt);
}
