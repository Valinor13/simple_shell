#include "shlib.h"

/**
 * main - simple shell
 * Return: returns 1 for success -1 for failure
 */
int main(int ac, char *av[], char *env[])
{
	char *cmd = NULL, **tknptr = NULL, *cntptr = NULL;
	size_t tkncnt, i, mode;

	(void)ac;
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
		cntptr = _strdup(cmd), tkncnt = get_tkncnt(cntptr, " ");
		tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			free(cmd), exit(1);
		tknptr[0] = strtok(cmd, " ");
		for (i = 1; i < tkncnt - 1; i++)
			tknptr[i] = strtok(NULL, " ");
		tknptr[i] = NULL;
		_exec(tknptr, cmd, av, env);
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
void _exec(char **tknptr, char *cmd, char *av[], char *env[])
{
	pid_t pid = fork();
	size_t i, pthcnt, len;
	char **pthtok, *tmpth = NULL, *npth = NULL;

	for (i = 0; env[i]; i++)
	{
		if (_strcmp("PATH=", env[i]) == 0)
			break;
	}
	len = _strlen(env[i]);
	tmpth = malloc(sizeof(char) * len + 1);
	tmpth = _strcpyr(tmpth, env[i], 5);
	tmpth = _gwd(&tmpth);
	npth = _strdup(tmpth), pthcnt = get_tkncnt(npth, ":");
	pthtok = malloc(sizeof(char *) * pthcnt);
	if (pthtok == NULL)
		free(tmpth), free(cmd), free(tknptr), exit(-1);
	pthtok[0] = strtok(tmpth, ":");
	for (i = 1; i < (pthcnt - 1); i++)
		pthtok[i] = strtok(NULL, ":");
	pthtok[i] = NULL;
	if (pid < 0)
		perror("forking failure"), exit(-1);
	if (pid == 0)
	{
		if (execve(tknptr[0], tknptr, env) == -1)
		{
			tknptr[0] = get_path(pthtok, tknptr);
			if (execve(tknptr[0], tknptr, env) == -1)
			{
				free(tmpth), free(pthtok);
				free(tknptr), free(cmd);
				perror(av[0]), exit(1);
			}
		}
	}
	wait(NULL);
free(tmpth), free(pthtok);
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

char *_gwd(char **tmpth)
{
	size_t i, tlen, clen, nlen, n = 100;
	char *cwd = NULL, *npth = NULL, *ntmp = NULL;

	ntmp = _strdup(*tmpth);
	tlen = _strlen(*tmpth);
	cwd = malloc(n);
	if (cwd == NULL)
	{
		perror("working directory is NULL");
		return (*tmpth);
	}
	while (getcwd(cwd, n) == NULL)
	{
		n *= 2, free(cwd), cwd = malloc(n);
		if (cwd == NULL)
		{
			perror("working directory is NULL");
			return (*tmpth);
		}
	}
	clen = _strlen(cwd);
	if (*tmpth[0] == ':')
	{
		npth = _strcat(cwd, *tmpth);
		free(cwd), free(*tmpth), free(ntmp);
		return (npth);
	}
	for (i = 0; *tmpth[i] == 00; i++)
	{
		if (*tmpth[i] == ':' && *tmpth[i + 1] == ':')
		{
			ntmp += (i + 1);
			*tmpth = _realloc(*tmpth, i, tlen + clen + 1);
			npth = _strcpy(*tmpth, cwd, (i + 1));
			nlen = _strlen(npth);
			npth = _strcpy(npth, ntmp, (nlen + 1));
			free(ntmp), free(cwd), free(*tmpth);
			return (npth);
		}
	}
	if (*tmpth[tlen] == ':')
	{
		npth = _strcat(*tmpth, cwd);
		free(cwd), free(*tmpth), free(ntmp);
		return (npth);
	}
free(cwd), free(ntmp);
return (*tmpth);
}

