/* syslog.h */

#define LOG_MAXLEN	256	/* max log mesg line length	*/

/* log priorities */

#define LOG_EMERG	0
#define	LOG_ALERT	1
#define	LOG_CRIT	2
#define	LOG_ERR		3
#define	LOG_WARNING	4
#define	LOG_NOTICE	5
#define	LOG_INFO	6
#define	LOG_DEBUG	7

/* log facilties */

#define	LOG_KERN	0000
#define	LOG_USER	0010
#define	LOG_MAIL	0020
#define	LOG_DAEMON	0030
#define LOG_AUTH	0040
#define	LOG_SYSLOG	0050
#define	LOG_LPR		0060
#define	LOG_NEWS	0070
#define	LOG_UUCP	0100
#define	LOG_CRON	0110
#define	LOG_AUTHPRIV	0120

int syslog(int, char *, char *, ...);
