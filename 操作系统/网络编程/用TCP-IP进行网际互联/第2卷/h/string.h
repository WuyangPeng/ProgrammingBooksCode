/* string.h */

void	*memcpy(void *, const void *, size_t);
void	*memset(void *, int, size_t);
char	*index(const char *, char);
char	*strcat(char *, char *), strncat(char *, char *, size_t);
char	*strncpy(char *, const char *, size_t);
int	strncmp(const char *, const char *, size_t);
int	sscanf(const char *, const char *, ...);

#define	BLKEQU(b1, b2, len)	(!memcmp((b1), (b2), len))
