 /*
  * @(#) scaffold.h 1.3 94/12/31 18:19:19
  * 
  * Author: Wietse Venema, Eindhoven University of Technology, The Netherlands.
  */

struct hostent *find_inet_addr __P((char *));
int check_dns __P((char *));
void shell_cmd __P((char *));
void clean_exit __P((struct request_info *));
#if 0
void rfc931 __P((struct request_info *));
#endif
int check_path __P((char *, struct stat *));
