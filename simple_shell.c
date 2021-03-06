#include "shlib.h"

/**
 * main - simple shell
 * @ac: voided, but necessary argument
 * @av: argument vectors
 * @env: environment variable
 * Return: returns 1 for success -1 for failure
 */
int main(int ac, char *av[], char *env[])
{
	char *cmd = NULL, **tknptr = NULL;
	size_t mode;
	int count = 0, *ln_cnt = &count, ex_stat = 0, esig;

	(void)ac, (void)env;
	signal(SIGINT, handler), mode = isatty(STDIN_FILENO);
	while (1)
	{
		count++;
		if (mode)
			_prompt1();
		cmd = read_line();
		if (cmd == NULL)
		{
			if (mode)
				write(STDOUT_FILENO, "\n", 1);
			exit(ex_stat);
		}
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue;
		}
		tknptr = _tokenize(cmd, av);
		if (tknptr == NULL || tknptr[0] == NULL)
		{
			free(cmd), free(tknptr);
			continue;
		}
		esig = bltcheck(tknptr, cmd, ex_stat);
		if (esig == 2)
			break;
		if (esig == 1)
			continue;
		ex_stat = _exec(tknptr, cmd, av, ln_cnt, ex_stat);
		free(tknptr), tknptr = NULL, free(cmd), cmd = NULL;
	}
	exit(ex_stat);
}

/**
 * _exec - executes a command
 * @tknptr: input array of strings
 * @cmd: input cmd pointer
 * @av: argument vectors, volume
 * @ln_cnt: Exactly what it says
 * @ex_stat: exit status
 * Return: returns void
 */
int _exec(char **tknptr, char *cmd, char *av[], int *ln_cnt, int ex_stat)
{
	struct stat statvar;
	pid_t pid = fork();
	int status;

	if (pid < 0)
		perror(av[0]), exit(EXIT_FAILURE);
	if (pid == 0)
	{
		tknptr[0] = get_tknptr(av, tknptr, cmd);
		if (stat(tknptr[0], &statvar) == -1)
		{
			_pterror(av, tknptr, ln_cnt);
			free(tknptr), free(cmd),  exit(127);
		}
		if (access(tknptr[0], X_OK) == -1)
		{
			free(tknptr), free(cmd);
			perror(av[0]), exit(126);
		}
		if (execve(tknptr[0], tknptr, environ) == -1)
			free(cmd), free(tknptr), perror(av[0]), exit(1);
	}
	/*Child path will either always find the path or not*/
	/*Parent process will wait until child is NULL value, then return*/
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ex_stat = WEXITSTATUS(status);
	else
		ex_stat = 0;
	return (ex_stat);
}

/**
 * _gwd - Appends working directory to the path if necessary
 * @pth: the PATH
 * Return: a pointer to the PATH
 */
char *_gwd(char *pth)
{
	size_t i, plen, clen, cmac = 100;
	char *cwd = NULL, *npth = NULL, *tpth = NULL;

	plen = _strlen(pth), cwd = malloc(cmac);
	while (getcwd(cwd, cmac) == NULL)
	{
	  /*If not enough memory has been allocated, double and try again*/
		cmac *= 2, free(cwd), cwd = malloc(cmac);
		if (cwd == NULL)
			return (pth);
	}
	clen = _strlen(cwd);
	if (pth[0] == ':')
	{
		npth = _strcat(cwd, pth), free(cwd), free(pth);
		return (npth);
	}
	for (i = 0; pth[i] != 00; i++)
	{
	/* _realloc pth < i then cwd, then pth between :: at i + 1 */
		if (pth[i] == ':' && pth[i + 1] == ':')
		{
			tpth = malloc(plen - i);
			if (tpth == NULL)
				return (pth);
			tpth = _strcpyr(tpth, pth, i + 1);
			npth = _realloc(pth, i + 1, plen + clen + 1);
			npth = _strcpy(npth, cwd, (i + 1));
			npth = _strcpy(npth, tpth, (i + clen + 1));
			npth[plen + clen] = 00, free(tpth), free(cwd);
			return (npth);
		}
	}
	if (pth[plen - 1] == ':')
	{
		npth = _strcat(pth, cwd), free(cwd), free(pth), free(tpth);
		return (npth);
	}
free(cwd), free(tpth);
return (pth);
}

