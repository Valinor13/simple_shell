#include "shlib.h"

/**
 *
 *
 *
 */
int main(int argc, char **argv)
{
	char *cmd;

	while (1)
	{
		print_prompt1();
		cmd = read_cmd();
		if (cmd == NULL)
			exit(EXIT_SUCCESS);
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
		_printf("%s\n", cmd);
		free(cmd);
	}
exit(EXIT_SUCCESS);
}
