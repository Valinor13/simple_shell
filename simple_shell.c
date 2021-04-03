#include "shlib.h"

/**
 * main - simple shell
 * @argc: arg count
 * @argv: arg list
 * Return: returns 1 for success -1 for failure
 */
int main(int argc, char **argv)
{
	char *cmd;

	(void)argv;
	(void)argc;
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
		_puts(cmd);
		free(cmd);
	}
exit(1);
}
