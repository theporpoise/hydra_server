#include <unistd.h>

void main()
{
	char str[100];

	write(1, "\ntype something: ", 17);

	read(0, str, 100);

	write(1, "\nyou typed :\n", 13);

	write(1, str, 10);

	write(1, "\n", 1);
}
