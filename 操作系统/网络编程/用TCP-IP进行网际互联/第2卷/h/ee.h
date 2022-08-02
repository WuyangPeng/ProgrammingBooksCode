/* ee.h - H2IO, IO2H */

/*
 * Constants for the Intel EtherExpress16 Ethernet device
 */

#define	EE_NRX		6	/* number (1520 byte) receive buffers	*/
#define	EE_NTX		1	/* number (1520 byte) transmit buffers	*/

#define	EE_SETMULTI	1	/* indicate set multicast to wstrt	*/

#define	EDLEN		1520

#define H2IO(ped, x)	((unsigned short)((char *)(x) - ped->ed_iomem))
#define IO2H(ped, x)	(ped->ed_iomem + (int)(x))

/* registers */

#define	DXREG		0x0	/* data transfer			*/
#define	WRPTR		0x2	/* write pointer			*/
#define	RDPTR		0x4	/* read pointer				*/
#define	CAC		0x6	/* channel attention			*/
#define	SIRQ		0x7	/* IRQ select				*/
#define	SMB		0x8	/* Shadow memory ptrs			*/
#define	MEMDEC		0xa	/* memory address decode		*/
#define	MEMC		0xb	/* memory mapped control		*/
#define	MEMPC		0xc	/* memcs16 page control			*/
#define	CONFIG		0xd	/* configuration and test		*/
#define	EEC		0xe	/* EEPROM control, reset		*/
#define	MEMEC		0xf	/* memory and control, e000 seg		*/
#define	AID		0xf	/* automatic ID				*/

/* Bit definitions */

#define	CONFIG_LINK	0x01	/* link integrity disable		*/
#define	CONFIG_LOOP	0x02	/* loop-back test enable		*/
#define	CONFIG_BUS16	0x04	/* adapter is in 16 bit slot		*/
#define	CONFIG_16EN	0x08	/* enable 16-bit if supported		*/
#define	CONFIG_ICLATE	0x10	/* activate IOCHRDY late		*/
#define	CONFIG_IOTE	0x20	/* IOCHRDY early/late test enable	*/
#define	CONFIG_TOGGLE	0x40	/* early/late test result		*/
#define	CONFIG_MCS16	0x80	/* test MEMCS16- settings		*/

#define	MEMC_MCS16	0x10	/* use MEMCS16- for 0xf0000 access	*/

#define	EEC_SK		0x01	/* EEPROM shift clock			*/
#define	EEC_CS		0x02	/* EEPROM chip select			*/
#define	EEC_DI		0x04	/* EEPROM data in			*/
#define	EEC_DO		0x08	/* EEPROM data out			*/
#define	EEC_GAR		0x40	/* reset ASIC				*/
#define	EEC_586R	0x80	/* reset 586				*/

#define	SIRQ_MASK	0x07	/* IRQ index				*/
#define	SIRQ_IEN	0x08	/* interrupt enable			*/

/* EEPROM commands */

#define	EEX_READ	0x06

/* EEPROM addresses */

#define	EE_BOARD	0x00	/* board configuration info		*/
#define	EE_MEM1		0x01	/* memory map (MEMC & MEMPC)		*/
#define	EE_EADDR	0x02	/* Ethernet address base (word offset)	*/
#define	EE_MEM2		0x06	/* memory map (MEMDEC)			*/

#define	EE_ROMSIZE	64	/* 16-bit words				*/

/* buffer memory map */

#define	MEMSIZE		0x10000
#define	ISCP		0x0		/* ISCP offset	*/
#define	SCB		0x8		/* SCB offset	*/
#define	SCP		0xfff6		/* SCP offset	*/

#define	SYSBUS_16	0x0
#define	SYSBUS_8	0x1

/* SCP & ISCP structs */

struct scp {
	unsigned char	 scp_sysbus;
	unsigned char	 scp_pad1;
	unsigned long	 scp_pad2;
	unsigned char	*scp_iscp;
};
struct iscp {
	unsigned char	 iscp_busy;
	unsigned char	 iscp_pad0;
	unsigned short	 iscp_scboff;
	unsigned char	*iscp_scbbase;
};

/* system control block */

struct scb {
	unsigned short	scb_status;	/* 82586 status		*/
	unsigned short	scb_cmd;	/* command word		*/
	unsigned short	scb_cbloff;	/* CBL offset		*/
	unsigned short	scb_rfaoff;	/* RFA offset		*/
	unsigned short	scb_ecrc;	/* # CRC errors		*/
	unsigned short	scb_ealign;	/* # alignment error	*/
	unsigned short	scb_eresource;	/* # resource errors	*/
	unsigned short	scb_eover;	/* # over-run errors	*/
};

