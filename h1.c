#include "shlib.h"
/**
 * read_cmd - takes input and reads to the main file
 * Return: 
 */
char *read_cmd(void)
{
char buf[1024], *ptr = NULL, *ptr2, ptrlen = 0;
int buflen;

while (getline(buf, 1024, stdin))
{
buflen = _strlen(buf);
if (!ptr)
ptr = malloc(sizeof(char) * (buflen + 1))
else
{
ptr2 = _realloc(ptr, ptrlen + buflen +1)
if (ptr2)
ptr = ptr2;
else
{
free(ptr);
ptr = NULL;
}
}
if (!ptr)
{
/*printf equivalent for standard error*/ 
return (NULL);
}
_strcopy(ptr+ptrlen, buf);

if (buf[bufflen - 1] == '\n')
{
if (buflen == 1 || buf[buflen - 2] != '\\')
return ptr;
ptr[ptrlen + buflen - 2] = '\0';
buflen -= 2;
print_prompt2();
}
ptrlen += buflen;
}
return (ptr);
}
