/* local.h */

#include <termios.h>

extern FILE	*scrfp;
extern char	scrname[];
extern struct termios	oldtty;

extern char	t_flushc, t_intrc, t_quitc, sg_erase, sg_kill;

extern int	errno;

int	errexit(const char *format, ...), cerrexit(const char *format, ...);
int	ttwrite(FILE *sfp, FILE *tfp, unsigned char *buf, int cc);
int	sowrite(FILE *sfp, FILE *tfp, unsigned char *buf, int cc);
int	fsmbuild(void);
