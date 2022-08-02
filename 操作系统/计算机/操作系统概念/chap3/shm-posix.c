/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * Figure 3.16
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Seventh Edition
 * Copyright John Wiley & Sons - 2005.
 */

#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main()
{
	/* the identifier for the shared memory segment */
	int segment_id;
	/* a pointer to the shared memory segment */
	char* shared_memory;
	/* the size (in bytes) of the shared memory segment */ 
	const int segment_size = 4096;

	/** allocate  a shared memory segment */
	segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

	/** attach the shared memory segment */
	shared_memory = (char *) shmat(segment_id, NULL, 0);
	printf("shared memory segment %d attached at address %p\n", segment_id, shared_memory);

	/** write a message to the shared memory segment   */
	sprintf(shared_memory, "Hi there!");

	/** now print out the string from shared memory */
	printf("*%s*\n", shared_memory);

	/** now detach the shared memory segment */ 
	if ( shmdt(shared_memory) == -1) {
		fprintf(stderr, "Unable to detach\n");
	}

	/** now remove the shared memory segment */
	shmctl(segment_id, IPC_RMID, NULL); 

	return 0;
}
