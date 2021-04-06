#include "shlib.h"

extern char **environ;

/**
 * main - simple shell
 * @argc: arg count
 * @argv: arg list
 * Return: returns 1 for success -1 for failure
 */
int main(void)
{
	char *cmd = NULL, **tknptr = NULL, *cntptr;
	size_t tkncnt, i;

	while (1)
	{
		cntptr = NULL;
		print_prompt1();
		cmd = read_cmd();
		if (cmd == NULL)
			exit(1);
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue;
		}
		if (_strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			break;
		}
		cntptr = _strdup(cmd);
		tkncnt = get_tkncnt(cntptr);
		tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			exit(1);
		tknptr[0] = strtok(cmd, " ");
		for (i = 1; i < tkncnt - 1; i++)
			tknptr[i] = strtok(NULL, " ");
		get_exec(tknptr);
		free(tknptr);
		free(cmd);
	}
exit(1);
}

void get_exec( char **tknptr)
{
	char *env_args[] = {"PATH=/bin", "USER=hshuser", NULL};
	pid_t pid = fork();

	if (pid != 0)
	{
		while (wait(NULL) != -1)
			;
	}
	if (pid == 0)
	{
		if (execve("/bin/ls", tknptr, env_args) == -1)
		{
			perror("exec failure");
			exit(-1);
		}
	}

return;
}
