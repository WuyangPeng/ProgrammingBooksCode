
#include <stdio.h>
#include <stdlib.h>

int main()
{
	putenv("Arch=stuff\n");
	printf("Arch=%s\n", getenv("Arch"));

	printf("putenv(): %d\n", putenv("Arch"));
	printf("Arch=%s\n", getenv("Arch"));

	printf("putenv(): %d\n", putenv("Arch"));
	printf("Arch=%s\n", getenv("Arch"));

	printf("putenv(): %d\n", putenv("Arch="));
	printf("Arch=%s\n", getenv("Arch"));

	printf("putenv(): %d\n", putenv("Arch="));
	printf("Arch=%s\n", getenv("Arch"));

	return 0;
}