/**
 * get_tknptr - gets the tknptr with path for execution
 * @av: program name in arg vector
 * @tknptr: path and command plus args
 * @cmd: original input string
 * Return: returns tknptr with path or exits with failure
 */
char *get_tknptr(char *av[], char *tknptr[], char *cmd)
{
	size_t i, pthcnt, len;
	char **pthtok = NULL, *tmpth = NULL, *npth = NULL;

		for (i = 0; environ[i]; i++)
		{
		/*When the function succesfully finds  PATH= in the env*/
			if (_strcmp2("PATH=", environ[i]) == 0)
				break;
		}
		if (environ[i] != NULL && _charcmp(tknptr[0], '/') != 0)
		{
			/*if we find PATH:*/
			len = _strlen(environ[i]), tmpth = malloc(sizeof(char) * len - 4);
			if (tmpth == NULL)
			/*tmpth = temporary path*/
			/*perror prints num of sys call associated w/ fail*/
				perror(av[0]), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			/*copies "PATH=..." into beginning of string at array point 5*/
			tmpth = _strcpyr(tmpth, environ[i], 5);
			/*Adds the current working directory to the path, if necessary*/
			tmpth = _gwd(tmpth), npth = _strdup(tmpth);
			if (npth == NULL)
				perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			pthcnt = get_tkncnt(npth, ":"), pthtok = malloc(sizeof(char *) * pthcnt);
			if (pthtok == NULL)
				perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			pthtok[0] = strtok(tmpth, ":");
			if ((pthtok[0][0] != ':' && pthtok[0][0] != '/') || pthtok[0] == NULL)
			{
				free(pthtok), free(tmpth);
				return (tknptr[0]);
			}
			for (i = 1; i < (pthcnt - 1); i++)
			/*strtok convert delim arg into first arg, tokenizes tknptr, end at 00*/
				pthtok[i] = strtok(NULL, ":");
			/*Append a NULL pointer to end of tokens*/
			pthtok[i] = NULL, tknptr[0] = get_path(pthtok, tknptr, av, cmd, tmpth);
			free(tmpth), free(pthtok);
		}
	return (tknptr[0]);
}

/**
 * bltcheck - checks built in commands
 * @cmd: the input
 * @tknptr: tokenized string
 * @ex_stat: exit status
 * Return: esig
*/

int bltcheck(char **tknptr, char *cmd, int ex_stat)
{
pid_t pidy = getpid();
int esig = 0, i = 0, len, *pidyptr = &pidy, *ex_st = &ex_stat;
char *tmpo;

if (_strcmp(tknptr[0], "exit") == 0)
esig = 2;
else if (_strcmp(tknptr[0], "env") == 0)
{
for (i = 0; environ[i] != NULL; i++)
{
len = _strlen(environ[i]), esig = 1;
write(STDOUT_FILENO, environ[i], len), write(STDOUT_FILENO, "\n", 1);
}
}
else if (_strcmp(tknptr[0], "echo") == 0)
{
if (tknptr[1])
{
if (_strcmp(tknptr[1], "$$") == 0)
{
esig = 1, tmpo = printint(pidyptr), len = _strlen(tmpo);
write(STDOUT_FILENO, tmpo, len), write(STDOUT_FILENO, "\n", 1);
free(tmpo);
}
else if (_strcmp(tknptr[1], "$?") == 0)
{
esig = 1, tmpo = printint(ex_st), len = _strlen(tmpo);
write(STDOUT_FILENO, tmpo, len), write(STDOUT_FILENO, "\n", 1);
free(tmpo);
}
}
}
if (esig == 1 || esig == 2)
{
free(cmd), free(tknptr), cmd = NULL, tknptr = NULL;
}
return (esig);
}
