/* x_conf.c - x_conf */

#include <conf.h>
#include <kernel.h>
#include <network.h>

extern	char	vers[];

/*------------------------------------------------------------------------
 *  x_conf  -  Print info about the system configuration
 *------------------------------------------------------------------------
 */
COMMAND	x_conf(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	char	str[128];
	char	name[80];
	char	*FindName();
	int	i;

	sprintf(str,"Identification\n");
	write(stdout, str, strlen(str));

	sprintf(str,"    Xinu version:     %s\n",vers);
	write(stdout, str, strlen(str));

#ifdef notyet
	sprintf(str,"    Ethernet address: %02x:%02x:%02x:%02x:%02x:%02x\n",
		eth[0].etpaddr[0]&0xff,
		eth[0].etpaddr[1]&0xff,
		eth[0].etpaddr[2]&0xff,
		eth[0].etpaddr[3]&0xff,
		eth[0].etpaddr[4]&0xff,
		eth[0].etpaddr[5]&0xff);
	write(stdout, str, strlen(str));
#endif
	
	for (i=0; i<Net.nif; ++i) {
		char	buf[32];

		if (nif[i].ni_state == NIS_DOWN)
			continue;
		if (i == NI_LOCAL)
			continue;
		sprintf(str,"    IP address:       %s\n",
			ip2dot(buf, nif[i].ni_ip));
		write(stdout, str, strlen(str));
		sprintf(str,"    Domain name:      %s\n",
			ip2name(nif[i].ni_ip,name) == SYSERR ? "UNKNOWN" : name);
		write(stdout, str, strlen(str));
	}


	sprintf(str,"\nTable sizes\n");
	write(stdout, str, strlen(str));

	sprintf(str,"    Number of processes:   %d\n",NPROC);
	write(stdout, str, strlen(str));

	sprintf(str,"    Number of semaphores:  %d\n",NSEM);
	write(stdout, str, strlen(str));

	sprintf(str,"    Number of devices:     %d\n",NDEVS);
	write(stdout, str, strlen(str));

	sprintf(str,"\nNetwork information\n");
	write(stdout, str, strlen(str));

#ifdef TSERVER
	sprintf(str,"    Time server:        %s	(%s)\n",
		TSERVER, FindName(TSERVER));
	write(stdout, str, strlen(str));
#endif	

#ifdef RSERVER
	sprintf(str,"    Remote file server: %s	(%s)\n",
		RSERVER, FindName(RSERVER));
	write(stdout, str, strlen(str));
#endif	

#ifdef NSERVER
	sprintf(str,"    Domain name server: %s	(%s)\n",
		NSERVER, FindName(NSERVER));
	write(stdout, str, strlen(str));
#endif	

	return(OK);
}

char *FindName(strIP)
     char *strIP;
{
    static char name[80];
    IPaddr addr;

    addr = dot2ip(strIP);
    
    if (ip2name(addr, name) == SYSERR)
	return("UNKNOWN");
    else
	return name;
}
