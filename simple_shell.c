#include "shlib.h"

/**
 * handler - Takes user input for ctrl+c
 * @num: voided
 * Return: the correct intended response to CTRL+C 
 */
void handler(int num)
{
(void)num;
write(STDOUT_FILENO, "\n$ ". 3);
}

/**
 * main - simple shell
 * @ac: voided, but necessary argument
 * @av: argument vectors
 * @env: environment variable
 * Return: returns 1 for success -1 for failure
 */
int main(int ac, char *av[], char *env[])
{
	char *cmd = NULL, **tknptr = NULL, *cntptr = NULL;
	size_t tkncnt, i, mode;
	int count = 0, *line_cnt = &count;

	(void)ac;
	signal(SIGINT, handler);
	mode = isatty(STDIN_FILENO);
	/*isatty answers if input is waiting, terminal up*/
	while (1)
	{
		count++;
		if (mode)
		{
			_prompt1();
		}
		cmd = read_line(line_cnt);
		/*effectively getline, including line count*/
		if (cmd == NULL)
		{
			if (mode)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue;
		}
/*		if (_strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break;
		}
*/		cntptr = _strdup(cmd);
		/*To clarify the contents of cmd before we tokenize it*/
		if (cntptr == NULL)
			perror(av[0]), free(cmd), exit(EXIT_FAILURE);
		tkncnt = get_tkncnt(cntptr, " "), tknptr = malloc(sizeof(char *) * tkncnt);
		/*get_tkncnt fills tkncnt with number of words, memory allocated for 2d array*/
		if (tknptr == NULL)
			perror(av[0]), free(cmd), exit(EXIT_FAILURE);
		tknptr[0] = strtok(cmd, " ");
		/*tknptr is fed a series of strings, treating them as entries in an array*/
		for (i = 1; i < tkncnt - 1; i++)
		  /*strtok converts the delimiter arg into first arg, tokenizing tknptr, ending in NULL*/
			tknptr[i] = strtok(NULL, " ");
		if (_strcmp(tknptr[0], "exit") == 0)
		{
			/*strcmp success on 0*/
			free(cmd), free(tknptr);
			break;
		}
		tknptr[i] = NULL, _exec(tknptr, cmd, av, env, line_cnt), free(tknptr), free(cmd);
	}
exit(EXIT_SUCCESS);
}

/**
 * _exec - executes a command
 * @tknptr: input array of strings
 * @cmd: input cmd pointer
 * @av: argument vectors, volume
 * @env: the environment
 * @line_cnt: Exactly what it says
 * Return: returns void
 */
void _exec(char **tknptr, char *cmd, char *av[], char *env[], int *line_cnt)
{
	pid_t pid = fork();

	if (pid < 0)
		perror(av[0]), exit(EXIT_FAILURE);
	if (pid == 0)
	{
		tknptr[0] = get_tknptr(env, av, tknptr, cmd);
		if (execve(tknptr[0], tknptr, env) == -1)
		{
			_pterror(av, tknptr, line_cnt);
			free(tknptr), free(cmd),  exit(EXIT_FAILURE);
		}
	}
	/*Child path will either always find the path or not*/
	/*Parent process will wait until child is NULL value, then return*/
	wait(NULL);
return;
}
/**
 * get_path - turns input of tkn path into string
 * @pthtok: tokenized 2d array of the path
 * @tknptr: tokenized array of the user's input
 * Return: new tknptr, with stat checked functionality
 */
char *get_path(char **pthtok, char **tknptr)
{
	struct stat statvar;
	int i;
	char *tmp = NULL;

	tmp = tknptr[0];
	for (i = 0; pthtok[i] != NULL; i++)
	{
		pthtok[i] = _strcat(pthtok[i], "/");
		/*appends tkn input w/ '/' to run stat*/
		if (pthtok[i] == NULL)
			return (tknptr[0]);
		tknptr[0] = _strcat(pthtok[i], tknptr[0]);
		/*Read with '/', append new string with user command*/
		free(pthtok[i]);
		if (tknptr[0] == NULL)
			return (tknptr[0]);
		if (stat(tknptr[0], &statvar) == 0)
			break;
		/*stat(0) == success, we break. If it fails, we try again*/
		free(tknptr[0]);
		tknptr[0] = tmp;
	}
return (tknptr[0]);
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
		/*If not enough space is allocated or the cwd is NULL*/
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
		if (pth[i] == ':' && pth[i + 1] == ':')
		{
			tpth = malloc(plen - i);
			if (tpth == NULL)
				return (pth);
		  /*_realloc prints *pth up to point i, then cwd, then path @i +1*/
		  /*in between the ::*/
			tpth = _strcpyr(tpth, pth, i + 1), npth = _realloc(pth, i + 1, plen + clen + 1);
			npth = _strcpy(npth, cwd, (i + 1)), npth = _strcpy(npth, tpth, (i + clen + 1));
			npth[plen + clen] = 00, free(tpth), free(cwd);
			return (npth);
		}
	}
	if (pth[plen - 1] == ':')
	{
	  /*If : is at the end, we place the cwd at the end*/
		npth = _strcat(pth, cwd), free(cwd), free(pth), free(tpth);
		return (npth);
	}
free(cwd), free(tpth);
return (pth);
}

/**
 * get_tknptr - gets the tknptr with path for execution
 * @env: environment path string
 * Return: returns tknptr with path or exits with failure
 */
char *get_tknptr(char *env[], char *av[], char *tknptr[], char *cmd)
{
	size_t i, pthcnt, len;
	char **pthtok = NULL, *tmpth = NULL, *npth = NULL;

		for (i = 0; env[i]; i++)
		{
		/*When the function succesfully finds  PATH= in the env*/
			if (_strcmp("PATH=", env[i]) == 0)
				break;
		}
		if (env[i] != NULL && _charcmp(tknptr[0], '/') != 0)
		{
			/*if we find PATH:*/
			len = _strlen(env[i]);
			tmpth = malloc(sizeof(char) * len - 4);
			if (tmpth == NULL)
			/*tmpth = temporary path*/
			/*perror prints num of sys call associated w/ fail*/
				perror(av[0]), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			/*copies "PATH=..." into beginning of string at array point 5*/
			tmpth = _strcpyr(tmpth, env[i], 5);
			/*Adds the current working directory to the path, if necessary*/
			tmpth = _gwd(tmpth);
			/*npth = new path*/
			npth = _strdup(tmpth);
			if (npth == NULL)
				perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			pthcnt = get_tkncnt(npth, ":");
			pthtok = malloc(sizeof(char *) * pthcnt);
			if (pthtok == NULL)
				perror(av[0]), free(tmpth), free(cmd), free(tknptr), exit(EXIT_FAILURE);
			pthtok[0] = strtok(tmpth, ":");
			for (i = 1; i < (pthcnt - 1); i++)
			/*strtok convert delimiter arg into first arg, tokenizes tknptr, end when finds 00*/
				pthtok[i] = strtok(NULL, ":");
			/*Append a NULL pointer to end of tokens*/
			pthtok[i] = NULL, tknptr[0] = get_path(pthtok, tknptr);
			free(tmpth), free(pthtok);
		}
	return (tknptr[0]);
}

