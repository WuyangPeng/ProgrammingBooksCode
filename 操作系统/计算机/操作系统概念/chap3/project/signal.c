#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define BUFFER_SIZE 50

static char buffer[BUFFER_SIZE];

/* the signal handler function */
void handle_SIGINT() {
	write(STDOUT_FILENO,buffer,strlen(buffer));

	exit(0);
}

int main(int argc, char *argv[]) 
{
	/* set up the signal handler */
	struct sigaction handler;
	handler.sa_handler = handle_SIGINT; 
	sigaction(SIGINT, &handler, NULL);

	strcpy(buffer,"Caught <ctrl><c>\n");

	/* wait for <control> <C> */
	while (1)
		;

	return 0;
}

