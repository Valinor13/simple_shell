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

	nptr = malloc(sizeof(nlen));
	if (nptr == NULL)
		return (NULL);
	if (nptr)
	{
		_memcpy(nptr, ptr, olen);
		free(ptr);
	}
	return (nptr);
}
