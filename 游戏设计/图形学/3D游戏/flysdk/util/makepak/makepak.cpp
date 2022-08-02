#include <stdio.h>
#include <string.h>

#define FLY_API
#include "../../lib/flypak.h"

class fpkutil : public fly_pak_util
{
protected:
	void update_status(char *filename, unsigned long size)
	{
		printf("%s\n", filename);
	}
};

int main(int argc, char *argv[], char *envp[])
{
	int rslt;

	if(argc!=2)
		return 1;

	fpkutil f;

	if(strstr(argv[1],".fpk"))
		rslt=f.explode(argv[1]);
	else
		rslt=f.implode(argv[1]);

	return rslt?0:1;
}