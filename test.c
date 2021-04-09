#include "shlib.h"

int main(void)
{
	write(1, "/usr/bin/env\n\0", 14);
return (0);
}