#define	STAT_CX		0x8000		/* action command completed	*/
#define	STAT_FR		0x4000		/* received a frame		*/
#define	STAT_CNA	0x2000		/* CU left active state		*/
#define	STAT_RNR	0x1000		/* receiver not ready		*/
#define	STAT_CUS	0x0100		/* CU is suspended		*/
#define	STAT_CUA	0x0200		/* CU is active			*/
#define	STAT_RUR	0x0040		/* RU is ready			*/

#define	SCBCMD_CUS	0x0100		/* start command unit		*/
#define	SCBCMD_RUS	0x0010		/* start receive unit		*/

#define	CFLEN	12

/* command block */

struct cbl {
	unsigned short	cbl_status;
	unsigned short	cbl_cmd;
	unsigned short	cbl_next;	/* next command			*/
	union {
		unsigned char		cbu_addr[EP_ALEN];
		struct {
			unsigned short	cbt_tbd;
			unsigned char	cbt_dst[EP_ALEN];
			unsigned short	cbt_len;
		} cbu_txdata;
		struct {
			unsigned short	cbm_alen;
			Eaddr		cbm_mca[EP_MAXMULTI];
		} cbu_mcdata;
		unsigned char		cbu_cfg[CFLEN];
	} cbl_data;
};

#define	cbl_addr	cbl_data.cbu_addr
#define	cbl_cfg		cbl_data.cbu_cfg
#define	cbl_tbd		cbl_data.cbu_txdata.cbt_tbd
#define	cbl_dst		cbl_data.cbu_txdata.cbt_dst
#define	cbl_len		cbl_data.cbu_txdata.cbt_len
#define	cbl_alen	cbl_data.cbu_mcdata.cbm_alen
#define	cbl_mca		cbl_data.cbu_mcdata.cbm_mca

/* command definitions */

#define	EECMD_NOP	0	/* no operation				*/
#define	EECMD_IASET	1	/* set the individual Ethernet address	*/
#define	EECMD_CONFIG	2	/* configure LAN parameters		*/
#define	EECMD_MCSET	3	/* set multicast address table		*/
#define	EECMD_TX	4	/* transmit a packet			*/

#define	EECMD_MASK	7	/* mask bits for basic command		*/

/* command modifiers */

#define	EECMD_EL	0x8000		/* is last on the list		*/
#define	EECMD_S		0x4000		/* suspend after completion	*/
#define	EECMD_I		0x2000		/* interrupt after completion	*/

#define	MCSTAT_C	0x8000		/* MCADD command completed	*/
#define	MCSTAT_OK	0x2000		/* error-free completion	*/
#define	MCSTAT_A	0x1000		/* command aborted		*/

/* transmit buffer descriptor */

struct tbd {
	unsigned int	tbd_count:14;	/* data byte count		*/
	unsigned int	tbd_pad:1;
	unsigned int	tbd_eof:1;	/* true if last TBD on list	*/
	unsigned short	tbd_next;
	unsigned int	tbd_buf;
};

/* transmit status bit definitions */

#define	TSTAT_C		0x8000		/* command completed		*/
#define	TSTAT_OK	0x2000		/* no transmit errors		*/
#define	TSTAT_NC	0x0400		/* no carrier			*/

/* receive structures */

/* Frame Descriptor */
struct rfd {
	unsigned short	rfd_status;	/* receive frame status		*/
	unsigned short	rfd_cmd;	/* command word			*/
	unsigned short	rfd_next;	/* next rfd offset		*/
	unsigned short	rfd_rbd;	/* RBD offset			*/
	Eaddr		rfd_dst;	/* destination Ether address	*/
	Eaddr		rfd_src;	/* source Ether address		*/
	unsigned short	rfd_len;	/* frame length			*/
};

#define	RSTAT_C		0x8000		/* completed storing a frame	*/
#define	RSTAT_OK	0x2000		/* received frame ok		*/
#define	RSTAT_ERR	0x0fc0		/* received frame error	mask	*/

/* Receive Buffer Descriptor */

struct rbd {
	unsigned int	rbd_count:14;	/* data byte count		*/
	unsigned int	rbd_valid:1;	/* count field valid		*/
	unsigned int	rbd_eof:1;	/* last buffer of frame		*/
	unsigned short	rbd_next;	/* next RBD offset		*/
	unsigned int	rbd_buf;	/* address of buffer		*/
	unsigned int	rbd_size:14;	/* size this buffer		*/
	unsigned int	rbd_pad:1;
	unsigned int	rbd_el:1;	/* end of buffer list		*/
};
