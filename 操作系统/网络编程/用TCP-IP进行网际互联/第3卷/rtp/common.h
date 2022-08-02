/* common.h - min, max */

#ifndef COMMON_H
#define COMMON_H
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef char           bool;

#define TRUE	  1
#define FALSE	  0
#define OK	  0
#define ERROR	 -1
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#endif
