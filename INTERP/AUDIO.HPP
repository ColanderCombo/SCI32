// audio.hpp

#ifndef AUDIO_HPP
#define AUDIO_HPP

#ifndef RESTYPE_HPP
#include "restype.hpp"
#endif

class MemID;

extern "C" {
void Merge(void far *, void *, int, char, char);
void Distort(void far *, int, char, char);
void Volume(void far *, int, char, char);
void Silence(void far *, int, char);
void Fill(void *, int, char);
char Decomp4To8(void *, void *, int, char);
int  Decomp8To16(void *, void *, int, int);
void Conv16To8(void *, void *, int);
void Conv8To16(void *, int);
void Conv11KTo22K(void *, int, char);
void CopyEOS(void *, void *, int, char);
void DupeChannel(void *, int, int, char);
}

#pragma aux (PushArgs) Merge;
#pragma aux (PushArgs) Distort;
#pragma aux (PushArgs) Volume;
#pragma aux (PushArgs) Silence;
#pragma aux (PushArgs) Fill;
#pragma aux (PushArgs) Decomp4To8;
#pragma aux (PushArgs) Decomp8To16;
#pragma aux (PushArgs) Conv16To8;
#pragma aux (PushArgs) Conv8To16;
#pragma aux (PushArgs) Conv11KTo22K;
#pragma aux (PushArgs) CopyEOS;
#pragma aux (PushArgs) DupeChannel;

void		AudioServer();
int		CallDAC(int,int);
Bool		InitAudioDriver();
void		EndAudio();
void		MakeName36(MemType,char*,ResNum,uchar,uchar,uchar,uchar);
int		FindAud36Entry(ResNum,uchar,uchar,uchar,uchar);
int		FindAudEntry(ResNum);

extern Bool		audioInstalled;
extern int		audVolFD;
extern int		sfxVolFD;
extern int		activeSamples;

// Audio Kernel Functions
enum	audioFuncs {
	WPLAY = 1,
	PLAY,
	STOP,
	PAUSE,
	RESUME,
	LOC,
	RATE,
	VOLUME,
	DACFOUND,
	BITS,
	DISTORT,
	DACMIXNORMAL,
	CHANNELS,
	PRELOAD,
	FADE
};

// Codes to be sent to the audio driver.
enum	audioCodes {
	DAC_INIT = 2,
	DAC_CONTINUE,
	DAC_TERMINATE,
	DAC_PLAY,
	DAC_STOP,
	DAC_PAUSE,
	DAC_RESUME,
	DAC_LOC,
	DAC_SET_RATE,
	DAC_SET_BITS,
	DAC_SET_CHANNELS,
	DAC_SET_VOLUME,
	DAC_SET_IRQ,
	DAC_SET_DMA,
	DAC_SET_BUFF,
	DAC_GET_ID,
	DAC_GET_VER,
	DAC_GET_REALOC,
	DAC_GET_MAX_CHNLS,
	DAC_GET_MAX_BITS,
	DAC_GET_MAX_RATE,
	DAC_GET_VOL,
	DAC_GET_BUFF_SEL,
	DAC_GET_BUFF_OFS
};

// structure of information in resource map file 
// used for audio type resource only 
_Packed struct ResAudEntry {
	unsigned short	id;
	unsigned short	offsetLSW;
	unsigned char	offsetMSB;
};

// structure of information in resource map file 
// used for sync+rave+audio base-36 type resource only 
_Packed struct ResAud36Entry {
	unsigned char	noun;
	unsigned char	verb;
	unsigned char	cond;
	union {
		unsigned char	sequ;
		unsigned char	sync;
		unsigned char	rave;
	} flag; 
	unsigned short	offsetLSW;
	unsigned char	offsetMSB;
	unsigned short	syncLen;
	unsigned short	raveLen;
};

struct RobotAudInfo
{
	RobotAudInfo(char* buff, int byteLen, int fileLoc)	:
		adr(buff), blen(byteLen), floc(fileLoc)  {}

	RobotAudInfo() {}

	char*		adr;			// compressed buffer address
	int		blen;			// compressed buffer length
	int		floc;			// original file-relative offset
	int		bofs[2];		// next uncompressed buffer offset
	int		hwm[2];		// next uncompressed file-relative offset
	MemID		id;			// uncompressed buffer
	int		len;			// uncompressed buffer length
	int		channel;		// even or odd buffer
	int		pofs;			// next uncompressed file-relative offset to play
};

Bool	AudRobot(RobotAudInfo);

#define	SYNCMASK		0x80
#define	RAVEMASK		0x40
#define	SEQUMASK		0x3F

// (Note: DAC_HBUFFSIZE must be a 2K multiple if ARIA is supported)
#define	DAC_HBUFFSIZE	(1*1024)
#define	DAC_MAXHBSIZE	(16*1024)
#define	INT_HBUFFSIZE	(30*1024)
#define	INT_MAXHBSIZE	(31*1024)

#endif
