/* rtp.h - rtptsgt, rtptsmax, rtphdrlen, rtpdata */

#include <common.h>
#include <util.h>

typedef unsigned int   ssrc_t;
typedef unsigned int   mediatime_t;
typedef	unsigned short seq_t;

#define RTP_TSWINDOW      (1 << 31)
#define RTP_CURRVERS	  2	/* RTP current version			*/
#define RTP_MINHDRLEN     12	/* RTP minimum header length		*/
#define RTP_MINSEQUENTIAL 2	/* sequential packets required		*/
#define RTP_JITTHRESH	  8000	/* jitter buffer `K' (in 1/8000 sec)	*/
#define RTP_BPBUFSZ	  2048	/* buffer pool buffer size		*/
#define RTP_BPBUFCNT      64	/* buffers in buffer pool		*/
#define RTP_LEEWAY	  400	/* playback leeway (in 1/8000 sec)	*/
#define RTP_INACTTHRESH	  5	/* number of cycles until timeout	*/
#define PCMMU_ID	  0	/* RTP ID for PCM mu-law		*/
#define PCMMU_CLKRT       8000	/* PCM clockrate			*/
#define PCMMU_BW	  64000	/* PCM bandwidth (bits/sec)		*/
#define rtptsgt(x, y)    (x>y?(x-y<RTP_TSWINDOW?TRUE:FALSE):		 \
			   (y-x<RTP_TSWINDOW?FALSE:TRUE))
#define rtptsmax(x, y)   (rtptsgt(x, y) ? x : y)
#define rtphdrlen(prtp)  (RTP_MINHDRLEN + (prtp->rtp_cc * 4))
#define rtpdata(prtp)	  ((char *) prtp + rtphdrlen(prtp))

struct rtp {
  unsigned int	rtp_cc:4;	/* source count				*/
  unsigned int	rtp_ext:1;	/* extension flag			*/
  unsigned int	rtp_pad:1;	/* padding flag				*/
  unsigned int	rtp_ver:2;	/* version				*/
  unsigned int	rtp_payload:7;	/* payload type				*/
  unsigned int	rtp_mark:1;	/* marker flag				*/
  seq_t		rtp_seq;	/* sequence number			*/
  mediatime_t	rtp_time;	/* timestamp				*/
  ssrc_t	rtp_ssrc;	/* synchronization source identifier	*/
  char		rtp_data[1];	/* beginning of RTP data		*/
};

struct rtpln {
  int		rln_len;	/* total length of packet		*/
  unsigned int	rln_seq;	/* extended sequence number	        */
  struct rtpln	*rln_next;	/* pkt with next lower sequence number	*/
  struct rtpln	*rln_prev;	/* pkt with next greater seq number	*/
  struct rtp	rln_rtp;	/* RTP packet			        */
};

struct stream {
  ssrc_t	  stm_ssrc;	/* synchronization source identifier	*/
  struct rtpln   *stm_qhead;	/* pointer to pkt with lowest seq num	*/
  struct rtpln   *stm_qtail;	/* pointer to pkt with highest seq num	*/
  pthread_mutex_t stm_qmutex;	/* mutex to lock queue			*/
  pthread_cond_t  stm_rcond;    /* cond var for blocking read	        */
  pthread_mutex_t stm_rmutex;   /* mutex associated read cond var	*/
  pthread_mutex_t stm_smutex;	/* mutex for locking stream structure	*/
  bool		  stm_buffering;/* TRUE when stream is still buffering  */
  struct timeval  stm_clkx;	/* local time stamp			*/
  mediatime_t	  stm_clky;	/* equivalent media time stamp		*/
  double	  stm_jitter;	/* jitter measure			*/ 
  int		  stm_inactive; /* number of inactive cycles or status	*/
  int		  stm_packets;	/* cumulative packets received		*/
  int		  stm_probation;/* sequential pkts to validate stream	*/
  seq_t		  stm_firstseq; /* first sequence number received	*/
  seq_t		  stm_hiseq;	/* greatest seq number recently recvd	*/
  int		  stm_badseq;	/* bad sequence number			*/
  int		  stm_roll;	/* sequence space ``roll-overs''	*/
  int		  stm_recprior; /* packets recv'd in last RTCP cycle	*/
  int		  stm_expprior; /* packets expected in last RTCP cycle	*/
  mediatime_t	  stm_lastts;	/* last ts for jitter compuataion	*/
  struct timeval  stm_lastrec;	/* time last pkt rcvd for jitter comp	*/
  unsigned int	  stm_ntp[2];   /* NTP timestamp of last SR (frac, int)	*/
  struct timeval  stm_lastsr;	/* local time last SR received	        */
};

struct session {
  unsigned int	  sn_ssrc;	/* local SSRC                           */
  int		  sn_rtpfd;	/* file descriptor for RTP		*/
  int		  sn_rtcpfd;	/* file descriptor for RTCP		*/
  struct sockaddr_in sn_rtcpto;	/* destination for RTCP packets		*/
  struct stream   sn_stream;    /* single stream being received         */
  bool            sn_detected;  /* TRUE once stream detected            */
  int             sn_avgrtcp;   /* RTCP len for interval computation	*/
};

void		rtpinit(unsigned int, int);
void		rtprecv(void);
int		rtpupdate(struct rtp *);
void		rtpinitseq(seq_t);
int		rtpupdateseq(seq_t);
void		rtpnewdata(void);
bool		rtpqinsert(struct rtpln *);
struct rtpln   *rtpqdequeue(void);
void		playaudio(void);

extern struct session	sn;
extern struct stream	stm;
