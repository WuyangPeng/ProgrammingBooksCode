/* rtcp.h - hton24 */

#include <rtp.h>
#define RTCP_HEADERLEN    4	/* RTCP header length (octets)		*/
#define RTCP_BWFRAC	  .05	/* fraction of b/w for RTCP		*/
#define RTCP_TTL	  16	/* TTL for our RTCP packets		*/
#define RTCP_MAXPACKETSZ  1024	/* RTCP receive buffer size		*/
#define RTCP_SR		  200   /* RTCP value for sender report		*/
#define RTCP_RR		  201	/* RTCP value for receiver report	*/
#define RTCP_BYE	  203	/* RTCP value for bye message		*/
#define hton24(v)         (((v&0xff) << 16) | (v&0xff00) |		\
			          ((v&0xff0000)>>16))

struct rtcp {
  unsigned int  rtcp_count:5;	/* object count				*/
  unsigned int	rtcp_pad:1;	/* padding present flag			*/
  unsigned int	rtcp_ver:2;	/* version				*/
  unsigned char	rtcp_type;	/* message type				*/
  unsigned short rtcp_length;	/* message length / 4 - 1		*/
  char		rtcp_data[1];	/* message data				*/
};

struct rblock {
  ssrc_t	rb_ssrc;	/* SSRC to which this rblock refers	*/
  unsigned int	rb_fraclost:8;	/* fraction lost since prev report	*/
  int		rb_cumlost:24;	/* cumulative packets lost		*/
  unsigned int	rb_hiseq;	/* extended highest seq received	*/
  unsigned int	rb_jitter;	/* jitter measure			*/
  unsigned int	rb_lastsrts;	/* middle 32 bits of last SR's NTP	*/
  unsigned int	rb_delay;	/* delay since last SR			*/
};

struct rr {
  ssrc_t	rr_ssrc;	/* SSRC of sender			*/
  char		rr_rblock[1];	/* pointer to first report block	*/
};

struct sr {
  ssrc_t	sr_ssrc;	/* SSRC of sender			*/  
  unsigned int	sr_intts;	/* NTP timestamp (high 32 bits)		*/
  unsigned int	sr_fracts;	/* NTP timestamp (low 32 bits)		*/
  unsigned int	sr_rtpts;	/* RTP media timestamp			*/
  unsigned int	sr_packets;	/* sender's sent packet count		*/
  unsigned int	sr_octets;	/* sender's sent octet count		*/
  char		sr_rblock[1];	/* pointer to first report block	*/
};

void   rtcpsendbye(void);
void   rtcpheader(struct rtcp *, int, unsigned char, int);
double rtcpinterval(int, int, double, int, int, int *, int);
void   rtcpcycle(void);
void   rtcprecv(void);
