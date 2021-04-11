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
	signal(SIGINT, SIG_IGN);
	mode = isatty(STDIN_FILENO);
	while (1)
	{
		count++;
		if (mode)
		{
			_prompt1();
		}
		cmd = read_line(line_cnt);
		if (cmd == NULL)
		{
			if (mode == 0)
				exit(0);
		}
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
		cntptr = _strdup(cmd);
		if (cntptr == NULL)
			perror(av[0]), free(cmd), exit(1);
		tkncnt = get_tkncnt(cntptr, " "), tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			perror(av[0]), free(cmd), exit(1);
		tknptr[0] = strtok(cmd, " ");
		for (i = 1; i < tkncnt - 1; i++)
			tknptr[i] = strtok(NULL, " ");
		tknptr[i] = NULL, _exec(tknptr, cmd, av, env, line_cnt), free(tknptr), free(cmd);
		if (mode == 0)
			break;
	}
exit(errno);
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
		perror(av[0]), exit(1);
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
				if (tmpth == NULL)
					perror(av[0]), free(cmd), free(tknptr), exit(1);
				tmpth = _strcpyr(tmpth, env[i], 5);
				tmpth = _gwd(&tmpth);
				npth = _strdup(tmpth);
				if (npth == NULL)
					perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(1);
				pthcnt = get_tkncnt(npth, ":");
				pthtok = malloc(sizeof(char *) * pthcnt);
				if (pthtok == NULL)
					perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(1);
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
		if (pthtok[i] == NULL)
			return (tknptr[0]);
		tknptr[0] = _strcat(pthtok[i], tknptr[0]);
		free(pthtok[i]);
		if (tknptr[0] == NULL)
			return (tknptr[0]);
		if (stat(tknptr[0], &statvar) == 0)
			break;
		free(tknptr[0]);
		tknptr[0] = tmp;
	}
return (tknptr[0]);
}

char *_gwd(char **pth)
{
	size_t i, plen, clen, nlen, cmac = 100;
	char *cwd = NULL, *npth = NULL, *tpth = NULL;

	tpth = _strdup(*pth), plen = _strlen(*pth), cwd = malloc(cmac);
	while (getcwd(cwd, cmac) == NULL)
	{
		cmac *= 2, free(cwd), cwd = malloc(cmac);
		if (cwd == NULL)
			return (*pth);
	}
	clen = _strlen(cwd);
	if (*pth[0] == ':')
	{
		npth = _strcat(cwd, *pth), free(cwd), free(*pth), free(tpth);
		return (npth);
	}
	for (i = 0; *pth[i] == 00; i++)
	{
		if (*pth[i] == ':' && *pth[i + 1] == ':')
		{
			tpth += (i + 1), *pth = _realloc(*pth, i, plen + clen + 1);
			*pth = _strcpy(*pth, cwd, (i + 1)), nlen = _strlen(*pth);
			*pth = _strcpy(*pth, tpth, (nlen + 1)), free(tpth), free(cwd);
			return (*pth);
		}
	}
	if (*pth[plen] == ':')
	{
		npth = _strcat(*pth, cwd), free(cwd), free(*pth), free(tpth);
		return (npth);
	}
free(cwd), free(tpth);
return (*pth);
}

