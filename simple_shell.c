#include "shlib.h"

/**
 * main - simple shell
 * @argc: arg count
 * @argv: arg list
 * Return: returns 1 for success -1 for failure
 */
int main(void)
{
	char *cmd, **tknptr, *tmp, *cntptr;
	size_t  i = 1, tkncnt;

	while (1)
	{
		print_prompt1();
		cmd = read_cmd();
		if (cmd == NULL)
			exit(1);
		if (cmd[0] == 00 || _strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}
		if (_strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			break;
		}
		cntptr = cmd;
		printf("%s\n", cmd);
		tkncnt = get_tkncnt(cntptr);
		tknptr = malloc(sizeof(char *) * tkncnt);
		if (tknptr == NULL)
			exit(1);
		tmp = strtok(cmd, " ");
		tknptr[0] = tmp;
		while (tmp != NULL)
		{
			tmp = strtok(NULL, " ");
			tknptr[i] = tmp;
			printf("tknptr: %s\n", tmp);
			i++;
		}
		for (i = 0; tknptr[i] != NULL; i++)
			printf("%s ", tknptr[i]);
		free(tknptr);
		free(cmd);
	}
exit(1);
}
