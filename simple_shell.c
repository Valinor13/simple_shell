#include "shlib.h"

/**
 * main - simple shell
 * Return: returns 1 for success -1 for failure
 */
int main(void)
{
	char *cmd = NULL, **tknptr = NULL, *cntptr = NULL, *tmp = NULL;
	size_t tkncnt, i, mode;

	mode = isatty(STDIN_FILENO);		
	while (1)
	{
		if (mode)
			print_prompt1();
		cmd = read_cmd();
		if (cmd == NULL)
			exit(1);
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue;
		}
		if (_strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break;
		}
		cntptr = _strdup(cmd), tkncnt = get_tkncnt(cntptr);
		tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			free(cmd), exit(1);
		tknptr[0] = strtok(cmd, " ");
		for (i = 1; i < tkncnt - 1; i++)
			tknptr[i] = strtok(NULL, " ");
		tknptr[i] = NULL;
		if (_strcmp("/bin/", tknptr[0]) == 0)
			tmp = NULL, get_exec(tknptr, cmd, tmp);
		else
		{
			tmp = _strcat("/bin/", tknptr[0]);
			tknptr[0] = tmp;
			get_exec(tknptr, cmd, tmp);
		}	
		if (tmp != NULL)
			free(tmp);
		free(tknptr), free(cmd);
		if (mode == 0)
			break;
	}
exit(1);
}

/**
 * get_exec - executes a command
 * @tknptr: input array of strings
 * Return: returns void
 */
void get_exec(char **tknptr, char *cmd, char *tmp)
{
	pid_t pid = fork();

	if (pid < 0)
		perror("forking failure"), exit(-1);
	wait(NULL);
	if (pid == 0)
	{
		if (execve(tknptr[0], tknptr, NULL) == -1)
		{
			if (tmp != NULL)
				free(tmp);
			free(cmd), free(tknptr);
			perror("./hsh");
			exit(1);
		}
	}

return;
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
