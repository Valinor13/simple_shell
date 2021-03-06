#include "shlib.h"
/**
 * read_line - takes input and reads to the main file
 * Return:  returns a character string of the command
 */
char *read_line(void)
{
	char *buf = NULL;
	size_t bsz = 0;
	ssize_t buflen;

	while ((buflen = getline(&buf, &bsz, stdin)) != -1)
	{
		if (buf[buflen - 1] == '\n')
			buf[buflen - 1] = 00;
		return (buf);
	}
free(buf), buf = NULL;
return (buf);
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

/**
 * _charcmp - compares characters looking for slash
 * @tknptr: tknptr 0 looking for slash
 * @slash: /
 * Return: returns size_t 0 for success 1 for failure
 */
size_t _charcmp(char *tknptr, char slash)
{
	int i = 0;

	while (tknptr[i])
	{
		if (tknptr[i] == slash)
			return (0);
		i++;
	}
return (1);
}

/**
 * get_path - turns input of tkn path into string
 * @pthtok: tokenized 2d array of the path
 * @tknptr: tokenized array of the user's input
 * @av: program name in arg vector
 * @cmd: original getline pointer
 * @tpth: temp path
 * Return: new tknptr, with stat checked functionality
 */
char *get_path(char **pthtok, char **tknptr, char **av, char *cmd, char *tpth)
{
	struct stat statvar;
	int i;
	char *tmp = NULL;

	tmp = tknptr[0];
	if (tmp == NULL)
		return (pthtok[0]);
	for (i = 0; pthtok[i] != NULL; i++)
	{
		pthtok[i] = _strcat(pthtok[i], "/");
		/*appends tkn input w/ '/' to run stat*/
		if (pthtok[i] == NULL)
			return (tmp);
		tknptr[0] = _strcat(pthtok[i], tknptr[0]);
		/*Read with '/', append new string with user command*/
		free(pthtok[i]);
		if (tknptr[0] == NULL)
			return (tmp);
		if (stat(tknptr[0], &statvar) == 0)
		{
			if (access(tknptr[0], X_OK) == -1)
			{
				free(tknptr[0]), free(tknptr), free(cmd), free(tpth);
				free(pthtok), perror(av[0]), exit(126);
			}
			break;
		}
		/*stat(0) == success, we break. If it fails, we try again*/
		free(tknptr[0]);
		tknptr[0] = tmp;
	}
return (tknptr[0]);
}
