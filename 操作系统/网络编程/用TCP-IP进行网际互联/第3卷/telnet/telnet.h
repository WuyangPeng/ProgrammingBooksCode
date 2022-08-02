/* telnet.h */

typedef unsigned char u_char;

/* TELNET Command Codes: */
#define	TCSB		(u_char)250	/* Start Subnegotiation		*/
#define	TCSE		(u_char)240	/* End Of Subnegotiation	*/
#define	TCNOP		(u_char)241	/* No Operation			*/
#define	TCDM		(u_char)242	/* Data Mark (for Sync)		*/
#define	TCBRK		(u_char)243	/* NVT Character BRK		*/
#define	TCIP		(u_char)244	/* Interrupt Process		*/
#define	TCAO		(u_char)245	/* Abort Output			*/
#define	TCAYT		(u_char)246	/* "Are You There?" Function	*/ 
#define	TCEC		(u_char)247	/* Erase Character		*/
#define	TCEL		(u_char)248	/* Erase Line			*/
#define	TCGA		(u_char)249	/* "Go Ahead" Function		*/
#define	TCWILL		(u_char)251	/* Desire/Confirm Will Do Option*/
#define	TCWONT		(u_char)252	/* Refusal To Do Option		*/
#define	TCDO		(u_char)253	/* Request To Do Option		*/
#define	TCDONT		(u_char)254	/* Request NOT To Do Option	*/
#define	TCIAC		(u_char)255	/* Interpret As Command Escape	*/

/* Telnet Option Codes: */
#define	TOTXBINARY	(u_char)  0	/* TRANSMIT-BINARY option	*/
#define	TOECHO		(u_char)  1	/* ECHO Option			*/
#define	TONOGA		(u_char)  3	/* Suppress Go-Ahead Option	*/
#define	TOTERMTYPE	(u_char) 24	/* Terminal-Type Option		*/

/* Network Virtual Printer Special Characters: */
#define	VPLF		'\n'	/* Line Feed				*/
#define	VPCR		'\r'	/* Carriage Return			*/
#define	VPBEL		'\a'	/* Bell (attention signal)		*/
#define	VPBS		'\b'	/* Back Space				*/
#define	VPHT		'\t'	/* Horizontal Tab			*/
#define	VPVT		'\v'	/* Vertical Tab				*/
#define	VPFF		'\f'	/* Form Feed				*/

/* Keyboard Command Characters: */
#define	KCESCAPE	035	/* Local escape character ('^]')	*/
#define	KCDCON		'.'	/* Disconnect escape command		*/
#define	KCSUSP		032	/* Suspend session escape command ('^Z')*/
#define	KCSCRIPT	's'	/* Begin scripting escape command	*/
#define	KCUNSCRIPT	'u'	/* End scripting escape command		*/
#define	KCSTATUS	024	/* Print status escape command ('^T')	*/
#define	KCNL		'\n'	/* Newline character			*/

#define	KCANY		(NCHRS+1)

/* Option Subnegotiation Constants: */
#define	TT_IS		0	/* TERMINAL_TYPE option "IS" command	*/
#define	TT_SEND		1	/* TERMINAL_TYPE option "SEND" command	*/

/* Boolean Option and State variables */
extern char	synching, doecho, sndbinary, rcvbinary;
