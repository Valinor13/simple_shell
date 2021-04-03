#include "shlib.h"
/**
 * read_cmd - takes input and reads to the main file
 * Return:  returns a character string of the command
 */
char *read_cmd(void)
{
	char *buf, *ptr = NULL, *ptr2, ptrlen = 0;
	size_t buflen, get_num, bsz = 1024;
	
	while ((get_num = getline(&buf, &bsz, stdin)) > 0)
	{
		buflen = _strlen(buf);
		if (!ptr)
			ptr = malloc(sizeof(char) * (buflen + 1));
		else
		{
			ptr2 = _realloc(ptr, buflen, ptrlen + buflen + 1);
			if (ptr2)
				ptr = ptr2;
			else
			{
				free(ptr);
				ptr = NULL;
				return (ptr);
			}
		}
		_strcpy(ptr+ptrlen, buf);
		if (buf[buflen - 1] == '\n')
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
