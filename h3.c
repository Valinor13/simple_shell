#include "shlib.h"
/**
 * _realloc - reallocate memory
 * @olen: the old length malloc'd
 * @nlen: the new length required
 * Return: a pointer to new space
 */

char *_realloc(char *ptr, size_t olen, size_t nlen)
{

char *nptr;

if (nlen == 0)
{
free(ptr);
return (NULL);
}
else if (!ptr)
{
return (malloc(nlen));
}
else if (nlen <= olen)
{
return (ptr);
}
else
{
if (!ptr)
free(ptr);
return (NULL);
}
else if (nlen > olen)
*nptr = malloc(sizeof(nlen));
if (nptr)
{
_memcpy(nptr, ptr, olen);
free(ptr);
}
return nptr;
}
}
