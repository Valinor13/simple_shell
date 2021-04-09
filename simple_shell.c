#include "shlib.h"

/**
 * main - simple shell
 * Return: returns 1 for success -1 for failure
 */
int main(int ac, char *av[], char *env[])
{
	char *cmd = NULL, **tknptr = NULL, *cntptr = NULL, *tmp = NULL;
	size_t tkncnt, i, mode;

	(void)ac;
	(void)env;
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
		if (_strcmp(cmd, "exit\0") == 0)
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
/*		if (_strcmp("./", tknptr[0]) == 0)
*/		tmp = NULL, _exec(tknptr, cmd, tmp, av, env);
/*		else
		{
			tmp = _strcat("./", tknptr[0]);
			tknptr[0] = tmp, _exec(tknptr, cmd, tmp, av, env);
		}
*/		if (tmp != NULL)
			free(tmp);
		free(tknptr), free(cmd);
		if (mode == 0)
			break;
	}
exit(1);
}

/**
 * _exec - executes a command
 * @tknptr: input array of strings
 * @cmd: input cmd pointer
 * @tmp: input tmp pointer
 * Return: returns void
 */
void _exec(char **tknptr, char *cmd, char *tmp, char *av[], char *env[])
{
	pid_t pid = fork();

	if (pid < 0)
		perror("forking failure"), exit(-1);
	wait(NULL);
	if (pid == 0)
	{
		if (execve(tknptr[0], tknptr, env) == -1)
		{
			if (tmp != NULL)
				free(tmp);
			free(cmd), free(tknptr);
			perror(av[0]);
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
