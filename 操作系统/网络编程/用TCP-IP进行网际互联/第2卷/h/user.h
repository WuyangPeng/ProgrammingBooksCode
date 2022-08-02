/* user.h */

struct user {
	unsigned int	 ue_uid;	/* numeric user identifier	*/
	char		*ue_login;	/* user's login name		*/
	char		*ue_name;	/* users real name		*/
	char		*ue_passwd;	/* users encrypted password	*/
};

extern struct user utab[];
struct user *getuser(unsigned long);
