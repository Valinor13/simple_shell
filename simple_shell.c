#include "shlib.h"

/**
 * main - simple shell
 * Return: returns 1 for success -1 for failure
 */
int main(int ac, char *av[], char *env[])
{
	char *cmd = NULL, **tknptr = NULL, *cntptr = NULL;
	size_t tkncnt, i, mode;
	int count = 0, *line_cnt = &count;

	(void)ac;
	mode = isatty(STDIN_FILENO);
	while (1)
	{
		count++;
		if (mode)
		{
			print_prompt1();
		}
		cmd = read_cmd(line_cnt);
		if (cmd == NULL)
			exit(-1);
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
		cntptr = _strdup(cmd), tkncnt = get_tkncnt(cntptr, " ");
		tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			free(cmd), perror("command tokenization failure"), exit(-1);
		tknptr[0] = strtok(cmd, " ");
		for (i = 1; i < tkncnt - 1; i++)
			tknptr[i] = strtok(NULL, " ");
		tknptr[i] = NULL;
		_exec(tknptr, cmd, av, env, line_cnt);
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
void _exec(char **tknptr, char *cmd, char *av[], char *env[], int *line_cnt)
{
	pid_t pid = fork();
	size_t i, pthcnt, len;
	char **pthtok, *tmpth = NULL, *npth = NULL;

	if (pid < 0)
		perror("forking failure"), exit(-1);
	if (pid == 0)
	{
		if (execve(tknptr[0], tknptr, env) == -1)
		{
			for (i = 0; env[i]; i++)
			{
				if (_strcmp("PATH=", env[i]) == 0)
					break;
			}
			if (env[i] != NULL)
			{
				len = _strlen(env[i]);
				tmpth = malloc(sizeof(char) * len + 1);
				tmpth = _strcpyr(tmpth, env[i], 5);
				tmpth = _gwd(&tmpth);
				npth = _strdup(tmpth), pthcnt = get_tkncnt(npth, ":");
				pthtok = malloc(sizeof(char *) * pthcnt);
				if (pthtok == NULL)
					perror("path failure"), free(tmpth), free(cmd), free(tknptr), exit(-1);
				pthtok[0] = strtok(tmpth, ":");
				for (i = 1; i < (pthcnt - 1); i++)
					pthtok[i] = strtok(NULL, ":");
				pthtok[i] = NULL;
				tknptr[0] = get_path(pthtok, tknptr);
			}
			if (execve(tknptr[0], tknptr, env) == -1)
			{
				_pterror(av, tknptr, line_cnt), free(tmpth), free(pthtok);
				free(tknptr), free(cmd),  exit(1);
			}
		}
	}
	wait(NULL);
return;
}

char *get_path(char **pthtok, char **tknptr)
{
	struct stat statvar;
	int i;
	char *tmp;

	tmp = tknptr[0];
	for (i = 0; pthtok[i] != NULL; i++)
	{
		pthtok[i] = _strcat(pthtok[i], "/");
		tknptr[0] = _strcat(pthtok[i], tknptr[0]), free(pthtok[i]);
		if (stat(tknptr[0], &statvar) == 0)
			break;
		free(tknptr[0]), tknptr[0] = tmp;
	}
return (tknptr[0]);
}

char *_gwd(char **p)
{
	size_t i, x, y, z, xx = 100;
	char *c = NULL, *n = NULL, *t = NULL;

	t = _strdup(*p), x = _strlen(*p), c = malloc(xx);
	if (c == NULL)
	{
		perror("working directory is NULL");
		exit(-1);
	}
	while (getcwd(c, xx) == NULL)
	{
		xx *= 2, free(c), c = malloc(xx);
		if (c == NULL)
		{
			perror("working directory is NULL");
			exit(-1);
		}
	}
	y = _strlen(c);
	if (*p[0] == ':')
	{
		n = _strcat(c, *p), free(c), free(*p), free(t);
		return (n);
	}
	for (i = 0; *p[i] == 00; i++)
	{
		if (*p[i] == ':' && *p[i + 1] == ':')
		{
			t += (i + 1), *p = _realloc(*p, i, x + y + 1), n = _strcpy(*p, c, (i + 1));
			z = _strlen(n), n = _strcpy(n, t, (z + 1)), free(t), free(c), free(*p);
			return (n);
		}
	}
	if (*p[x] == ':')
	{
		n = _strcat(*p, c), free(c), free(*p), free(t);
		return (n);
	}
free(c), free(t);
return (*p);
}

