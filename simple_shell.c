#include "shlib.h"

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
		if (cmd[0] == 00 || cmd[0] == '\n')
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
		i = 1;
		while (i < tkncnt - 1)
		{
			tknptr[i] = strtok(NULL, " ");
			i++;
		}
		free(tknptr);
		free(cmd);
	}
exit(1);
}
