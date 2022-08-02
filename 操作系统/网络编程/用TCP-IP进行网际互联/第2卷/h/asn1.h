/* asn1.h - A1_SIGNED */

/* constants for parsing an SNMP packet, according to ASN.1		*/

/* ASN.1 object types */
#define ASN1_SEQ		0x30	/* sequence object		*/
#define	ASN1_INT		0x02	/* integer			*/
#define	ASN1_OCTSTR		0x04	/* octet string			*/
#define ASN1_NULL		0x05	/* null				*/
#define ASN1_OBJID		0x06	/* object identifier		*/
#define ASN1_IPADDR		0x40	/* ip address			*/
#define ASN1_COUNTER		0x41	/* counter			*/
#define ASN1_GAUGE		0x42	/* gauge			*/
#define ASN1_TIMETICKS		0x43	/* time ticks			*/

/* Protocol Data Unit types -- SNMP specific				*/
#define PDU_GET			0xA0	/* get request			*/
#define PDU_GETN		0xA1	/* get-next request		*/
#define PDU_RESP		0xA2	/* response			*/
#define PDU_SET			0xA3	/* set request			*/
#define PDU_TRAP		0xA4	/* trap message 		*/

/* Constants used for conversion of objects to/from ASN.1 notation	*/
#define CHAR_BITS	8		/* number of bits per char	*/
#define CHAR_HIBIT	0x80		/* octet with the high bit set	*/
#define BYTE2_HIBIT	0x8000		/* 2 bytes with high bit set	*/
#define BYTE3_HIBIT	0x800000	/* 3 bytes with high bit set	*/
#define BYTE4_HIBIT	0x80000000	/* 4 bytes with high bit set	*/

#define	A1_SIGNED(x)	((x) == ASN1_INT)

/* the standard MIB prefix - 1.3.6.1.2.1 				*/
extern char MIB_PREFIX[];

/* the standard MIB prefix is encoded by ASN.1 into 5 octets		*/
#define MIB_PREF_SZ 	5
