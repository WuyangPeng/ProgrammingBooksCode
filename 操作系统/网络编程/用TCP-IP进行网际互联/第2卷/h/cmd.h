/* cmd.h */

/* Declarations for all commands known by the shell */

struct	cmdent	{			/* entry in command table	*/
	char	*cmdnam;		/* name of command		*/
	Bool	cbuiltin;		/* Is this a builtin command?	*/
	int	(*cproc)();		/* procedure that implements cmd*/
};

extern	int
	x_arp(),	x_bpool(),	x_cat(),	x_close(),
	x_conf(),	x_cp(),        	x_creat(),	x_date(),
	x_devs(),	x_dg(),		x_dumper(),	x_echo(),
	x_exit(),
	x_finger(),
	x_help(),
    	x_ifstat(),	x_igmp(),
	x_kill(),	x_mem(),	x_mount(),
	x_mv(),		x_net(),	x_ns(),
	x_ospf(),
	x_ping(),	x_ps(),
	x_reboot(),	x_rf(),		x_rls(),	x_rm(),
	x_route(),	x_routes(),
	x_sema(),	x_sleep(),	x_snmp(),	x_stacktrace(),
	x_timerq(),
	x_unmou(),	x_uptime(),	x_who();

/* Commands:	 name		Builtin?	procedure	*/

#define	CMDS 	"arp",		FALSE,		x_arp,		\
		"bpool",	FALSE,		x_bpool,	\
		"cat",		FALSE,		x_cat,		\
		"close",	FALSE,		x_close,	\
		"conf",		FALSE,		x_conf,		\
		"cp",		FALSE,		x_cp,		\
		"create",	FALSE,		x_creat,	\
		"date",		FALSE,		x_date,		\
		"devs",		FALSE,		x_devs,		\
		"dg",		FALSE,		x_dg,		\
		"dumper",	FALSE,		x_dumper,	\
		"echo",		FALSE,		x_echo,		\
		"exit",		TRUE,		x_exit,		\
		"finger",	FALSE,		x_finger,	\
		"help",		FALSE,		x_help,		\
		"ifstat",	FALSE,		x_ifstat,	\
		"igmp",		FALSE,		x_igmp,		\
		"kill",		TRUE,		x_kill,		\
		"logout",	TRUE,		x_exit,		\
		"mem",		FALSE,		x_mem,		\
		"mount",	FALSE,		x_mount,	\
		"mv",		FALSE,		x_mv,		\
		"netstat",	FALSE,		x_net,		\
		"ns",		FALSE,		x_ns,		\
		"ospf",		FALSE,		x_ospf,		\
		"ping",		FALSE,		x_ping,		\
		"ps",		FALSE,		x_ps,		\
		"reboot",	TRUE,		x_reboot,	\
		"rf",		FALSE,		x_rf,		\
		"rls",		FALSE,		x_rls,		\
		"rm",		FALSE,		x_rm,		\
		"route",	FALSE,		x_route,	\
		"routes",	FALSE,		x_routes,	\
		"ruptime",	FALSE,		x_uptime,	\
		"sema",		FALSE,		x_sema,		\
		"sleep",	FALSE,		x_sleep,	\
		"snmp",		FALSE,		x_snmp,		\
		"stacktrace",	FALSE,		x_stacktrace,	\
		"time",		FALSE,		x_date,		\
		"timerq",	FALSE,		x_timerq,	\
		"unmount",	FALSE,		x_unmou,	\
		"uptime",	FALSE,		x_uptime,	\
		"who",		FALSE,		x_who,		\
		"?",		FALSE,		x_help

extern	struct	cmdent	cmds[];
